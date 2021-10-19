#pragma once
#include "constants.hpp"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "tab.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "types.hpp"
#include "fonts.hpp"
#include "threadPool.hpp"
class GUI {

private:
  std::vector<Tab> tabs;
  std::vector<request> history;
  int active_tab;
  std::string active_response;
  std::unique_ptr<FontManager> fontManager;

  ImGuiTableFlags workspaceTableFlags;
  ImGuiWindowFlags windowFlags;

  void HelpMarker(const char *desc);

  void responseArea();
  void workspaceArea();
  void workspaceBar();
  void tabConfig();
  void centerModal();

  void settingsPopup();
  void historyPopup();
  void drawBody();
  void drawKeyValueDesc(std::vector<KeyValuePair> &vec);

public:
  void render();
  void setFont(const std::unique_ptr<FontManager> );
  GUI();
  ~GUI();
};
