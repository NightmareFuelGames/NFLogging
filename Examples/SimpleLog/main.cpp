//
// Created by User on 21/09/2024.
//

#include <iostream>
#include <NFLogging.h>

static void logFunctionImplementation(const NFLOG_MSG& entry)
{
	std::cout << entry.category->name << " | " << entry.getMessage() << std::endl;
}

int main()
{
	NFLOG_NS::setLoggingFunction(logFunctionImplementation);
	static NFLOG_CAT coreCategory("CORE");
	NFLOG_NS::info(coreCategory.name, "Hello World!");

	for (int i = 0; i < 10; i++)
	{
		NFLOG_NS::info(coreCategory.name, "Hello World! " + std::to_string(i));
	}

	return 0;
}
