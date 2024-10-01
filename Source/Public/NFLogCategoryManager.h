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
    LogCategoryManager()  = default; // Declaration (already in your header)
    ~LogCategoryManager() = default; // Declaration (already in your header)

    // Shutdown the LogCategoryManager
    void shutDown();

    // Get predefined categories
    [[nodiscard]] LogCategory*           getCoreCategory();
    [[nodiscard]] NFLOG_API LogCategory* getTempCategory();

    // Register a new category
    std::shared_ptr<LogCategory> registerCategory(const char* name);

    // Get a category by name
    std::shared_ptr<LogCategory> getCategoryByName(const char* name);

  private:
    // All registered categories
    std::map<const char*, std::shared_ptr<LogCategory>> allRegisteredCategories = {};

  public:
    static LogCategoryManager* m_Instance;
  };
}


#endif // NFLOGCATEGORYMANAGER_H
