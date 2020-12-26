#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "imgui.h"
#include "tab.hpp"
#include "constants.hpp"
#include "threadPool.hpp"

extern Constants *constants;

class GUI
{

private:
    std::vector<Tab> tabs;
    int active_tab;
    std::string active_response;

    void responseArea();
    void workspaceArea();
    void settingsArea();
    void workspaceBar();

    void settingsPopup();

public:
    void render();
    GUI();
};

extern ThreadPool pool;