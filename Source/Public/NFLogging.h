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

  /*NFLOG_API FORCEINLINE void log(std::string* category,
                                 LogLevel     level,
                                 std::string* message);

  NFLOG_API FORCEINLINE void log(std::string category,
                                 LogLevel    level,
                                 std::string message);*/

  /*
  FORCEINLINE void NFLOG_API log(std::shared_ptr<std::string> category,
                                 LogLevel                     level,
                                 std::shared_ptr<std::string> message);
                                 */

  /*void NFLOG_API levelToString(LogLevel level);*/
};

#endif // NFLOGGING_H
