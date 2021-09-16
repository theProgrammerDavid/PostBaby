#include "logger.hpp"

void Logger::critical(const char *message) { this->logger->critical(message); }
void Logger::warn(const char *message) { this->logger->warn(message); }
void Logger::info(const char *message) { this->logger->info(message); }
void Logger::error(const char *message) { this->logger->error(message); }

Logger::Logger() {
#if _WIN32
   logger =
      spdlog::basic_logger_mt("PostBabyLogger",
      std::string(getenv("AppData")) + "\\PostBaby\\PostBaby.log") );
#else
  logger = spdlog::basic_logger_mt("PostBabyLogger",
                                   std::string(getenv("HOME")) +
                                       "/.config/PostBaby/PostBaby.log");

#endif
}
std::atomic<Logger *> Logger::instance;
std::mutex Logger::myMutex;

Logger *Logger::getInstance() {
  Logger *sin = instance.load(std::memory_order_acquire);
  if (!sin) {
    std::lock_guard<std::mutex> myLock(myMutex);
    sin = instance.load(std::memory_order_relaxed);
    if (!sin) {
      sin = new Logger();
      instance.store(sin, std::memory_order_release);
    }
  }
  // volatile int dummy{};
  return sin;
}