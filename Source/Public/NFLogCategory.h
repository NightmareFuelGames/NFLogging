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


#ifndef LOGCATEGORY_H
#define LOGCATEGORY_H

#include <map>
#include <string>
#include <utility>
#include <vector>
#include <memory>

#include <NFLoggingCommon.h>
#include <NFLogLevel.h>

namespace nf::log
{
  struct NFLOG_API LogCategory
  {
    friend struct LogCategoryManager;

  public:
    explicit LogCategory(const char* name)
      : c_Name(name)
    {
      if (name == nullptr)
      {
        c_Name = "NULL";
      }

      if (name == NF_LOG_MANAGER_NAME)
      {
        c_Namespace = constructNameSpace();
        return;
      }
    }

    virtual ~LogCategory();

  public :
    void log(const char* message, LogLevel level);
    void info(const char* message) { log(message, LogLevel::Info); }
    void warn(const char* message) { log(message, LogLevel::Warning); }
    void error(const char* message) { log(message, LogLevel::Error); }

    [[nodiscard]]

    const char* getNamespace() const
    {
      return c_Namespace.c_str();
    }

    [[nodiscard]] const char* getName() const
    {
      return c_Name;
    }

    std::vector<std::shared_ptr<LogMessage>>& getLogMessages()
    {
      return m_logMessages;
    }

    void addLogMessage(const std::shared_ptr<LogMessage>& logMessage);
    /*void addSubCategory(const std::shared_ptr<LogCategory>& subCategory);*/

  private:
    std::string constructNameSpace() const noexcept;

    const char* c_Name;
    std::string c_Namespace;

    std::shared_ptr<LogCategory> m_parent = nullptr;

    std::vector<std::shared_ptr<LogMessage>> m_logMessages = {};
    /*todo: implement subcategories
    std::map<const char*, std::shared_ptr<LogCategory>> m_subCategories = {};
    */
  };
}
#endif //LOGCATEGORY_H
