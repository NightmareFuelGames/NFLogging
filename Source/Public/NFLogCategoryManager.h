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

#ifndef NFLOGCATEGORYMANAGER_H
#define NFLOGCATEGORYMANAGER_H

#include <NFLogCategory.h>
#include <map>

namespace nf::log
{
  struct LogCategoryManager
  {
    LogCategoryManager() = default;

    static LogCategoryManager* getInstance()
    {
      if (m_Instance != nullptr)
      {
        m_Instance = new LogCategoryManager();
        m_Instance->init();
      }
      return m_Instance;
    }

    void shutDown();

    [[nodiscard]] static NFLOG_API LogCategory* getCoreCategory();
    [[nodiscard]] static NFLOG_API LogCategory* getTempCategory();

    // Register a new category
    std::shared_ptr<LogCategory> registerCategory(const char* name);
    bool                         registerCategory(const std::shared_ptr<LogCategory>& category);

    // Get a category by name
    std::shared_ptr<LogCategory> getCategoryByName(const char* name);

  private:
    /**/

    // Shutdown the LogCategoryManager


    bool                                                init();
    std::map<const char*, std::shared_ptr<LogCategory>> m_subCategories = {}; // All registered categories
  private:
    static LogCategoryManager* m_Instance;
  };
}


#endif // NFLOGCATEGORYMANAGER_H
