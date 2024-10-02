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


#include "NFLogCategory.h"
#include <NFLogMessage.h>
#include <NFLogging_Priv.h>
#include <iostream>

namespace nf::log
{
  LogCategory::~LogCategory() {}

  void LogCategory::log(const char *message, LogLevel level)
  {
    const auto logMessage = std::make_shared<LogMessage>(message, level);
    addLogMessage(logMessage);
    callGlobalLogFunction_Implementation(*this, *logMessage);
  }

  void LogCategory::addLogMessage(const std::shared_ptr<LogMessage> &logMessage)
  {
    m_logMessages.push_back(logMessage);
  }

  std::string LogCategory::constructNameSpace() const noexcept
  {
    if (m_parent == nullptr)
    {
      return getName();
    }

    const std::string parentName = m_parent->getName();
    const std::string nameSpace  = parentName + "." + c_Name;
    return nameSpace;
  }


}
