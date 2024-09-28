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

#include <map>
#include <string>

#include <mutex>  // To make thread-safe in case of multithreading
#include <NFLogging.h>

namespace nf::log
{
  struct LogCategory;


  struct LogCategoryManager
  {
  private:
    // Private constructor to prevent instantiation
    LogCategoryManager() = default;

    // Declare destructor
    ~LogCategoryManager();

    // Delete copy constructor and assignment operator
    LogCategoryManager(const LogCategoryManager&)            = delete;
    LogCategoryManager& operator=(const LogCategoryManager&) = delete;

    // Map of all registered log categories
    std::map<std::string, LogCategory*> allRegisteredCategories = {};

    // Mutex to ensure thread safety if needed
    inline static std::mutex mutex;

  public:
    static LogCategoryManager& getInstance();

    static void shutDown();

    static LogCategory* getCoreCategory();
    static LogCategory* getTempCategory();

    static void sendCoreCategory(const std::string& msg,
                                 LogLevel           level);

    // Public methods remain the same
    bool isCategoryRegistered(const std::string& name) const
    {
      std::lock_guard<std::mutex> lock(mutex);
      return allRegisteredCategories.find(name) != allRegisteredCategories.end();
    }

    bool isCategoryRegistered(const LogCategory* category) const;

    LogCategory* registerCategory(const std::string& name);
    LogCategory* registerCategory(LogCategory* category);

    LogCategory* getCategoryPtr(const std::string& name);
    LogCategory* getCategoryChecked(const std::string& name);

    LogCategory& getCategoryOrTemp(const std::string& name);
  };
}

#endif // NFLOGCATEGORYMANAGER_H
