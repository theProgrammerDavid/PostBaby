#include "gui.hpp"

GUI::GUI() {
  // workspaceTableFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
  // ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable |
  // ImGuiTableFlags_ScrollY | ImGuiTableFlags_ScrollX; windowFlags =
  // ImGuiWindowFlags_NoTitleBar;
  constants->db->getHistory(history);
  active_tab = 0;
  active_response = "";
  Tab t(tabs.size() + 1);
  tabs.push_back(t);
  Tab t2(tabs.size() + 1);
  tabs.push_back(t2);
}

GUI::~GUI(){
}

void GUI::responseArea() {
  if (tabs[active_tab].getStatusCode() > 0) {
    ImGui::Text("Code:%d", tabs[active_tab].getStatusCode());
    ImGui::SameLine();
  }

  if (tabs[active_tab].getTimeElapsed() > 0) {
    ImGui::Text("Time: %f s", tabs[active_tab].getTimeElapsed());
  }

  if (ImGui::BeginTabBar("ResponseBar")) {
    if (ImGui::BeginTabItem("Body")) {
      ImGuiWindowFlags response_flags = ImGuiWindowFlags_HorizontalScrollbar;
      ImGui::BeginChild("ResponseBar",
                        ImVec2(ImGui::GetWindowContentRegionWidth(),
                               ImGui::GetWindowHeight()),
                        false, response_flags);
      ImGui::InputTextMultiline("##ResponseBody", &active_response,
                                ImVec2(ImGui::GetWindowContentRegionWidth(),
                                       ImGui::GetWindowHeight()));
      ImGui::EndChild();
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Headers")) {
      const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
      ImVec2 WorkspaceTableSize = ImVec2(-FLT_MIN, TEXT_BASE_HEIGHT * 10);
      if (ImGui::BeginTable("Response Headers", 2, constants->getTableFlags(),
                            WorkspaceTableSize)) {

        ImGui::TableSetupColumn("Key");
        ImGui::TableSetupColumn("Value");

        ImGui::TableHeadersRow();

        int count = 0;
        for (auto i : tabs[active_tab].res.header) {
          ImGui::TableNextRow();

          ImGui::TableSetColumnIndex(0);
          ImGui::PushID(0);
          ImGui::Text("%s", i.first.c_str());
          ImGui::PopID();

          count++;

          ImGui::TableSetColumnIndex(1);
          ImGui::PushID(1);
          ImGui::Text("%s", i.second.c_str());
          ImGui::PopID();
        }
        ImGui::EndTable();
      }
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Cookies")) {
      const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
      ImVec2 WorkspaceTableSize = ImVec2(-FLT_MIN, TEXT_BASE_HEIGHT * 10);

      if (ImGui::BeginTable("Cookies", 2, constants->getTableFlags(),
                            WorkspaceTableSize)) {

        ImGui::TableSetupColumn("Key");
        ImGui::TableSetupColumn("Value");

        ImGui::TableHeadersRow();

        for (auto i : tabs[active_tab].res.cookies) {
          ImGui::TableNextRow();

          ImGui::TableSetColumnIndex(0);
          ImGui::PushID(0);
          ImGui::Text("%s", i.first.c_str());
          ImGui::PopID();

          ImGui::TableSetColumnIndex(1);
          ImGui::PushID(1);
          ImGui::Text("%s", i.second.c_str());
          ImGui::PopID();
        }
        ImGui::EndTable();
      }
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
  }
}

void GUI::workspaceBar() {
  if (ImGui::Button("Preferences")) {
    ImGui::OpenPopup("Edit Preferences");
  }
  this->settingsPopup();
  ImGui::SameLine();
  if (ImGui::Button("History")) {
    ImGui::OpenPopup("History");
  }
  this->historyPopup();
  ImGui::SameLine();
  ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1fFPS",
                     ImGui::GetIO().Framerate);
  ImGui::SameLine();
  if (constants->isOnline) {
    ImGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "Online");
  } else {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Offline");
  }
  ImGui::SameLine();
  if (constants->configError) {
    ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Config Error");
  }
}

