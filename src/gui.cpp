#include "gui.hpp"

GUI::GUI()
{
    active_tab = 0;
    active_response = "If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them";
    Tab t;
    tabs.push_back(t);
    Tab t2;
    t2.title = "Title2";
    tabs.push_back(t2);
}
void GUI::responseArea()
{
    ImGui::Begin("Response");

    if (ImGui::BeginTabBar("ResponseBar"))
    {
        if (ImGui::BeginTabItem("Body"))
        {

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

    ImGui::TextWrapped("%s", active_response.c_str());
    ImGui::End();
}

void GUI::workspaceBar()
{
    ImGui::Begin("Workspace Bar");
    if (ImGui::Button("New"))
    {
        Tab t;
        tabs.push_back(t);
    }
    ImGui::End();
}

void GUI::settingsPopup()
{
    centerModal();

    if (ImGui::BeginPopupModal("Edit Preferences", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Changes will be saved automatically");
        ImGui::Separator();

        ImGui::InputInt("URL Max Size", &constants->MAX_URL_SIZE);

        ImGui::Separator();
        if (ImGui::Button("OK", ImVec2(120, 0)))
        {
            ImGui::CloseCurrentPopup();
        }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
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

void GUI::settingsArea()
{
    ImGui::Begin("Settings");
    if (ImGui::Button("Preferences"))
    {
        ImGui::OpenPopup("Edit Preferences");
    }
    auto f_settings_popup = pool.enqueue(&GUI::settingsPopup, this);
    // settingsPopup();

    if (ImGui::Button("History"))
    {
    }

    f_settings_popup.get();
    ImGui::End();
}

void GUI::render()
{
    // Main Workspace
    ImGui::BeginGroup();

    // Left Vertical
    ImGui::BeginGroup();
    {
        if (ImGui::Button("+", ImVec2(20, 20)))
        {
            Tab t;
            tabs.push_back(t);
        }
        // ImGui::Separator();
        ImGui::SameLine();

        if (ImGui::BeginTabBar("TabItem"))
        {

            for (size_t n = 0; n < tabs.size(); n++)
            {
                if (ImGui::BeginTabItem(tabs.at(n).title.c_str(), &tabs.at(n).isOpen, ImGuiTabItemFlags_None))
                {
                    active_tab = n;
                    ImGui::InputText("URL", (char *)tabs.at(n).getUrl(), constants->MAX_URL_SIZE);
                    ImGui::SameLine();
                    if (ImGui::Button("Send"))
                    {
                    }

                    if (ImGui::BeginTabBar("TabItemConfig"))
                    {

                        if (ImGui::BeginTabItem("Params"))
                        {
                            ImGui::Text("Params go here");

                            if (ImGui::BeginTable("##table1", 3))
                            {
                                // Display headers so we can inspect their interaction with borders.
                                // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)

                                ImGui::TableSetupColumn("One");
                                ImGui::TableSetupColumn("Two");
                                ImGui::TableSetupColumn("Three");
                                ImGui::TableHeadersRow();

                                for (int row = 0; row < 5; row++)
                                {
                                    ImGui::TableNextRow();
                                    for (int column = 0; column < 3; column++)
                                    {
                                        ImGui::TableSetColumnIndex(column);
                                        char buf[32];
                                        sprintf(buf, "Hello %d,%d", column, row);
                                        // if (contents_type == CT_Text)
                                        ImGui::TextUnformatted(buf);
                                        ImGui::Separator();
                                        // else if (contents_type)
                                        // ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                                    }
                                }
                                ImGui::EndTable();
                            }
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Authorization"))
                        {
                            ImGui::Text("Authorization goes here");
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Headers"))
                        {
                            ImGui::Text("headers go here");
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Body"))
                        {
                            ImGui::Text("Body goes here");
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Pre-Request Script"))
                        {
                            ImGui::Text("Pre-Requests Script goes here");
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Tests"))
                        {
                            ImGui::Text("Tests go here");
                            ImGui::EndTabItem();
                        }
                        if (ImGui::BeginTabItem("Settings"))
                        {
                            ImGui::Text("Settings go here");
                            ImGui::EndTabItem();
                        }

                        ImGui::EndTabBar();
                    }

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
    ImGui::EndGroup();
    
    ImGui::SameLine();
    // Right Vertical
    ImGui::BeginGroup();
    {
        if (ImGui::Button("Preferences"))
        {
            ImGui::OpenPopup("Edit Preferences");
        }
        auto f_settings_popup = pool.enqueue(&GUI::settingsPopup, this);
        // settingsPopup();

        if (ImGui::Button("History"))
        {
        }

        f_settings_popup.get();
    }
    ImGui::EndGroup();

    ImGui::EndGroup();

    // pool.enqueue(&GUI::responseArea, this).get();

    // responseArea();
    // workspaceBar();
    // workspaceArea();
    // settingsArea();
    // t.get();
    // for(int i=0;i<waiters.size();i++){
    // waiters.at(i).get();
    // }
}
void GUI::workspaceArea()
{
    ImGui::Begin("Workspace");
    if (ImGui::Button("+", ImVec2(20, 20)))
    {
        Tab t;
        tabs.push_back(t);
    }
    // ImGui::Separator();
    ImGui::SameLine();

    if (ImGui::BeginTabBar("TabItem"))
    {

        for (size_t n = 0; n < tabs.size(); n++)
        {
            if (ImGui::BeginTabItem(tabs.at(n).title.c_str(), &tabs.at(n).isOpen, ImGuiTabItemFlags_None))
            {
                active_tab = n;
                ImGui::InputText("URL", (char *)tabs.at(n).getUrl(), constants->MAX_URL_SIZE);
                ImGui::SameLine();
                if (ImGui::Button("Send"))
                {
                }

                if (ImGui::BeginTabBar("TabItemConfig"))
                {

                    if (ImGui::BeginTabItem("Params"))
                    {
                        ImGui::Text("Params go here");

                        if (ImGui::BeginTable("##table1", 3))
                        {
                            // Display headers so we can inspect their interaction with borders.
                            // (Headers are not the main purpose of this section of the demo, so we are not elaborating on them too much. See other sections for details)

                            ImGui::TableSetupColumn("One");
                            ImGui::TableSetupColumn("Two");
                            ImGui::TableSetupColumn("Three");
                            ImGui::TableHeadersRow();

                            for (int row = 0; row < 5; row++)
                            {
                                ImGui::TableNextRow();
                                for (int column = 0; column < 3; column++)
                                {
                                    ImGui::TableSetColumnIndex(column);
                                    char buf[32];
                                    sprintf(buf, "Hello %d,%d", column, row);
                                    // if (contents_type == CT_Text)
                                    ImGui::TextUnformatted(buf);
                                    ImGui::Separator();
                                    // else if (contents_type)
                                    // ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
                                }
                            }
                            ImGui::EndTable();
                        }
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Authorization"))
                    {
                        ImGui::Text("Authorization goes here");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Headers"))
                    {
                        ImGui::Text("headers go here");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Body"))
                    {
                        ImGui::Text("Body goes here");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Pre-Request Script"))
                    {
                        ImGui::Text("Pre-Requests Script goes here");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Tests"))
                    {
                        ImGui::Text("Tests go here");
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Settings"))
                    {
                        ImGui::Text("Settings go here");
                        ImGui::EndTabItem();
                    }

                    ImGui::EndTabBar();
                }

                ImGui::EndTabItem();
            }

            if (!tabs.at(n).isOpen)
            {
                tabs.erase(tabs.begin() + n);
            }
        }
        ImGui::EndTabBar();
    }

    ImGui::End();
}