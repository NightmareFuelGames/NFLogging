#include "NFLoggingCommon.h"

#include "NFLogging.h"

#include <iostream>
#include <map>

NFLOG_NS_DEC
{
	// Initialize the function pointer to null
	LogFunctionPtr G_LogFunction = nullptr;

	static void logSendToOutput(const LogMessage& message)
	{
		// Log the message
		if (G_LogFunction)
		{
			G_LogFunction(message);
		}
		else
		{
			// Fallback, if no log function is set (e.g., log to console or discard)
			std::cout << "No Log IMPLEMENTATION SET | " << message.message << std::endl;
		}
	}

	static std::string getDefaultCategoryName()
	{
		return NF_DEFAULT_LOG_PRF + std::string(" | ") + NF_DEFAULT_LOG_CATEGORY + std::string(" | ") +
			NF_DEFAULT_LOG_SFX;
	}

	static std::string getCategoryName(const std::string& cat)
	{
		bool addPrefix = false;
		bool addSuffix = false;

		if (cat.empty())
		{
			return getDefaultCategoryName();
		}

		if (cat.find(NF_DEFAULT_LOG_PRF) == std::string::npos)
		{
			addPrefix = true;
		}

		if (cat.find(NF_DEFAULT_LOG_SFX) == std::string::npos)
		{
			addSuffix = true;
		}

		std::string result = cat;

		if (addPrefix)
		{
			result = NF_DEFAULT_LOG_PRF + std::string(" | ") + result;
		}

		if (addSuffix)
		{
			result = result + std::string(" | ") + NF_DEFAULT_LOG_SFX;
		}

		return result;
	}

	inline static std::map<std::string, std::shared_ptr<LogCategory>> categoryMap = {
		{ getDefaultCategoryName(), std::make_shared<LogCategory>(getDefaultCategoryName()) } // Default category
	};


	void setLoggingFunction(const LogFunctionPtr logFunc)
	{
		G_LogFunction = logFunc;
	}

	const std::string& levelToString(const Level level)
	{
		static std::string unkown = "!UNKOWN! LEVEL";
		static std::string info = "Info   ";
		static std::string warning = "Warning";
		static std::string error = "Error  ";

		switch (level)
		{
		case Level::Info:
			return info;
		case Level::Warning:
			return warning;
		case Level::Error:
			return error;
		default:
			return unkown;
		}
	}

	static void logImpl(const std::string& _cat, const std::string& message, const Level level)
	{
		std::string cat = getCategoryName(_cat);
		std::shared_ptr<LogCategory> category = categoryMap[cat];
		if (!category)
		{
			category = std::make_shared<LogCategory>(cat);
			categoryMap[cat] = category;
		}

		const LogMessage msg(message, level, category);
		logSendToOutput(msg);
	}

	void log(const std::string& categoryName, const std::string& message, Level level)
	{
		logImpl(categoryName, message, level);
	}

	void info(const std::string& categoryName, const std::string& message)
	{
		logImpl(categoryName, message, Level::Info);
	}

	void info(const std::string& message)
	{
		info(getDefaultCategoryName(), message);
	}


	void warn(const std::string& message)
	{
		warn(getDefaultCategoryName(), message);
	}

	void warn(const std::string& categoryName, const std::string& message)
	{
		logImpl(categoryName, message, Level::Warning);
	}

	void error(const std::string& categoryName, const std::string& message)
	{
		logImpl(categoryName, message, Level::Error);
	}

	void error(const std::string& message)
	{
		error(getDefaultCategoryName(), message);
	}


}