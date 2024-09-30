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

////typedefss
namespace nf::log
{
  struct LogCategory;
  struct LogMessage;
};

typedef void (*LogFunctionPtr)(
  const nf::log::LogCategory* category,
  const nf::log::LogMessage*  message);

////TEXT
#define NFLOG_TCHAR wchar_t
#define NFLOG_LOG_PREFIX "[Nightmare]"
#define NFLOG_CAT_SEP_O  "["
#define NFLOG_CAT_SEP_C  "]"

