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

#include <string>
#include <NFLoggingCommon.h>
#include <map>
#include <vector>

namespace nf::log
{
  struct LogMessage;
}

namespace nf::log
{
  struct NFLOG_EXPORT LogCategory
  {
    friend struct LogCategoryManager;

  public:
    explicit LogCategory(std::string name)
      : m_Name(std::move(name))
    {
    }

    ~LogCategory();

    [[nodiscard]] std::string getName() const
    {
      return std::string(
          NFLOG_LOG_PREFIX) /*[Nightmare][*/
        + NFLOG_CAT_SEP_O /*[*/
        + m_Name /*category name*/
        + NFLOG_CAT_SEP_C; /*]*/
    }

    std::vector<LogMessage*> getLogMessages() const
    {
      return m_logMessages;
    }

    void addLogMessage(LogMessage* logMessage)
    {
      m_logMessages.push_back(logMessage);
    }

    /*void addMessage(LogMessage* msg);
    */

  private:
    std::vector<LogMessage*> m_logMessages = {};
    const std::string        m_Name;
  };
}
#endif //LOGCATEGORY_H
