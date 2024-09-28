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

#include <NFLogCategoryManager.h>
#include <iostream>
#include "NFLogCategory.h"

namespace nf::log
{
  LogFunctionPtr G_LogFunction = nullptr;

  inline void setLoggingFunction(const LogFunctionPtr logFunc)
  {
    G_LogFunction = logFunc;
  }

  /*
  const static LogCategory* GetLogCategory(const std::string& name)
  {
    return allRegisteredCategories[name];
  }
  */

  void init(const LogFunctionPtr logFunc)
  {
    setLoggingFunction(logFunc);
  }

  void shutDown()
  {
    LogCategoryManager::shutDown();
  }

  /////////////////////////////////////////////////////
  std::string levelToString(const LogLevel level)
  {
    const static std::string unkown  = "!UNKOWN! LEVEL";
    const static std::string info    = "Info   ";
    const static std::string warning = "Warning";
    const static std::string error   = "Error  ";

    switch (level)
    {
    case LogLevel::Info:
      return info;
    case LogLevel::Warning:
      return warning;
    case LogLevel::Error:
      return error;
    }
    return unkown;
  }

  void logImpl(
    //@formatter:off
    LogCategory *category, const std::string& message,
    const LogLevel level, const bool checkIfCategoryIsRegistered = true
    //@formatter:on
    )
  {
    if (category == nullptr)
    {
      return;
    }

    if (checkIfCategoryIsRegistered) {} //todo: implement

    if (G_LogFunction != nullptr)
    {
      LogMessage *msg = new LogMessage(message, level);
      G_LogFunction(category, msg);
      category->addLogMessage(msg);
    }
    else
    {
      std::cout << levelToString(level)
        << " | "
        << category->getName()
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
   */
  void logImpl(const std::string &_cat,
               const std::string &message,
               const LogLevel     level)
  {
    if (_cat.empty())
    {
      LogCategoryManager::sendCoreCategory(
        "Category name is empty, logging (" +
        (message.length() > 4)
        ? message.substr(0, 4)
        : message +
        ") to the temp category", LogLevel::Error);

      logImpl(LogCategoryManager::getTempCategory(), message, level);
      return;
    }

    logImpl(LogCategoryManager::getInstance().getCategoryChecked(_cat), message, level);
  }

  void log(LogCategory *category, const std::string &message, const LogLevel level)
  {
    logImpl(category, message, level);
  }

  void log(const std::string &categoryName, const std::string &message, const LogLevel level)
  {
    logImpl(categoryName, message, level);
  }

  /*void log(const std::string &parentCategoryName, const std::string &categoryName, const std::string &message,
           const LogLevel     level)
  {
    logImpl(parentCategoryName + NFLOG_CAT_SEP_O + categoryName + NFLOG_CAT_SEP_C, message, level);
  }
  */

  void log(const std::string &message, const LogLevel level)
  {
    //log to temp category
    logImpl(LogCategoryManager::getTempCategory(), message, level);
  }

  void info(const std::string &categoryName, const std::string &message)
  {
    log(categoryName, message, LogLevel::Info);
  }

  void info(const std::string &message)
  {
    log(message, LogLevel::Info);
  }

  void warn(const std::string &message)
  {
    log(message, LogLevel::Warning);
  }

  void warn(const std::string &categoryName, const std::string &message)
  {
    log(categoryName, message, LogLevel::Warning);
  }

  void error(const std::string &categoryName, const std::string &message)
  {
    log(categoryName, message, LogLevel::Error);
  }

  void error(const std::string &message)
  {
    log(message, LogLevel::Error);
  }


}
