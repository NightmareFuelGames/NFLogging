#ifndef NFLOGGING_H
#define NFLOGGING_H

#include <NFLoggingCommon.h>

namespace nf::log
{
  enum class LogLevel;

  NFLOG_API void init(LogFunctionPtr logFunc);

  NFLOG_API void shutDown();

  NFLOG_API void log(const char *category, LogLevel level, const char *message) noexcept;

};

#endif // NFLOGGING_H
