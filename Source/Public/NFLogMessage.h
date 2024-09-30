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
// Created by User on 29/09/2024.
//

#ifndef NFLOGMESSAGE_H
#define NFLOGMESSAGE_H

#include <string>

#include <NFLogLevel.h>

namespace nf::log
{
  struct LogMessage
  {
    explicit LogMessage(const char* message, LogLevel level)
      : level(level),
        message(message)
    {
    }

    [[nodiscard]] const char* getMessage() const
    {
      return message.c_str();
    }

    const LogLevel level;

  private:
    const std::string message;
  };
} // namespace nf::log

#endif //NFLOGMESSAGE_H
