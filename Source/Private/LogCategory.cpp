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

#include <NFLoggingCore.h>
#include <iostream>

#include "NFLogCategory.h"

namespace nf::log
{
  LogCategory::~LogCategory()
  {
    const uint8_t total = m_logMessages.size();

    for (const LogMessage *msg : m_logMessages)
    {
      delete msg;
    };

    const std::string
      msg;
    const LogMessage *logMessage = new LogMessage(
      ("Deleted " + std::to_string(total) + " log messages. -" + m_Name),
      LogLevel::Info
      );
    core::logImpl(this, logMessage);
    delete logMessage;
  }

  /*void LogCategory::addMessage(LogMessage *msg)
  {
    m_logMessages.push_back(msg);
  }*/
}
