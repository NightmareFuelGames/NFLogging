#pragma once

// #if defined(_WIN32) || defined(__CYGWIN__)
// #define NFLOG_CALL/* __stdcall*/
// #else
// #define NFLOG_CALL
// #endif
//

/*
  Library import helpers
*/

/*
#ifdef NFLOG_EXPORTS
  #define NFLOG_API __declspec(dllexport)
#else
#define NFLOG_API __declspec(dllimport)
#endif*/

#if defined(_WIN32) || defined(__CYGWIN__)
#define NFLOG_CALL __stdcall
#else
#define NFLOG_CALL
#endif

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__ORBIS__) || defined(F_USE_DECLSPEC)
#define NFLOG_EXPORT __declspec(dllexport)
#elif defined(__APPLE__) || defined(__ANDROID__) || defined(__linux__) || defined(F_USE_ATTRIBUTE)
#define NFLOG_EXPORT __attribute__((visibility("default")))
#else
  #define NFLOG_EXPORT
#endif


#ifdef NFLOG_EXPORTS
#define NFLOG_API NFLOG_EXPORT NFLOG_CALL
#else
#define NFLOG_API NFLOG_CALL
#endif

#define NFLOG_TCHAR wchar_t

#define NFLOG_LOG_PREFIX "[Nightmare]"
#define NFLOG_CAT_SEP_O  "["
#define NFLOG_CAT_SEP_C  "]"

#ifndef FORCEINLINE
#if (_MSC_VER >= 1200)
#define FORCEINLINE __forceinline
#else
#define FORCEINLINE __inline
#endif
#endif
