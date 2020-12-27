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
    pool.enqueue(&GUI::responseArea, this).get();

    // responseArea();
    workspaceBar();
    workspaceArea();
    settingsArea();
    // t.get();
    // for(int i=0;i<waiters.size();i++){
    // waiters.at(i).get();
    // }
}
void GUI::workspaceArea()
{
    ImGui::Begin("Workspace");

    ImGui::SameLine();

    if (ImGui::BeginTabBar("MyTabBar"))
    {
        for (int n = 0; n < tabs.size(); n++)
            if (ImGui::BeginTabItem(tabs.at(n).title.c_str(), &tabs.at(n).isOpen, ImGuiTabItemFlags_None))
            {
                active_tab = n;
                ImGui::InputText("URL", (char *)tabs.at(n).getUrl(), constants->MAX_URL_SIZE);
                ImGui::SameLine();
                if (ImGui::Button("Send"))
                {
                }
                ImGui::EndTabItem();
            }
        ImGui::EndTabBar();
    }

    ImGui::End();
}