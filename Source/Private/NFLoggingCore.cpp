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

#include "NFLoggingCore.h"

#include <NFLogCategoryManager.h>
#include <iostream>
#include "NFLogCategory.h"
#include "NFLogging.h"

namespace nf::log::core
{
  void logImpl(std::string message, const LogLevel level)
  {
    auto *category = LogCategoryManager::getCoreCategory();
    logImpl(category, std::move(message), level);
  }

  void logImpl(LogCategory *category, std::string message, LogLevel level)
  {
    const LogMessage *logMessage = new LogMessage(std::move(message), level);
    logImpl(category, logMessage);
  }

  void logImpl(LogCategory *category, const LogMessage *message)
  {
    if (G_LogFunction != nullptr)
    {
      G_LogFunction(category, message);
      category->addLogMessage(const_cast<LogMessage *>(message));
    }
    else
    {
      std::cout << message->message << std::endl;
    }
  }
}
