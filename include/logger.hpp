#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
class Logger {
public:
  void info(const char *message);
  void info(const char *message, std::initializer_list<const char*> list);

  void warn(const char *message);
  void warn(const char *message, std::initializer_list<const char *> list);

  void error(const char *message);
  void error(const char *message, std::initializer_list<const char *> list);

  void critical(const char *message);
  void critical(const char *message, std::initializer_list<const char *> list);

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
