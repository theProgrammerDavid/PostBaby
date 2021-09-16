#pragma once
#include "logger.hpp"
#include "config.hpp"
#include "database.hpp"
#include "imgui.h"
#include "util.hpp"
#include <cpr/cprtypes.h>
#include <cpr/ssl_options.h>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#ifdef _Win32
#include <Windows.h>
#endif
using namespace cpr;

void glfw_error_callback(int error, const char *description);

class Constants {
private:
  std::string workingDir;
  std::string configFilePath;
  std::string iniFilePath;
  std::string dbFilePath;
  std::string logFilePath;
  ImGuiWindowFlags windowFlags;
  ImGuiTableFlags tableFlags;
  YAML::Node config;
  template <class T>
  void writeToFile(std::ofstream &fout, const char *key, const T &value);

public:
  ImGuiWindowFlags getWindowFlags();
  ImGuiTableFlags getTableFlags();
  Database *db;
  void writeConfig();
  void updateWindowFlags();

  const char *getWorkingDir();
  const char *getConfigFilePath();
  const char *getIniFilePath();
  const char *getLogFilePath();

  void defaultValues();
  void createConfigFile();
  bool configFileExists();
  void setOnlineStatus(bool status);
  Constants();
  enum { DARK, LIGHT, CLASSIC };

  void setTheme();
  int MAX_URL_SIZE;
  SslOptions sslOpts;
  int REQUEST_TIMEOUT;
  int WINDOW_WIDTH;
  int WINDOW_HEIGHT;
  int CURRENT_THEME;
  float FONT_SIZE;
  bool configError;
  bool moveWindow;
  bool htmlIndent;
  bool jsonIndent;
  bool isOnline;
  std::string PATH_TO_FONT;
  float highDPIscaleFactor;

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  const char *REQUEST_TYPE[6] = {"GET",    "POST", "PUT",
                                 "DELETE", "HEAD", "OPTIONS"};
  const char *THEMES[3] = {"DARK", "LIGHT", "CLASSIC"};
  ImVec4 TEMP_BG_COLOR = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  /* Static access method. */
  // static Constants* getInstance();
};
inline std::unique_ptr<Constants> constants{new Constants()};