#ifndef RAENGINE_GLOBAL_H
#define RAENGINE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(RAENGINE_LIBRARY)
#  define RAENGINESHARED_EXPORT Q_DECL_EXPORT
#else
#  define RAENGINESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // RAENGINE_GLOBAL_H
