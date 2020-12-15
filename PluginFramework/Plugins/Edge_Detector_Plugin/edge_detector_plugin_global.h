#ifndef EDGE_DETECTOR_PLUGIN_GLOBAL_H
#define EDGE_DETECTOR_PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(EDGE_DETECTOR_PLUGIN_LIBRARY)
#  define EDGE_DETECTOR_PLUGINSHARED_EXPORT Q_DECL_EXPORT
#else
#  define EDGE_DETECTOR_PLUGINSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // EDGE_DETECTOR_PLUGIN_GLOBAL_H