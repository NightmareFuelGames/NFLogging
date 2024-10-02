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

#include <NFLogCategoryManager.h>
#include <iostream>

namespace nf::log {
bool LogCategory::init() {
  return true;
}

LogCategory::~LogCategory() {
  //std::cout << "LogCategory::~LogCategory() " << c_Name << std::endl;
}

void LogCategory::log(const char *message, LogLevel level) {
  /*auto category = self();*/
  LogCategoryManager::getInstance()->registerCategory(shared_from_this());
}

void LogCategory::addLogMessage(const std::shared_ptr<LogMessage> &logMessage) {
  m_logMessages.push_back(logMessage);
}


/**
 *
 * @return Construct namespace string without own name
 */
std::string LogCategory::constructNameSpace() const noexcept
// NOLINT(*-no-recursion)
{
  if (m_parent == nullptr) {
    return getName();
  } else {
    const std::string parentName = m_parent->getName();
    const std::string nameSpace  = parentName + "." + c_Name;
    return nameSpace;
  }
}


}
