#ifndef QTKINECT_H
#define QTKINECT_H

#include <QThread>

#include <XnOpenNI.h>
#include <XnCppWrapper.h>

// Header for NITE
#include "XnVNite.h"
#include "XnVPointControl.h"

#include "QtKinect_global.h"

#include "libfreenect.h"

class QTemporaryFile;

class QtKinect : public QThread{
    Q_OBJECT
public:
    explicit QtKinect(QObject * parent = 0);
    ~QtKinect() { cleanupExit(); }

    void cleanupExit();
    void focusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt);
    void sessionStarting(const XnPoint3D& ptPosition, void* UserCxt);
    void sessionEnding(void* UserCxt);
    void gestureRecognized (xn::GestureGenerator &generator, const XnChar *strGesture, const XnPoint3D *pIDPosition, const XnPoint3D *pEndPosition, void *pCookie);

    void pushCB (XnFloat fVelocity, XnFloat fAngle, void *UserCxt);
    void waveCB (void *UserCxt);

    void pointCreateCB(const XnVHandPointContext* pContext, void* cxt);
    void pointUpdateCB(const XnVHandPointContext* pContext, void* cxt);

    void initDevice();

    void setLed(freenect_led_options led, const bool autoLED = true);
    void setTilt(int degres);

    const bool kinectIsOpen() { return m_deviceOpened; }

private:

    // OpenNI objects
    xn::Context m_context;
    xn::ScriptNode m_scriptNode;
    xn::DepthGenerator m_depthGenerator;
    xn::HandsGenerator m_handsGenerator;
    xn::GestureGenerator m_gestureGenerator;

    //libfreenect objects
    freenect_context *m_f_ctx;
    freenect_device *m_f_dev;

    // NITE objects
    XnVSessionManager* m_pSessionManager;

    //need one for every gesture recognition object, so list is easier
    QList<XnVFlowRouter*> m_pFlowRouters;

    // the drawer
    XnVPointControl* m_handTracker;

    //Gesture recognition
    XnVPushDetector* m_pushDetector;
    XnVWaveDetector* m_waveDetector;

    bool m_deviceOpened;
    bool m_terminateExecution;

protected:
    void run();
Q_SIGNALS:
    void message(const QString &);
    void pointGenerated(XnPoint3D handPoint, XnUInt32 handID);
    void pushDetected();
    void waveDetected();

};
#endif // QTKINECT_H
