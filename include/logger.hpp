#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
// class Logger {
// public:
//   void info(const char *message);
//   void warn(const char *message);
//   void error(const char *message);
//   void critical(const char *message);
//   Logger();

// private:
//   std::shared_ptr<spdlog::logger> logger;
// };

class Logger {
public:
  void info(const char *message);
  void warn(const char *message);
  void error(const char *message);
  void critical(const char *message);

  static Logger *getInstance();

private:
  Logger();
  ~Logger() = default;
  Logger(const Logger &) = delete;
  Logger &operator=(const Logger &) = delete;

  static std::atomic<Logger *> instance;
  static std::mutex myMutex;

  std::shared_ptr<spdlog::logger> logger;
};
