#include "NFLogCategoryManager.h"

#include <NFLogging.h>
#include "NFLogCategory.h"

#include <NFLoggingCore.h>

namespace nf::log
{
  static LogCategory *NFLogCoreCategory = new LogCategory("CORE");
  static LogCategory *NFLogTempCategory = new LogCategory("TEMP");

  LogCategoryManager::~LogCategoryManager() {}

  LogCategory *LogCategoryManager::getCategoryChecked(const std::string &name)
  {
    if (const auto foundCat = getCategoryPtr(name); foundCat != nullptr)
    {
      return foundCat;
    }
    else
    {
      return registerCategory(name);
    }
  }

  LogCategory *LogCategoryManager::getCategoryPtr(const std::string &name)
  {
    if (name == "CORE")
    {
      return NFLogCoreCategory;
    }

    if (name == "TEMP")
    {
      return NFLogTempCategory;
    }

    if (allRegisteredCategories.find(name) == allRegisteredCategories.end())
    {
      return nullptr;
    }

    return allRegisteredCategories.at(name);
  }

  LogCategory &LogCategoryManager::getCategoryOrTemp(const std::string &name)
  {
    if (isCategoryRegistered(name))
    {
      return *getCategoryPtr(name);
    }

    return *NFLogTempCategory;
  }

  LogCategoryManager &LogCategoryManager::getInstance()
  {
    // Ensuring thread safety for Singleton initialization
    std::lock_guard lock(mutex);

    static LogCategoryManager *instance;
    if (instance == nullptr)
    {
      instance = new LogCategoryManager();
    }

    return *instance;
  }

  void LogCategoryManager::shutDown()
  {
    core::logImpl(NFLogCoreCategory, "Shutting down category manager. deleting all category objects.",
                  LogLevel::Info);

    for (auto &[name, category] : getInstance().allRegisteredCategories)
    {
      delete category;
    }

    core::logImpl(NFLogCoreCategory, "Deleting temp category", LogLevel::Info);
    core::logImpl(NFLogCoreCategory, "Deleting core category", LogLevel::Info);
    delete NFLogTempCategory;
    delete NFLogCoreCategory;

    delete &getInstance();
  }

  bool LogCategoryManager::isCategoryRegistered(const LogCategory *category) const
  {
    return isCategoryRegistered(category->m_Name);
  }

  LogCategory *LogCategoryManager::getCoreCategory()
  {
    return NFLogCoreCategory;
  }

  LogCategory *LogCategoryManager::getTempCategory()
  {
    return NFLogTempCategory;
  }

  void LogCategoryManager::sendCoreCategory(const std::string &msg,
                                            const LogLevel     level)
  {
    core::logImpl(NFLogCoreCategory, msg, level);
  }

  LogCategory *LogCategoryManager::registerCategory(const std::string &name)
  {
    core::logImpl(NFLogCoreCategory, "Trying to register category: " + name, LogLevel::Info);

    LogCategory *category = getCategoryPtr(name);
    if (category != nullptr)
    {
      core::logImpl(NFLogCoreCategory,
                    "Category %s is already registered. Can't register again. Returning registered category",
                    LogLevel::Error);
      return category;
    }

    //actually register the category
    category = new LogCategory(name);
    registerCategory(category);

    return category;
  }

  LogCategory *LogCategoryManager::registerCategory(LogCategory *category)
  {
    if (auto *foundCategory = getCategoryPtr(category->m_Name); foundCategory != nullptr)
    {
      core::logImpl(NFLogCoreCategory, "Category name " + category->m_Name + " already registered." +
                    "returning the found category and !DELETING! the category given as the parameter",
                    LogLevel::Error);
      delete category; //delete the category that was passed in, and replace its pointer with the found category
      category = foundCategory;

    }

    allRegisteredCategories[category->m_Name] = (category);
    return category;
  }

}
