#ifndef QTKINECT_GLOBAL_H
#define QTKINECT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QTKINECT_LIBRARY)
#  define QTKINECTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define QTKINECTSHARED_EXPORT Q_DECL_IMPORT
#endif

#define CHECK_RC(rc, what)                                                            \
        if (rc != XN_STATUS_OK)                                                       \
        {                                                                             \
            emit message(QString("%1 failed: %2").arg(what , xnGetStatusString(rc))) ;\
            return;                                                                   \
        }

#define CHECK_ERRORS(rc, errors, what)                                                \
        if (rc == XN_STATUS_NO_NODE_PRESENT)                                          \
        {                                                                             \
                XnChar strError[1024];                                                \
                errors.ToString(strError, 1024);                                      \
                emit message(strError) ;                                              \
                return;                                                               \
        }

#endif // QTKINECT_GLOBAL_H