void GUI::historyPopup(){

  

  const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
  ImVec2 WorkspaceTableSize = ImVec2(FLT_MAX, TEXT_BASE_HEIGHT * 8);
  centerModal();

  ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x * 0.5f,
                                  ImGui::GetIO().DisplaySize.y * 0.5f));

  if (ImGui::BeginPopupModal("History", NULL,
                             ImGuiWindowFlags_AlwaysAutoResize)) {

    ImGui::Text("Changes will be saved automatically");
    ImGui::Text("Total: %d", history.size());

    if(ImGui::Button("Reload")){
      constants->db->getHistory(history);
    }
    ImGui::Separator();

    ImGui::BeginTable("##HistoryTable", 3,
                      ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders |
                          ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable,
                      WorkspaceTableSize);

    ImGui::TableSetupColumn("No.", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("Method");
    ImGui::TableSetupColumn("URL");

    ImGui::TableHeadersRow();
    for (size_t row = 0; row < history.size(); row++) {
      ImGui::TableNextRow();

      ImGui::TableSetColumnIndex(0);
      ImGui::PushID(row);
      // ImGui::Text("%d", history[row].id);
      ImGui::Text("%d", row+1);
      ImGui::SameLine();
      if (ImGui::Button("Load")) {
        tabs[active_tab].loadTabFromHistory(history[row]);
      }
      ImGui::SameLine();
      if(ImGui::Button("Del")){
        std::thread delRow([&]{
            history.erase(history.begin()+row);
            constants->db->deleteRow(history[row].id);
        });
        delRow.detach();  
      }
      ImGui::PopID();

      ImGui::TableSetColumnIndex(1);
      ImGui::PushID(row);
      ImGui::Text("%s", getHttpMethod(history[row].method));
      ImGui::PopID();

      ImGui::TableSetColumnIndex(2);
      ImGui::PushID(row);
      ImGui::Text("%s", history[row].url.c_str());

      ImGui::PopID();
    }
    ImGui::EndTable();
    ImGui::Separator();
    if (ImGui::Button("Close")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::SetItemDefaultFocus();
    
    
    ImGui::EndPopup();
  }
}

void GUI::setFont(std::unique_ptr<FontManager> fontManager){
  this->fontManager = std::move(fontManager);
}

void GUI::settingsPopup() {
  const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
  ImVec2 WorkspaceTableSize = ImVec2(FLT_MAX, TEXT_BASE_HEIGHT * 8);
  centerModal();

  if (ImGui::BeginPopupModal("Edit Preferences", NULL,
                             ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Changes will be saved automatically");
    ImGui::Separator();
    
    
    if(ImGui::TreeNode("Font")){

       if(ImGui::BeginListBox("Font")){

          for(const auto i:this->fontManager->fonts){
            const bool isSelected = this->fontManager->selectedFont == i.first;

            if(ImGui::Selectable(i.first.c_str(), isSelected)){
              this->fontManager->selectedFont = i.first;
            }

            if(isSelected){
              ImGui::SetItemDefaultFocus();
            }
          }
        ImGui::EndListBox();
      }
    }

    ImGui::Separator();
    if(ImGui::TreeNode("General")){      
      ImGui::InputInt("Window Width", &constants->WINDOW_WIDTH);
      ImGui::InputInt("Window Height", &constants->WINDOW_HEIGHT);

      ImGui::InputFloat("Font Size", &constants->FONT_SIZE);
      ImGui::SameLine();
      HelpMarker("Changes to font size will take effect after restart");

      ImGui::Separator();

      ImGui::InputInt("URL Max Size", &constants->MAX_URL_SIZE);
      ImGui::InputInt("Request Timeout (ms)", &constants->REQUEST_TIMEOUT);
      ImGui::Checkbox("Moveable Window", &constants->moveWindow);
      ImGui::Checkbox("HTML Indent", &constants->htmlIndent);
      ImGui::Checkbox("JSON Indent", &constants->jsonIndent);
    }

    //  THEMES
    ImGui::Separator();
    // ImGui::Text("Theme");
    if(ImGui::TreeNode("Themes")){
        if (ImGui::BeginCombo("Theme",
                            constants->THEMES[constants->CURRENT_THEME])) {
        for (int n = 0; n < IM_ARRAYSIZE(constants->THEMES); n++) {
          const bool is_selected = (constants->CURRENT_THEME == n);
          if (ImGui::Selectable(constants->THEMES[n], is_selected))
            constants->CURRENT_THEME = n;

          // Set the initial focus when opening the combo (scrolling + keyboard
          // navigation focus)
          if (is_selected)
            ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
      }
      ImGui::ColorEdit3("Background", (float *)&constants->clear_color);
    }
    // THEMES
    ImGui::Separator();
    if (ImGui::Button("OK", ImVec2(120, 0))) {
      constants->updateWindowFlags();
      constants->setTheme();
      constants->setFontPath(fontManager->getPathToSelectedFont());

      // constants->clear_color = constants->TEMP_BG_COLOR;
      ImGui::CloseCurrentPopup();
      std::thread t([&] { constants->writeConfig(); });
      t.detach();
    }
    ImGui::SetItemDefaultFocus();
    ImGui::SameLine();
    if (ImGui::Button("Cancel", ImVec2(120, 0))) {
      constants->TEMP_BG_COLOR = constants->clear_color;
      ImGui::CloseCurrentPopup();
    }
    ImGui::SameLine();
    if (ImGui::Button("Reset")) {
      std::thread t([&] {
        constants->defaultValues();
        constants->createConfigFile();
      });
      t.detach();
    }
    ImGui::SameLine();
    HelpMarker("\"OK\" saves changes\n\"Cancel\" discards changes.\n\"Reset\" "
               "resets config file to defaults");
    ImGui::EndPopup();
  }
}

void GUI::centerModal() {
  ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f,
                ImGui::GetIO().DisplaySize.y * 0.5f);
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void GUI::HelpMarker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::IsItemHovered()) {
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

void GUI::drawKeyValueDesc(std::vector<KeyValuePair> &vec) {
  const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
  ImVec2 WorkspaceTableSize = ImVec2(-FLT_MIN, TEXT_BASE_HEIGHT * 8);

  if (ImGui::BeginTable("##table1", 5, constants->getTableFlags(),
                        WorkspaceTableSize)) {

    ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed);
    ImGui::TableSetupColumn("Key");
    ImGui::TableSetupColumn("Value");
    ImGui::TableSetupColumn("Description");
    ImGui::TableSetupColumn("Del", ImGuiTableColumnFlags_WidthFixed);

    ImGui::TableHeadersRow();

    for (size_t row = 0; row < vec.size(); row++) {
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::PushID(row);
      ImGui::Checkbox("", &vec[row].enable);
      ImGui::PopID();

      ImGui::TableSetColumnIndex(1);
      ImGui::PushID(vec[row]._id);

      ImGui::InputText("##Key", &vec[row].key);

      ImGui::SameLine();
      // if (ImGui::Button("Clear"))
      // {
      //     vec[row].setKey("");
      // }
      ImGui::PopID();

      ImGui::TableSetColumnIndex(2);
      ImGui::PushID(vec[row]._id);
      ImGui::InputText("##Value", &vec[row].value);
      ImGui::PopID();

      ImGui::TableSetColumnIndex(3);
      ImGui::PushID(vec[row]._id);
      ImGui::InputText("##Description", &vec[row].description);
      ImGui::PopID();

      ImGui::TableSetColumnIndex(4);

      ImGui::PushID(row);
      if (ImGui::Button("X")) {
        vec.erase(vec.begin() + row);
      }
      ImGui::PopID();
    }
    ImGui::EndTable();
    if (ImGui::Button("+")) {
      KeyValuePair kvp;
      vec.push_back(kvp);
    }
  }
}

void GUI::drawBody() {

  if (tabs[active_tab].getBodyType() == tabs[active_tab].BODY_NONE) {
    ImGui::Text("HTTP request does not have a Body");
  } else if (tabs[active_tab].getBodyType() ==
             tabs[active_tab].BODY_URL_ENCODED) {
    ImGui::Text("URL encoded");
    drawKeyValueDesc(tabs[active_tab].urlParams);
  } else if (tabs[active_tab].getBodyType() ==
             tabs[active_tab].BODY_FORM_DATA) {
    ImGui::Text("Form Data");
    drawKeyValueDesc(tabs[active_tab].formData);
  } else if (tabs[active_tab].getBodyType() == tabs[active_tab].BODY_RAW) {
    ImGui::Text("Raw Body");
    ImGui::SameLine();
    HelpMarker("Ctrl+Enter for newline. Only JSON is supported for now");

    ImGui::InputTextMultiline(" ", &tabs[active_tab].rawBody, ImVec2(1200, 200),
                              ImGuiInputTextFlags_AllowTabInput |
                                  ImGuiInputTextFlags_CtrlEnterForNewLine);
  } else if (tabs[active_tab].getBodyType() == tabs[active_tab].BODY_BINARY) {
    ImGui::Text("WIP Binary Body");
  } else {
    ImGui::Text("WIP GraphQl Body");
  }
}

void GUI::tabConfig() {
  if (ImGui::BeginTabBar("TabItemConfig")) {
    if (ImGui::BeginTabItem("Params")) {
      // drawParams();
      drawKeyValueDesc(tabs[active_tab].queryParams);
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Authorization")) {
      ImGui::Text("WIP Authorization");

      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Headers")) {
      ImGui::Text("HTTP Headers");
      drawKeyValueDesc(tabs[active_tab].headers);
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Body")) {
      ImGui::NewLine();
      if (ImGui::Button("None")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_NONE;
      }
      ImGui::SameLine();

      if (ImGui::Button("Url Encoded")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_URL_ENCODED;
      }
      ImGui::SameLine();
      if (ImGui::Button("Form Data")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_FORM_DATA;
      }
      ImGui::SameLine();
      if (ImGui::Button("Raw")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_RAW;
      }
      ImGui::SameLine();
      if (ImGui::Button("Binary")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_BINARY;
      }
      ImGui::SameLine();
      if (ImGui::Button("GraphQl")) {
        tabs[active_tab].currentBodyType = tabs[active_tab].BODY_GRAPHQL;
      }
      ImGui::EndTabItem();
      drawBody();
    }
    if (ImGui::BeginTabItem("Settings")) {
      ImGui::Text("Settings go here");
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }
}

void GUI::render() {
  ImGuiWindowFlags flags = constants->getWindowFlags();

  if (ImGui::Begin("config", NULL, flags)) {
    ImGui::BeginGroup();
    this->workspaceBar();
    ImGui::EndGroup();

    ImGui::NewLine();
    // Left Vertical
    ImGui::BeginGroup();
    { workspaceArea(); }

    ImGui::EndGroup();
    responseArea();
    ImGui::End();
  }
}
void GUI::workspaceArea() {
  if (ImGui::BeginTabBar("TabItem", ImGuiTabBarFlags_TabListPopupButton)) {
    if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing |
                                      ImGuiTabItemFlags_NoTooltip)) {
      Tab t(tabs.size() + 1);
      tabs.push_back(t);
    }
    for (size_t n = 0; n < tabs.size(); n++) {
      if (ImGui::BeginTabItem(tabs[n].title.c_str(), &tabs[n].isOpen,
                              ImGuiTabItemFlags_None)) {
        active_tab = n;
        this->active_response = tabs[active_tab].getResponse();
        ImGui::Text("Method");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(100 * constants->highDPIscaleFactor);
        ImGui::Combo(" ", &tabs[n].currentHttpMethod, constants->REQUEST_TYPE,
                     IM_ARRAYSIZE(constants->REQUEST_TYPE));
        ImGui::SameLine();
        ImGui::InputText("URL", &tabs[n].url);
        ImGui::SameLine();
        if (ImGui::Button("Send")) {
          std::thread t([&] {
           try{
              tabs[active_tab].updateTitle();
            tabs[active_tab].sendRequest();
           }
           catch(const std::exception& e){
             std::cout<<"error"<<std::endl;
           }
          });
          t.detach();
        }
        ImGui::NewLine();
        this->tabConfig();
        ImGui::EndTabItem();
      }

      if (!tabs[n].isOpen) {
        tabs.erase(tabs.begin() + n);
      }
    }
    ImGui::EndTabBar();
  }
}