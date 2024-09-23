//
// Created by User on 23/09/2024.
//

#pragma once

/*
	Library import helpers
*/
#if defined(_WIN32) || defined(__CYGWIN__)
	#define NFLOG_CALL/* __stdcall*/
#else
	#define NFLOG_CALL
#endif

/*
#if defined(_WIN32) || defined(__CYGWIN__) || defined(__ORBIS__) || defined(NFLOG_USE_DECLSPEC)
	#define NFLOG_EXPORT __declspec(dllexport)
#elif defined(__APPLE__) || defined(__ANDROID__) || defined(__linux__) || defined(NFLOG_USE_ATTRIBUTE)
	#define NFLOG_EXPORT __attribute__((visibility("default")))
#else
	#define NFLOG_EXPORT
#endif
*/

/*
#ifdef NFLOGEXPORTS
	#define NFLOG_API NFLOG_EXPORT NFLOG_CALL
#else
	#define NFLOG_API NFLOG_CALL
#endif
*/

#ifdef NFLOG_EXPORTS
	#define NFLOG_API __declspec(dllexport)
#else
	#define NFLOG_API __declspec(dllimport)
#endif


#define NFLOG_LVL NFLOG_NS::Level
#define NFLOG_CAT NFLOG_NS::LogCategory
#define NFLOG_MSG NFLOG_NS::LogMessage

#ifndef NFLOG_NS
#define NFLOG_NS nf::log
#define NFLOG_NS_DEC namespace NFLOG_NS
#endif

namespace nf::log {
	struct LogMessage;
}
typedef void (*LogFunctionPtr)(const NFLOG_MSG& message);

#define NFLOG_TCHAR wchar_t

