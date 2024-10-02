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
#include <mutex>

#include "NFLogMessage.h"
#include "NFLogLevel.h"

#include <NFLogCategory.h>
#include <NFLogCategoryManager.h>
#include <iostream>

namespace nf::log
{
  LogFunctionPtr      G_LogFunction                  = nullptr;
  LogCategoryManager *LogCategoryManager::m_Instance = nullptr;

  void callGlobalLogFunction_Implementation(const LogCategory &category,
                                            const LogMessage & message)
  {
    if (G_LogFunction)
    {
      G_LogFunction(category, message);
    }
    else
    {
      std::cout << "**No log function set**" << "[" << category.getName() << "] - " << message.getMessage() <<
        std::endl;
    }
  }

  void init(const LogFunctionPtr logFunc)
  {
    G_LogFunction = logFunc;
    LogCategoryManager::getInstance()->registerCategory("Core");
    LogCategoryManager::getInstance()->registerCategory("Temp");
  }

  void shutDown()
  {
    LogCategoryManager::getInstance()->shutDown();
  }

  void log(const char *category, LogLevel level, const char *message) noexcept
  {
    //mutex
    static std::mutex m_mutex;
    //lock
    std::lock_guard lock(m_mutex);

    static bool initialized = false;
    if (!initialized)
    {
      init([](const LogCategory &cat, const LogMessage &msg) -> void
        {
          std::cout << cat.getName() << " | " << msg.getMessage() << std::endl;
        }
        );
    }

    const auto logCategory =
      LogCategoryManager::getInstance()->getCategoryByName(category);
    logCategory->log(message, level);
  }

}
