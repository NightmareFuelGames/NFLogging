//
// Created by User on 24/09/2024.
//

#pragma once

#include <NFLoggingCommon.h>
#include <NFLogging.h>

#include <NFLogCategory.h>
#include <NFLogMacros.h>
#include <NFLogging.h>
#include <NFLoggingCommon.h>

#define NF_DEFINE_LOG_STATIC(Category) \
namespace NFLOG_NS \
{ \
static struct Category##Log : public nf::log::LogCategory { \
__forceinline Category##Log() : nf::log::LogCategory(#Category) { \
} \
} ##Category##_Log; \
}
