// File: main.cpp
#include <iostream>
#include <NFLogging.h>
#include <array>
#include <random>
#include <thread>
#include <chrono>
#include <vector>

#include <NFLoggingCommon.h>
#include <NFLogging.h>
#include <NFLogCategoryManager.h>
#include <NFLogCategory.h>
#include <NFLogMessage.h>


// Logging function that will print log messages
static void logFunctionImplementation(const nf::log::LogCategory *category,
                                      const nf::log::LogMessage * message)
{
  std::cout << category->getName() << " -  | " << message->getMessage() << std::endl;
}

// Function for each thread to execute logging operations
void logRandomMessages(const std::array<std::string, 10> &namesArray, int threadId)
{
  std::random_device rd;
  std::mt19937       mt(rd());

  int levelIndex    = 0;
  int categoryIndex = 0;

  // Start the logging loop for 3 seconds
  const auto start_time = std::chrono::steady_clock::now();
  int        total      = 0;

  while (std::chrono::steady_clock::now() - start_time < std::chrono::seconds(3))
  {
    categoryIndex = std::uniform_int_distribution<int>(0, 9)(mt);
    levelIndex    = std::uniform_int_distribution<int>(0, 2)(mt);

    float timeLeftInSeconds = std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::seconds(3) - (std::chrono::steady_clock::now() - start_time)
      ).count();

    std::string msgTime = "Time left: " + std::to_string(timeLeftInSeconds);
    std::string msg     = "Thread " + std::to_string(threadId) + " | Random message | " + msgTime;
    nf::log::log(namesArray[categoryIndex].c_str(),
                 static_cast<nf::log::LogLevel>(levelIndex),
                 msg.c_str());
    total++;
  }
}

#include <NFLogging.h>

int main()
{
  // Initialize the logging system with the custom log function
  init(logFunctionImplementation);

  // Predefined category names
  static auto namesArray = std::array<std::string, 10>{
    "AAA", "BBB", "CCC", "DDD", "EEE", "FFF", "GGG", "HHH", "III", "JJJ"
  };

  // Register categories
  std::string initialName = "topper";
  nf::log::log(initialName.c_str(), nf::log::LogLevel::Info, "Registering categories");

  for (const auto &name : namesArray)
  {
    nf::log::log(name.c_str(), nf::log::LogLevel::Info,
                 ("Registering category: " + name).c_str());
  }

  // Create multiple threads to simulate concurrent logging
  const int numThreads = 4;

  std::vector<std::thread> threads;

  auto start_time = std::chrono::steady_clock::now();

  threads.reserve(numThreads);
  for (int i = 0; i < numThreads; ++i)
  {
    threads.emplace_back(logRandomMessages, std::cref(namesArray), i);
  }


  // Wait for all threads to finish
  for (auto &thread : threads)
  {
    thread.join();
  }

  // Log the total run information
  const auto end_time = std::chrono::steady_clock::now();
  nf::log::log("topper", nf::log::LogLevel::Info, "All threads have finished running");

  nf::log::log("topper", nf::log::LogLevel::Info,
               ("Total time taken: " + std::to_string(std::chrono::duration_cast<std::chrono::seconds>(
                 end_time - start_time).count()) + " seconds").c_str());

  // Shutdown the logging s
  nf::log::shutDown();

  return 0;
}
