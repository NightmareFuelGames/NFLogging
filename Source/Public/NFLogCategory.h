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
#include <vector>
#include <memory>

#include <NFLoggingCommon.h>

namespace nf::log
{
  struct LogCategory
  {
    friend struct LogCategoryManager;

  public:
    explicit LogCategory(const char* name)
      : c_Name(name)
    {
    }

    ~LogCategory();

    [[nodiscard]] const char* getName() const
    {
      return c_Name;
    }

    std::vector<std::shared_ptr<LogMessage>> getLogMessages() const
    {
      return m_logMessages;
    }

    void addLogMessage(const std::shared_ptr<LogMessage>& logMessage);

    const char* c_Name;

  private:
    std::vector<std::shared_ptr<LogMessage>> m_logMessages = {};
  };
}
#endif //LOGCATEGORY_H
