#include "QtKinect.h"
#include <QDebug>
#include <QMetaType>
#include <QTime>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QDir>

#include "callBacks.h"

QtKinect::QtKinect(QObject * parent) :
    QThread(parent),
    m_f_ctx(0),
    m_f_dev(0),
    m_pSessionManager(0),
    m_handTracker(0),
    m_pushDetector(0),
    m_deviceOpened(false),
    m_terminateExecution(false)
{

}

void QtKinect::cleanupExit()
{
    m_scriptNode.Release();
    m_depthGenerator.Release();
    m_handsGenerator.Release();
    m_gestureGenerator.Release();
    m_context.Release();

    m_terminateExecution = true;
    wait();
}

// Callback for when the focus is in progress
void QtKinect::focusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
    Q_UNUSED(strFocus)
    Q_UNUSED(ptPosition)
    Q_UNUSED(fProgress)
    emit message(tr("Focus progress: %1").arg(fProgress));
}

// callback for session start
void QtKinect::sessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
    Q_UNUSED(ptPosition)
    Q_UNUSED(UserCxt)
    emit message(tr("Session start"));
}

// Callback for session end
void QtKinect::sessionEnding(void* UserCxt)
{
    Q_UNUSED(UserCxt)
    emit message(tr("Session end"));
}

void QtKinect::pushCB (XnFloat fVelocity, XnFloat fAngle, void *UserCxt)
{
    Q_UNUSED(fVelocity)
    Q_UNUSED(fAngle)
    Q_UNUSED(UserCxt)
    emit pushDetected();
}

void QtKinect::waveCB(void *UserCxt)
{
    Q_UNUSED(UserCxt)
    emit waveDetected();
}

void QtKinect::pointCreateCB(const XnVHandPointContext* pContext, void* cxt)
{
    Q_UNUSED(cxt)
    emit pointGenerated(pContext->ptPosition, pContext->nID);
}

void QtKinect::pointUpdateCB(const XnVHandPointContext* pContext, void* cxt)
{
    Q_UNUSED(cxt)
    emit pointGenerated(pContext->ptPosition, pContext->nID);
}

void QtKinect::initDevice()
{
    emit message(tr("starting Kinect initialisation"));

    //Retrieve xml file from Qt resource, then create a temporary file in order to have a valid path to give to the Kinect libs.
    QFile xmlFile(":/configTracking.xml");
    xmlFile.open(QIODevice::ReadOnly);
    QTemporaryFile xmlTempFile;
    if (xmlTempFile.open())
        xmlTempFile.write(xmlFile.readAll());
    xmlTempFile.seek(0);

    XnStatus rc = XN_STATUS_OK;
    xn::EnumerationErrors errors;

    // Initialize OpenNI
    rc = m_context.InitFromXmlFile(xmlTempFile.fileName().toAscii(), m_scriptNode, &errors);
    CHECK_ERRORS(rc, errors, "InitFromXmlFile");
    CHECK_RC(rc, "InitFromXmlFile");

    rc = m_context.FindExistingNode(XN_NODE_TYPE_DEPTH, m_depthGenerator);
    CHECK_RC(rc, "Find depth generator");
    rc = m_context.FindExistingNode(XN_NODE_TYPE_HANDS, m_handsGenerator);
    CHECK_RC(rc, "Find hands generator");
    rc = m_context.FindExistingNode(XN_NODE_TYPE_GESTURE, m_gestureGenerator);
    CHECK_RC(rc, "Find gesture generator");

    // Create NITE objects
    m_pSessionManager = new XnVSessionManager;
    rc = m_pSessionManager->Initialize(&m_context, "Click,Wave", "RaiseHand");
    CHECK_RC(rc, "SessionManager::Initialize");

    m_pSessionManager->RegisterSession(this, &::SessionStarting, &::SessionEnding, &::FocusProgress);

    m_handTracker = new XnVPointControl("Hand tracker");
    m_handTracker->RegisterPointCreate(this, &::PointCreateCB);
    m_handTracker->RegisterPointUpdate(this, &::PointUpdateCB);
    m_pFlowRouters.append(new XnVFlowRouter);
    m_pFlowRouters.last()->SetActive(m_handTracker);

    //push
    m_pushDetector = new XnVPushDetector("pushes");
    m_pushDetector->RegisterPush(this, &::PushCB);
    m_pFlowRouters.append(new XnVFlowRouter);
    m_pFlowRouters.last()->SetActive(m_pushDetector);

    //wave
    m_waveDetector=new XnVWaveDetector("waves");
    m_waveDetector->RegisterWave(this,&::WaveCB);
    m_pFlowRouters.append(new XnVFlowRouter);
    m_pFlowRouters.last()->SetActive(m_waveDetector);

    //add the listeners
    foreach(XnVFlowRouter * router, m_pFlowRouters)
        m_pSessionManager->AddListener(router);

    //libfreenect init for led/motor/acc stuff
    if (freenect_init(&m_f_ctx, NULL) < 0) {
        emit message(tr("Freenect driver failed to initialize."));
        return;
    }
    freenect_set_log_level(m_f_ctx, FREENECT_LOG_DEBUG);
    int nr_devices = freenect_num_devices (m_f_ctx);
    emit message(tr("Number of devices found: %1").arg(nr_devices));
    freenect_select_subdevices(m_f_ctx, FREENECT_DEVICE_MOTOR);
    if (freenect_open_device(m_f_ctx, &m_f_dev, 0) < 0) {
        emit message("Could not open device");
        m_deviceOpened = false;
    }
    else {
        emit message(tr("device successfully opened"));
        m_deviceOpened = true;
    }

    // Initialization done. Start generating
    rc = m_context.StartGeneratingAll();
    CHECK_RC(rc, "StartGenerating");
    rc = m_gestureGenerator.StartGenerating();
    CHECK_RC(rc, "StartGenerating gestures");

    emit message(tr("Kinect initialized. Entering main loop."));
    start();
}

void QtKinect::setLed(freenect_led_options led, const bool autoLED)
{
    freenect_set_led(m_f_dev,led);
}

void QtKinect::setTilt(int degres)
{
    freenect_set_tilt_degs(m_f_dev,degres);
}

void QtKinect::run()
{
    XnStatus rc = XN_STATUS_OK;
    forever{
        if (m_terminateExecution)
            return;
        rc = m_context.WaitAnyUpdateAll();
        CHECK_RC(rc, "updating context");
        m_pSessionManager->Update(&m_context);
    }
}
