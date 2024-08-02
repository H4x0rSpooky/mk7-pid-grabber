#include <base/entries.hpp>

#include <base/pointers.hpp>

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::game_session(MenuEntry *entry)
    {
        if ((*g_pointers->m_network_engine)->local_player_id != UINT32_MAX && (*g_pointers->m_network_engine)->station_buffer_mgr->peer_amount > 1)
        {
            std::vector<PlayerInfo> list;

            for (size_t i = 0; i < (*g_pointers->m_network_engine)->station_buffer_mgr->peer_amount; i++)
            {
                if ((*g_pointers->m_network_engine)->local_player_id == i)
                    continue;

                if (auto player_data = utilities::get_network_player_data(i))
                {
                    std::string name = utilities::parse_name(player_data);

                    list.push_back({ i, player_data->loaded, { name, player_data->principal_id } });
                }
            }

            if (!list.empty())
            {
                std::vector<std::string> items;

                for (const PlayerInfo &i : list)
                    items.push_back(i.info.name);
                
                Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Current Amount", Utils::Format("%d", ((*g_pointers->m_network_engine)->station_buffer_mgr->peer_amount - 1)), false), items);
                keyboard.CanAbort(true);
                
                int option = keyboard.Open();
                
                if (option != UINT32_MAX)
                {
                    auto player = list[option];

                    if (player.loaded)
                    {
                        std::string message_box{};

                        message_box += utilities::format_output("Principal ID (DEC)", std::to_string(player.info.principal_id), false);
                        message_box += utilities::format_output("Principal ID (HEX)", "0x" << Utils::ToHex(player.info.principal_id), true);
                        message_box += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(player.info.principal_id)), true);
                        
                        MessageBox(Color::DodgerBlue << player.info.name, message_box, DialogType::DialogOk, ClearScreen::Both)();
                    }
                    else
                        MessageBox(Color::Orange << "An error occurred", Color::DodgerBlue << player.info.name << Color::White << " is unavailable", DialogType::DialogOk, ClearScreen::Both)();
                }
            }
        }
        else
            MessageBox(Color::Orange << "An error occurred", Color::White << "Make sure you're online & in a lobby", DialogType::DialogOk, ClearScreen::Both)();
    }
}