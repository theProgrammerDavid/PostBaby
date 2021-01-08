#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "imgui.h"
#include "tab.hpp"
#include "constants.hpp"


// extern Constants *constants;
extern std::unique_ptr<Constants> constants;

class GUI
{

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

    void drawParams();
    void drawBody();
    void drawKeyValueDesc(std::vector<KeyValuePair>& vec);

public:
    void render();
    GUI();
};
 