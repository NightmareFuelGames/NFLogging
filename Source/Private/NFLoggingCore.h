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

//
// Created by User on 27/09/2024.
//

#ifndef NFLOGGINGCORE_H
#define NFLOGGINGCORE_H

#include "NFLogging.h"

namespace nf::log::core
{
  void logImpl(std::string message, LogLevel level);
  void logImpl(LogCategory* category, std::string message, LogLevel level);
  void logImpl(LogCategory* category, const LogMessage* message);
}

#endif //NFLOGGINGCORE_H
