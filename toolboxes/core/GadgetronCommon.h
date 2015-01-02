#ifndef GADGETRONCOMMON_H
#define GADGETRONCOMMON_H
//#include "log.h"
#include <iostream>

#ifndef _WIN32

#define GCC_VERSION (__GNUC__ * 10000           \
                     + __GNUC_MINOR__ * 1000    \
                     + __GNUC_PATCHLEVEL__)

#if GCC_VERSION < 42000
#pragma message ("GCC version is older than 4.2.0")
#define GCC_OLD_FLAG 1
#endif

#else

    // disable warning 4251, needs to have dll-interface to be used by clients
    #pragma warning( disable : 4251 )

    // warning C4344: behavior change: use of explicit template arguments
    #pragma warning( disable : 4344 )

    // The POSIX name for this item is deprecated. Instead, use the ISO C++ conformant name
    #pragma warning( disable : 4996 )

#endif // _WIN32


// Macros FOR TIMING
#define GADGET_START_TIMING(timer, oper) { timer.start(#oper); } 
#define GADGET_STOP_TIMING(timer) { timer.stop(); }

#define GADGET_START_TIMING_CONDITION(timer, oper, con) { if ( con ) { timer.start(#oper); } } 
#define GADGET_STOP_TIMING_CONDITION(timer, con) { if ( con ) { timer.stop(); } }

// MACROS FOR PRINTING
#define GADGET_OSTREAM_PRINT(os, content) { os << #content << " is " << content << std::endl; }

#define GADGET_CHECK_PERFORM(con, action) { if ( con ) { action; } }

// MACROS for EXPORTING
#define GADGET_EXPORT_ARRAY(debugFolder, exporter, a, filename) { if ( !debugFolder.empty() ) { exporter.exportArray(a, debugFolder+filename); } }
#define GADGET_EXPORT_ARRAY_COMPLEX(debugFolder, exporter, a, filename) { if ( !debugFolder.empty() ) { exporter.exportArrayComplex(a, debugFolder+filename); } }
#define GADGET_EXPORT_ARRAY_COMPLEX_REAL_IMAG(debugFolder, exporter, a, filename) { if ( !debugFolder.empty() ) { exporter.exportArrayComplexRealImag(a, debugFolder+filename); } }

#define GADGET_EXPORT_IMAGE(debugFolder, exporter, a, filename) { if ( !debugFolder.empty() ) { exporter.exportImage(a, debugFolder+filename); } }
#define GADGET_EXPORT_IMAGE_COMPLEX(debugFolder, exporter, a, filename) { if ( !debugFolder.empty() ) { exporter.exportImageComplex(a, debugFolder+filename); } }


// MACROS FOR UTILITY
#define GT_MIN(a,b)    (((a)<(b))?(a):(b))
#define GT_MAX(a,b)    (((a)>(b))?(a):(b))
#define GT_ABS(a)      (((a)>=0)?(a):(-(a)))
#define GT_SGN(a)      (((a)>=0)?(1):(-1))
#define GT_PI          3.141592653589793238462
#define GT_IMAGING_GEOMETRY_DELTA 0.001
#define GT_MKINT(a)    (((a)>=0)?((int)((a)+0.5)):((int)((a)-0.5)))
#define GT_SQR(a)      ((a)*(a))

#endif  //GADGETRONCOMMON_H
