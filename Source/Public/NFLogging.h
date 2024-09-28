#ifndef NFLOGGING_H
#define NFLOGGING_H

#include "NFLoggingCommon.h"

#include "NFLogCategory.h"

#include <future>
#include <string>
#include <utility>

// #include "spdlog/details/os-inl.h"

namespace nf::log
{
  enum class LogLevel
  {
    Info    = 0,
    Warning = 1,
    Error   = 2
  };

  struct NFLOG_EXPORT LogMessage
  {
    const std::string message;
    const LogLevel    level;

    LogMessage(std::string message, const LogLevel level)
      : message(std::move(message)),
        level(level)
    {
    }

    [[nodiscard]] std::string string() const
    {
      return message;
    }
  };

  typedef void (*                    LogFunctionPtr)(const LogCategory* LogCategory, const LogMessage* message);
  extern LogFunctionPtr NFLOG_EXPORT G_LogFunction;

  void NFLOG_API init(LogFunctionPtr logFunc);
  void NFLOG_API shutDown();


  // Use NFLOG_API for all functions and global variables
  // NFLOG_API


  std::string NFLOG_API levelToString(LogLevel level);
  void NFLOG_API        setLoggingFunction(LogFunctionPtr logFunc);

  //\ brief Log a message with a category
  //\ param category The category of the message
  /*** Log functions ***/
#ifdef log
#define log_backup log
#undef log
#endif
  void NFLOG_API log(LogCategory* category, const std::string& message, LogLevel level);
  void NFLOG_API log(const std::string& categoryName, const std::string& message, LogLevel level);
  /* void NFLOG_API log(const std::string& parentCategoryName,
                                   const std::string& categoryName,
                                   const std::string&
                                   message, LogLevel level);*/
  void NFLOG_API log(const std::string& message, LogLevel level);
#ifdef log_backup
#define log log_backup
#undef log_backup
#endif

#ifdef info
#define info_backup info
#undef info
#endif
  void NFLOG_API info(const std::string& categoryName, const std::string& message);
  void NFLOG_API info(const std::string& message);
#ifdef log_backup
#define info log_backup
#undef log_backup
#endif

#ifdef warn
#define warn_backup warn
#undef warn
#endif
  void NFLOG_API warn(const std::string& categoryName, const std::string& message);
  void NFLOG_API warn(const std::string& message);
#ifdef warn_backup
#define warn warn_backup
#undef warn_backup
#endif

#ifdef error
#define error_backup error
#undef error
#endif
  void NFLOG_API error(const std::string& categoryName, const std::string& message);
  void NFLOG_API error(const std::string& message);
#ifdef error_backup
#define error error_backup
#undef error_backup
#endif
};

#endif //NFLOGGING_H
