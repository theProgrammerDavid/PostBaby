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

    void responseArea();
    void workspaceArea();
    void workspaceBar();
    void tabConfig();
    void centerModal();

    void settingsPopup();

    void drawParams();
    void drawHeaders();

public:
    void render();
    GUI();
};
 