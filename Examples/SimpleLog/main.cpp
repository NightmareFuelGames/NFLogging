// File: main.cpp
#include <iostream>
#include <NFLogging.h>
#include <array>
#include <random>
#include <thread>


static void logFunctionImplementation(
  const nf::log::LogCategory *cat, const nf::log::LogMessage *message)
{
  std::cout << cat->getName() << " - " << nf::log::levelToString(message->level)
    << " | " << message->message << std::endl;
}

int main()
{
  static auto namesArray =
    std::array<std::string, 10>{
      "AAA",
      "BBB",
      "CCC",
      "DDD",
      "EEE",
      "FFF",
      "GGG",
      "HHH",
      "III",
      "JJJ"
    };

  init(logFunctionImplementation);

  for (auto &name : namesArray)
  {
    nf::log::log(name, "One run to register all. | Register World! | nf::log::LogLevel::Info", nf::log::LogLevel::Info);
  }


  auto val = std::random_device();
  auto mt  = std::mt19937(val());

  int levelIndex    = 0;
  int categoryIndex = 0;
  // Record the start time
  const auto start_time = std::chrono::steady_clock::now();
  int        total      = 0;
  // Run the loop for 10 minutes (600 seconds)
  while (std::chrono::steady_clock::now() -
    start_time < std::chrono::seconds(3))
  {
    categoryIndex = std::uniform_int_distribution<int>(0, 8)(mt);
    levelIndex    = std::uniform_int_distribution<int>(0, 3)(mt);

    float timeleftInSeconds = std::chrono::duration_cast<std::chrono::seconds>(
        std::chrono::seconds(3) - (std::chrono::steady_clock::now() - start_time))
      .count();

    std::string msgTime = "time left: " + std::to_string(timeleftInSeconds);

    std::string msg = "Random message | Time: " + msgTime;
    switch (levelIndex)
    {
    case 0:
      nf::log::log(namesArray[categoryIndex], msg,
                   nf::log::LogLevel::Info);
      break;
    case 1:
      nf::log::log(namesArray[categoryIndex], msg,
                   nf::log::LogLevel::Warning);
      break;
    case 2:
      nf::log::log(namesArray[categoryIndex], msg,
                   nf::log::LogLevel::Error);
      break;
    default:
      nf::log::log(namesArray[categoryIndex], msg,
                   nf::log::LogLevel::Info);
      break;
    }

    total++;
    /*std::this_thread::sleep_for(std::chrono::milliseconds(100));*/
  }
  nf::log::info("StartTime: " + std::to_string(start_time.time_since_epoch().count()));
  nf::log::info("EndTime: " + std::to_string(std::chrono::steady_clock::now().time_since_epoch().count()));
  nf::log::info("Total: " + std::to_string(total));
  nf::log::info("Shutting down now: " + std::to_string(total));
  nf::log::shutDown();
  return 0;
}
