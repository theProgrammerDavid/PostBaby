#include "gui.hpp"

GUI::GUI()
{
    workspaceTableFlags = ImGuiTableFlags_RowBg | ImGuiTableFlags_Borders | ImGuiTableFlags_BordersV | ImGuiTableFlags_Resizable | ImGuiTableFlags_ScrollY;
    windowFlags = ImGuiWindowFlags_NoTitleBar;
    active_tab = 0;
    active_response = "";
    Tab t(tabs.size() + 1);
    tabs.push_back(t);
    Tab t2(tabs.size() + 1);
    tabs.push_back(t2);
}
void GUI::responseArea()
{
    if (ImGui::BeginTabBar("ResponseBar"))
    {
        if (ImGui::BeginTabItem("Body"))
        {
            ImGuiWindowFlags response_flags = ImGuiWindowFlags_HorizontalScrollbar;
            ImGui::BeginChild("ResponseBar", ImVec2(ImGui::GetWindowContentRegionWidth(), ImGui::GetWindowHeight()), false, response_flags);
            ImGui::TextWrapped("%s", active_response.c_str());
            ImGui::EndChild();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Headers"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Cookies"))
        {

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Test Results"))
        {

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void GUI::workspaceBar()
{
    if (ImGui::Button("Preferences"))
    {
        ImGui::OpenPopup("Edit Preferences");
    }
    this->settingsPopup();
    // settingsPopup();
    ImGui::SameLine();
    if (ImGui::Button("History"))
    {
    }
    ImGui::SameLine();
    ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.0f, 1.0f), "%.1fFPS", ImGui::GetIO().Framerate);
}

void GUI::settingsPopup()
{
    centerModal();

    if (ImGui::BeginPopupModal("Edit Preferences", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Changes will be saved automatically");
        ImGui::Separator();

        ImGui::InputInt("URL Max Size", &constants->MAX_URL_SIZE);
        ImGui::InputInt("Request Timeout (ms)", &constants->REQUEST_TIMEOUT);
        //  THEMES
        ImGui::Separator();
        ImGui::Text("Theme");
        if (ImGui::BeginCombo("Theme", constants->THEMES[constants->CURRENT_THEME]))
        {
            for (int n = 0; n < IM_ARRAYSIZE(constants->THEMES); n++)
            {
                const bool is_selected = (constants->CURRENT_THEME == n);
                if (ImGui::Selectable(constants->THEMES[n], is_selected))
                    constants->CURRENT_THEME = n;

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                    ImGui::SetItemDefaultFocus();
            }
            ImGui::EndCombo();
        }
        ImGui::ColorEdit3("Background", (float *)&constants->TEMP_BG_COLOR);
        // THEMES
        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            constants->setTheme();
            constants->clear_color = constants->TEMP_BG_COLOR;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            constants->TEMP_BG_COLOR = constants->clear_color;
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void GUI::centerModal()
{
    ImVec2 center(ImGui::GetIO().DisplaySize.x * 0.5f, ImGui::GetIO().DisplaySize.y * 0.5f);
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
}

void GUI::HelpMarker(const char *desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void GUI::drawKeyValueDesc(std::vector<KeyValuePair> &vec)
{
    const float TEXT_BASE_HEIGHT = ImGui::GetTextLineHeightWithSpacing();
    ImVec2 WorkspaceTableSize = ImVec2(-FLT_MIN, TEXT_BASE_HEIGHT * 8);
    // ImGui::Text("URL E");
    if (ImGui::BeginTable("##table1", 5, workspaceTableFlags, WorkspaceTableSize))
    {

        ImGui::TableSetupColumn("Use", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Key");
        ImGui::TableSetupColumn("Value");
        ImGui::TableSetupColumn("Description");
        ImGui::TableSetupColumn("Del", ImGuiTableColumnFlags_WidthFixed);

        ImGui::TableHeadersRow();

        for (size_t row = 0; row < vec.size(); row++)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::PushID(row);
            ImGui::Checkbox("", vec.at(row).getEnableRef());
            ImGui::PopID();

            ImGui::TableSetColumnIndex(1);
            ImGui::PushID(vec.at(row)._id);
            // ImGui::InputText("Key", vec.at(row).getKey(), 128);
            ImGui::InputText("Key", &vec.at(row).key, 128);

            ImGui::SameLine();
            if (ImGui::Button("Clear"))
            {
                vec.at(row).setKey("");
            }
            ImGui::PopID();

            ImGui::TableSetColumnIndex(2);
            ImGui::PushID(vec.at(row)._id);
            ImGui::InputText("Value", vec.at(row).getValue(), 128);
            ImGui::PopID();

            ImGui::TableSetColumnIndex(3);
            ImGui::PushID(vec.at(row)._id);
            ImGui::InputText("Description", vec.at(row).getDescription(), 128);
            ImGui::PopID();

            ImGui::TableSetColumnIndex(4);

            ImGui::PushID(row);
            if (ImGui::Button("X"))
            {
                vec.erase(vec.begin() + row);
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
        if (ImGui::Button("+"))
        {
            KeyValuePair kvp;
            vec.push_back(kvp);
        }
    }
}

void GUI::drawBody()
{

    if (tabs.at(active_tab).getBodyType() == tabs.at(active_tab).BODY_NONE)
    {
        ImGui::Text("HTTP request does not have a Body");
    }
    else if (tabs.at(active_tab).getBodyType() == tabs.at(active_tab).BODY_URL_ENCODED)
    {
        ImGui::Text("URL encoded");
        drawKeyValueDesc(tabs.at(active_tab).urlParams);
    }
    else if (tabs.at(active_tab).getBodyType() == tabs.at(active_tab).BODY_FORM_DATA)
    {
        ImGui::Text("Form Data");
        drawKeyValueDesc(tabs.at(active_tab).formData);
    }
    else if (tabs.at(active_tab).getBodyType() == tabs.at(active_tab).BODY_RAW)
    {
        ImGui::Text("Raw Body");
        ImGui::SameLine();
        HelpMarker("Ctrl+Enter for newline");
        ImGui::InputTextMultiline(" ", tabs.at(active_tab).getRawBodyRef(), 1024, ImVec2(1200, 200), ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CtrlEnterForNewLine);
    }
    else if (tabs.at(active_tab).getBodyType() == tabs.at(active_tab).BODY_BINARY)
    {
        ImGui::Text("Binary Body");
    }
    else
    {
        ImGui::Text("GraphQl Body");
    }
}

void GUI::tabConfig()
{
    if (ImGui::BeginTabBar("TabItemConfig"))
    {
        if (ImGui::BeginTabItem("Params"))
        {
            // drawParams();
            drawKeyValueDesc(tabs.at(active_tab).queryParams);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Authorization"))
        {
            ImGui::Text("Authorization goes here");

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Headers"))
        {
            ImGui::Text("HTTP Headers");
            drawKeyValueDesc(tabs.at(active_tab).headers);
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Body"))
        {
            ImGui::NewLine();
            if (ImGui::Button("None"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_NONE;
            }
            ImGui::SameLine();

            if (ImGui::Button("Url Encoded"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_URL_ENCODED;
            }
            ImGui::SameLine();
            if (ImGui::Button("Form Data"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_FORM_DATA;
            }
            ImGui::SameLine();
            if (ImGui::Button("Raw"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_RAW;
            }
            ImGui::SameLine();
            if (ImGui::Button("Binary"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_BINARY;
            }
            ImGui::SameLine();
            if (ImGui::Button("GraphQl"))
            {
                tabs.at(active_tab).currentBodyType = tabs.at(active_tab).BODY_GRAPHQL;
            }
            ImGui::EndTabItem();
            drawBody();
        }
        if (ImGui::BeginTabItem("Settings"))
        {
            ImGui::Text("Settings go here");
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void GUI::render()
{
    if (ImGui::Begin("xP", NULL, windowFlags))
    {
        ImGui::BeginGroup();
        this->workspaceBar();
        ImGui::EndGroup();

        ImGui::NewLine();
        // Left Vertical
        ImGui::BeginGroup();
        {

            workspaceArea();

            // ImGui::Separator();
            // ImGui::SameLine();
        }

        ImGui::EndGroup();

        // pool.enqueue(&GUI::responseArea, this).get();
        ImGui::NewLine();

        responseArea();

        ImGui::End();
    }
    // Main Workspace
}
void GUI::workspaceArea()
{
    if (ImGui::BeginTabBar("TabItem"))
    {
        if (ImGui::TabItemButton("+", ImGuiTabItemFlags_Trailing | ImGuiTabItemFlags_NoTooltip))
        {
            Tab t(tabs.size() + 1);
            tabs.push_back(t);
        }
        for (size_t n = 0; n < tabs.size(); n++)
        {
            if (ImGui::BeginTabItem(tabs.at(n).getTitle(), &tabs.at(n).isOpen, ImGuiTabItemFlags_None))
            {
                active_tab = n;
                this->active_response = tabs.at(active_tab).getResponse();
                ImGui::Text("Method");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100);
                ImGui::Combo(" ", &tabs.at(n).currentHttpMethod, constants->REQUEST_TYPE, IM_ARRAYSIZE(constants->REQUEST_TYPE));
                ImGui::SameLine();
                ImGui::InputText("URL", (char *)tabs.at(n).getUrl(), constants->MAX_URL_SIZE);
                ImGui::SameLine();
                if (ImGui::Button("Send"))
                {
                    tabs.at(active_tab).sendRequest();
                }
                ImGui::NewLine();
                this->tabConfig();
                ImGui::EndTabItem();
            }

            if (!tabs.at(n).isOpen)
            {
                tabs.erase(tabs.begin() + n);
            }
        }
        ImGui::EndTabBar();
    }
}