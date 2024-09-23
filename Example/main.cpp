//
// Created by User on 21/09/2024.
//

#include <iostream>
#include <NFLogging.h>

static void logFunction(const char* message, nf::logging::Level level)
{

	// Implement your own logging function here
	// For example, you could write to a file or to the console
	// You could also use a library like spdlog or boost.log
	// For now, we'll just print to the console
	switch (level)
	{
	case nf::logging::Level::Info:
		std::cout << "Info: " << message << std::endl;
		break;
	case nf::logging::Level::Warning:
		std::cout << "Warning: " << message << std::endl;
		break;
	case nf::logging::Level::Error:
		std::cout << "Error: " << message << std::endl;
		break;
	}
}

int main()
{

	nf::logging::info("Hello, World!");
	nf::logging::warning("This is a warning!");
	nf::logging::error("This is an error!");

	nf::logging::info("Hello, World!");
	nf::logging::warning("This is a warning!");
	nf::logging::error("This is an error!");

	nf::logging::info("Hello, World!");
	nf::logging::warning("This is a warning!");
	nf::logging::error("This is an error!");

	nf::logging::setLoggingFunction(logFunction);
	nf::logging::info("Hello, World!");
	nf::logging::warning("This is a warning!");
	nf::logging::error("This is an error!");
	return 0;
}
