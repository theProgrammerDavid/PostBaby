#pragma once
#include "constants.hpp"
#include "imgui.h"
#include "imgui_stdlib.h"
#include "tab.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class GUI {

private:
  std::vector<Tab> tabs;
  int active_tab;
  std::string active_response;

  ImGuiTableFlags workspaceTableFlags;
  ImGuiWindowFlags windowFlags;

  void HelpMarker(const char *desc);

  void responseArea();
  void workspaceArea();
  void workspaceBar();
  void tabConfig();
  void centerModal();

  void settingsPopup();

  void drawBody();
  void drawKeyValueDesc(std::vector<KeyValuePair> &vec);

public:
  void render();
  GUI();
};
