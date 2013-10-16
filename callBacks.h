#ifndef CALLBACKS_H
#define CALLBACKS_H
#include "QtKinect.h"

void XN_CALLBACK_TYPE FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
    QtKinect *instance = static_cast<QtKinect*>(UserCxt);
    instance->focusProgress(strFocus, ptPosition, fProgress, UserCxt);
}
void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
    QtKinect *instance = static_cast<QtKinect*>(UserCxt);
    instance->sessionStarting(ptPosition, UserCxt);
}
void XN_CALLBACK_TYPE SessionEnding(void* UserCxt)
{
    QtKinect *instance = static_cast<QtKinect*>(UserCxt);
    instance->sessionEnding(UserCxt);
}
void XN_CALLBACK_TYPE PushCB (XnFloat fVelocity, XnFloat fAngle, void *UserCxt)
{
    QtKinect *instance = static_cast<QtKinect*>(UserCxt);
    instance->pushCB( fVelocity, fAngle, UserCxt);
}

void XN_CALLBACK_TYPE WaveCB (void *UserCxt)
{
    QtKinect *instance = static_cast<QtKinect*>(UserCxt);
    instance->waveCB(UserCxt);

}

void XN_CALLBACK_TYPE PointCreateCB(const XnVHandPointContext* pContext, void* cxt)
{
    QtKinect *instance = static_cast<QtKinect*>(cxt);
    instance->pointCreateCB( pContext, cxt);
}
void XN_CALLBACK_TYPE PointUpdateCB(const XnVHandPointContext* pContext, void* cxt)
{
    QtKinect *instance = static_cast<QtKinect*>(cxt);
    instance->pointUpdateCB( pContext, cxt);
}

#endif // CALLBACKS_H
