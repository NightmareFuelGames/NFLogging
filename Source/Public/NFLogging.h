//
// Created by User on 21/09/2024.
//

#ifndef NFLOGGING_H
#define NFLOGGING_H
#include "NFLoggingCommon.h"

#include <future>
#include <string>
#include <utility>

#define NF_DEFAULT_LOG_PRF "NightmareLog"
#define NF_DEFAULT_LOG_SFX ""
#define NF_DEFAULT_LOG_CATEGORY "CORE"

NFLOG_NS_DEC
{
  extern LogFunctionPtr NFLOG_API G_LogFunction;
  enum class Level
  {
    Info = 0,
    Warning = 1,
    Error = 2
  };

  struct LogCategory
  {
    std::string name;

    explicit LogCategory(std::string name) : name(std::move(name))
    {
    }
  };

  struct LogMessage
  {
    std::shared_ptr<std::string> message;
    NFLOG_LVL level;
    std::shared_ptr<NFLOG_CAT> category;

    explicit LogMessage(
      const std::string& message,
      const NFLOG_LVL level,
      const std::shared_ptr<NFLOG_CAT>& category
    ) : level(level), category(category)
    {
      this->message = std::make_shared<std::string>(message);
    }
  };

  // Use NFLOG_API for all functions and global variables
  NFLOG_API const std::string& levelToString(Level level);
  void NFLOG_API setLoggingFunction(LogFunctionPtr logFunc);
  void NFLOG_API log(const std::string& categoryName, const std::string& message, Level level);

  void NFLOG_API info(const std::string& categoryName, const std::string& message);
  void NFLOG_API info(const std::string& message);

  void NFLOG_API warn(const std::string& categoryName, const std::string& message);
  void NFLOG_API warn(const std::string& message);

  void NFLOG_API error(const std::string& categoryName, const std::string& message);
  void NFLOG_API error(const std::string& message);


};

#endif //NFLOGGING_H
