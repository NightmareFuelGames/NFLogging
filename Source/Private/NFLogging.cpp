/******************************************************************************
 *  Copyright (C) 2024- by Nightmare Fuel Games                               *
 *                                                                            *
 *  Permission to use, copy, modify, and distribute this software and         *
 *   its documentation under the terms of the GNU General Public License is   *
 *   hereby granted.                                                          *
 *                                                                            *
 *  No representations are made about the suitability of this software        *
 *  for any purpose.                                                          *
 *  It is provided "as is" without express or implied warranty.               *
 *                                                                            *
 *  See the GNU General Public License for more details.                      *
 ******************************************************************************/

#include "NFLogging.h"
#include <iostream>
#include <mutex>

#include "NFLogMessage.h"
#include "NFLogLevel.h"


#include <NFLogCategory.h>
#include <NFLogCategoryManager.h>

namespace nf::log
{
  LogFunctionPtr      G_LogFunction                  = nullptr;
  LogCategoryManager *LogCategoryManager::m_Instance = nullptr;
  static bool         initialized                    = false;

  void init(LogFunctionPtr logFunc)
  {
    if (initialized) { return; }
    G_LogFunction = logFunc;

    LogCategoryManager::m_Instance = new LogCategoryManager();

    LogCategoryManager::m_Instance->registerCategory("Core");
    LogCategoryManager::m_Instance->registerCategory("Temp");
    initialized = true;
  }

  void shutDown()
  {
    if (LogCategoryManager::m_Instance != nullptr)
    {
      LogCategoryManager::m_Instance->shutDown();
      delete LogCategoryManager::m_Instance;
      LogCategoryManager::m_Instance = nullptr;
    }
  }

  void callGlobalLogFunction(const std::shared_ptr<LogCategory> &category, const std::shared_ptr<LogMessage> &message)
  {
    if (G_LogFunction != nullptr)
    {
      G_LogFunction(category.get(), message.get());
    }
    else
    {
      std::cout
        << std::string()
        << category->c_Name
        << std::string(" | ")
        << message->getMessage()
        << std::endl;
    }
  }

  /*void log(
    std::string *category,
    LogLevel     level,
    std::string *message)
  {
    /*td::string categoryString = *category; ///<---here is the error
    std::string messageString  = *message;

    log(categoryString, level, messageString);void#1#
  }*/

  void log(const char *category, LogLevel level, const char *message) noexcept
  {
    static std::mutex m_mutex;
    //lock
    std::lock_guard<std::mutex> lock(m_mutex);

    if
    (
      !
      initialized
    )
    {
      return;
    }

    const auto logCategory =
      LogCategoryManager::m_Instance->getCategoryByName(category);
    const auto logMessage = std::make_shared<LogMessage>(message, level);

    logCategory
      ->
      addLogMessage(logMessage);
    callGlobalLogFunction(logCategory, logMessage);
  }

  /*void log(std::string category,
           LogLevel    level,
           std::string message
    ) {}*/

  /*void log(std::shared_ptr<std::string> category,
           LogLevel                     level,
           std::shared_ptr<std::string> message
    )
  {
    std::string categoryString(*category);

    LogCategory *logCategory = LogCategoryManager::m_Instance->getCategoryByName(categoryString).get();
    LogMessage * logMessage  = new LogMessage(*message, level);

    callGlobalLogFunction(logCategory, logMessage);
  }*/ // namespace nf::log

  /////////////////////////////////////////////////////
  // Deprecated functions
  /////////////////////////////////////////////////////
  /*
  void logImpl(
    //@formatter:off
    LogCategory* category, const char* message,
    const LogLevel level, const bool checkIfCategoryIsRegistered = true
    //@formatter:on
    )
  {
    if (checkIfCategoryIsRegistered) {} //todo: implement

    if (G_LogFunction != nullptr)
    {
      G_LogFunction(category, new LogMessage(message, level));
    }
    else
    {
      std::cout << levelToString(level)
        << " | "
        << category->m_Name
        << std::string(" | ")
        << message
        << std::endl;
    }
  }


  /**
   * @deprecated this is a deprecated function and should not be used. Use the log function that takes a category instead.
   * @param _cat
   * @param message
   * @param level
   #1#
  void logImpl(const std::string &_cat,
               const std::string &message,
               const LogLevel     level)
  {
    if (_cat.empty() || message.empty())
    {
      std::string errorMessage =
        "Category name is empty. Can't log message.";
      error("NFLogging", errorMessage);
      return;
    }


  }


  void loggingImpl(LogCategory *category, const char *message, LogLevel level)
  {
    logImpl(category, message, level);
  }

  void loggingImpl(const char *categoryName, const char *message, LogLevel level)
  {
    logImpl(categoryName, message, level);
  }

  void info(const std::string &message) {}

  void info(const std::string &categoryName, const std::string &message)
  {
    loggingImpl(categoryName.c_str(), message.c_str(), LogLevel::Info);
  }

  void warn(const std::string &categoryName, const std::string &message)
  {
    loggingImpl(categoryName.c_str(), message.c_str(), LogLevel::Warning);
  }

  void error(const std::string &categoryName, const std::string &message)
  {
    loggingImpl(categoryName.c_str(), message.c_str(), LogLevel::Error);
  }
  */

}
