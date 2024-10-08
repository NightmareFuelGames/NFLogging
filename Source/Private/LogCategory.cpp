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

namespace nf::log
{

  LogCategory::~LogCategory() {}

  void LogCategory::addLogMessage(const std::shared_ptr<LogMessage> &logMessage)
  {
    m_logMessages.push_back(logMessage);
  }


}
