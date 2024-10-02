#pragma once


#ifdef NFLOG_EXPORTS
#if defined(_MSC_VER)
#define NFLOG_API __declspec(dllexport) // Microsoft
#elif defined(__GNUC__)
#define NFLOG_API __attribute__((visibility("default"))) // GCC#endif
#endif
#else
#if defined(_MSC_VER)
#define NFLOG_API __declspec(dllimport) // Microsoft
#elif defined(__GNUC__)
#define NFLOG_API __attribute__((visibility("default"))) // GCC#endif
#endif
#endif

#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif
#include <cstdarg>
#include <string>

////typedefss
namespace nf::log
{
  struct LogCategory;
  struct LogMessage;
};

typedef void (*LogFunctionPtr)(
  const nf::log::LogCategory* category,
  const nf::log::LogMessage*  message);

/******************************************************************************
 *  Logging Macros
 ******************************************************************************/

#define NF_LOG_NAMESPACE_STR "NF"
#define NF_LOG_NAMESPACE_SEP "::"

#define NF_LOG_MANAGER_NAME "LOGMANAGER"

//////
//Create namespace like this: NF_LOG_CREATE_NAMESPACE_A("MyNamespace", "MySubNamespace")
//This will create a namespace like this: NF::MyNamespace::MySubNamespace::test

#define NF_LOG_CREATE_NAMESPACE_INTERNAL(outstring, ...) \
  do { \
    std::string temp; \
    const std::string tempArray[] = {__VA_ARGS__}; \
    for (const auto &str : tempArray) \
    { \
      temp = str; \
      outstring += NF_LOG_NAMESPACE_SEP; \
      outstring += temp; \
    } \
  } while (0)


#define NF_LOG_CREATE_NAMESPACE(outstring, ...) \
  do { \
    outstring = NF_LOG_NAMESPACE_STR; \
    NF_LOG_CREATE_NAMESPACE_INTERNAL(outstring, __VA_ARGS__); \
  } while (0)

