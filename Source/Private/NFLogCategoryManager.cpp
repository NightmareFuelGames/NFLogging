#include "NFLogCategoryManager.h"

#include <NFLogCategory.h>
#include <memory>

namespace nf::log
{
  bool LogCategoryManager::init()
  {
    if (m_Instance == nullptr)
    {
      m_Instance = new LogCategoryManager();
      return true;
    }
    return false;
  }

  std::shared_ptr<LogCategory> LogCategoryManager::registerCategory(const char *name)
  {
    std::shared_ptr<LogCategory> cat = getCategoryByName(name);
    if (m_Instance == nullptr)
    {
      init();
    }

    if (!cat)
    {
      m_subCategories[name] = std::make_shared<LogCategory>(name);
    }
    return cat;
  }

  bool LogCategoryManager::registerCategory(const std::shared_ptr<LogCategory> &category
    )
  {
    std::shared_ptr<LogCategory> cat = getCategoryByName(category->getName());
    if (!cat)
    {
      m_subCategories[category->getName()] = category;
      return true;
    }

    return false;
  }

  std::shared_ptr<LogCategory> LogCategoryManager::getCategoryByName(
    const char *name)
  {
    if (m_Instance == nullptr)
    {
      init();
      return m_Instance->getCategoryByName(name);
    }

    if (name == nullptr)
    {
      return nullptr;
    }
    auto it = m_subCategories.find(name);
    if (it != m_subCategories.end())
    {
      return it->second;
    }
    m_subCategories[name] = std::make_shared<LogCategory>(name);
    return m_subCategories[name];
  }

  void LogCategoryManager::shutDown()
  {
    m_subCategories.clear();
  }

  LogCategory *LogCategoryManager::getTempCategory()
  {
    return LogCategoryManager::m_Instance->m_subCategories["Temp"].get();
  }

}
