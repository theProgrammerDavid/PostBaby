#pragma once
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>
class Logger
{
public:
  /**
 * @param message message to log to info
 * */
  void info(const char *message);

  /**
 * @param message message to log to info
 * @param list additional C strings to log
 * */
  void info(const char *message, std::initializer_list<const char *> list);

  /**
 * @param message message to log to warn
 * */
  void warn(const char *message);

  /**
 * @param message message to log to warn
 * @param list additional C strings to log
 * */
  void warn(const char *message, std::initializer_list<const char *> list);

  /**
 * @param message message to log to error
 * */
  void error(const char *message);

  /**
 * @param message message to log to error
 * @param list additional C strings to log
 * */
  void error(const char *message, std::initializer_list<const char *> list);

  /**
 * @param message message to log to critical
 * */
  void critical(const char *message);

  /**
 * @param message message to log to critical
 * @param list additional C strings to log
 * */
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
