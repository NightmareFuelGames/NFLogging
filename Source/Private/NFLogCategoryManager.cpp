#include "NFLogCategoryManager.h"
#include <memory>
#include <mutex>

namespace nf::log
{
  std::shared_ptr<LogCategory> LogCategoryManager::registerCategory(const char *name)
  {
    std::shared_ptr<LogCategory> cat = getCategoryByName(name);
    if (!cat)
    {
      allRegisteredCategories[name] = std::make_shared<LogCategory>(name);
    }
    return cat;
  }

  //void LogCategoryManager::sendLogCoreCategory(const std::string &message, LogLevel level) {}
  //void LogCategoryManager::sendLogTempCategory(const std::string &message, LogLevel level) {}

  std::shared_ptr<LogCategory> LogCategoryManager::getCategoryByName(const char *name)
  {
    auto it = allRegisteredCategories.find(name);
    if (it != allRegisteredCategories.end())
    {
      return it->second;
    }
    allRegisteredCategories[name] = std::make_shared<LogCategory>(name);
    return allRegisteredCategories[name];
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
}
