#ifndef QDISCORD_GLOBAL_H
#define QDISCORD_GLOBAL_H

#include <QtCore/qglobal.h>

#ifndef QDISCORD_STATIC
#  ifdef QDISCORD_LIBRARY
#    define QDISCORD_API Q_DECL_EXPORT
#  else
#    define QDISCORD_API Q_DECL_IMPORT
#  endif
#endif

#endif // QDISCORD_GLOBAL_H
