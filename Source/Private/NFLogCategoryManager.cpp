#include "NFLogCategoryManager.h"
#include <iostream>
#include <memory>
#include <mutex>

namespace nf::log
{
  std::shared_ptr<LogCategory> LogCategoryManager::registerCategory(const char *name)
  {
    std::shared_ptr<LogCategory> cat = getCategoryByName(name);
    if (!cat)
    {
      cat                           = std::make_shared<LogCategory>(name);
      allRegisteredCategories[name] = cat;
    }
    return cat;
  }

  //void LogCategoryManager::sendLogCoreCategory(const std::string &message, LogLevel level) {}
  //void LogCategoryManager::sendLogTempCategory(const std::string &message, LogLevel level) {}

  std::shared_ptr<LogCategory> LogCategoryManager::getCategoryByName(const char *name)
  {
    if (allRegisteredCategories.empty())
    {
      if (auto it = allRegisteredCategories.find(name); it != allRegisteredCategories.end())
      {
        return it->second;
      }
    }

    allRegisteredCategories[name] = std::make_shared<LogCategory>(name);
    return allRegisteredCategories[name]; // Return nullptr if not found
  }

  void LogCategoryManager::shutDown()
  {
    allRegisteredCategories.clear();
  }

  LogCategory *LogCategoryManager::getTempCategory()
  {
    return allRegisteredCategories["Temp"].get();
  }

  LogCategory *LogCategoryManager::getCoreCategory()
  {
    return allRegisteredCategories["Core"].get();
  }

  /*
  void LogCategoryManager::sendLogCoreCategory(const char *message, LogLevel level)
  {
    LogCategory *coreCategory = getCoreCategory();
    LogMessage * logMessage   = new LogMessage(message, level);

    coreCategory->addLogMessage(logMessage);
  }


  void LogCategoryManager::sendLogTempCategory(const std::string &message, LogLevel level)
  {
    LogCategory *tempCategory = getTempCategory();
    LogMessage * logMessage   = new LogMessage(message, level);

    tempCategory->addLogMessage(logMessage);
  }


g
  LogCategory *LogCategoryManager::getCategoryByName(const std::string &name)
  {

  }#1#

  LogCategoryManager::~LogCategoryManager()
  {
    shutDown();
  }

  LogCategoryManager &LogCategoryManager::getInstance()
  {
    static LogCategoryManager instance; // Thread-safe in C++11 and later
    return instance;
  }

  /*
  void LogCategoryManager::shutDown()
  {
    #1#

  LogCategory *LogCategoryManager::getCoreCategory()
  {
    // Static members initialization
    static LogCategory *NFLogCoreCategory = new LogCategory("CORE");
    return NFLogCoreCategory;
  }

  LogCategory *LogCategoryManager::getTempCategory()
  {
    static LogCategory *NFLogTempCategory = new LogCategory("TEMP");
    return NFLogTempCategory;
  }
  */


}
