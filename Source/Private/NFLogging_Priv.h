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
// Created by User on 02/10/2024.
//

#ifndef NFLOGGING_PRIV_H
#define NFLOGGING_PRIV_H

namespace nf::log
{
  void callGlobalLogFunction_Implementation(const LogCategory &category,
                                            const LogMessage & message);
}
#endif //NFLOGGING_PRIV_H
