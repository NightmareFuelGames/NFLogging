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

#include "NFLogging.h"
#include <iostream>
#include <mutex>

#include "NFLogMessage.h"
#include "NFLogLevel.h"


#include <NFLogCategory.h>
#include <NFLogCategoryManager.h>

namespace nf::log {
  LogFunctionPtr      G_LogFunction                  = nullptr;
  LogCategoryManager *LogCategoryManager::m_Instance = nullptr;
  static bool         initialized                    = false;

void init(LogFunctionPtr logFunc) {
  if (LogCategoryManager::initialized) { return; }
  G_LogFunction                  = logFunc;
  LogCategoryManager::m_Instance = new LogCategoryManager();
  LogCategoryManager::getInstance()->registerCategory("Core");
  LogCategoryManager::getInstance()->registerCategory("Temp");
  LogCategoryManager::initialized = true;
}

void shutDown() {
  LogCategoryManager::getInstance()->shutDown();
}

void callGlobalLogFunction(const std::shared_ptr<LogCategory> &category,
                           const std::shared_ptr<LogMessage> & message) {
  if (G_LogFunction != nullptr) {
    G_LogFunction(category.get(), message.get());
  } else {
    std::cout
        << std::string()
        << category->getName()
        << std::string(" | ")
        << message->getMessage()
        << std::endl;
  }
}

void log(const char *category, LogLevel level, const char *message) noexcept {
  static std::mutex m_mutex;
  //lock
  std::lock_guard lock(m_mutex);

  if (!LogCategoryManager::initialized) {
    return;
  }

  const auto logCategory = LogCategoryManager::getInstance()->
      getCategoryByName(category);
  const auto logMessage = std::make_shared<LogMessage>(message, level);

  logCategory->addLogMessage(logMessage);
  callGlobalLogFunction(logCategory, logMessage);
}

}
