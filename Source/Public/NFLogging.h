#ifndef NFLOGGING_H
#define NFLOGGING_H

#include <NFLogLevel.h>

#include "NFLoggingCommon.h"

#include "NFLogCategory.h"

namespace nf::log
{
  extern LogFunctionPtr G_LogFunction;

  NFLOG_API void init(LogFunctionPtr logFunc);

  NFLOG_API void shutDown();

  NFLOG_API void log(const char *category, LogLevel level, const char *message) noexcept;

};

#endif // NFLOGGING_H
