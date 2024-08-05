#include <base/entries.hpp>

#include <base/pointers.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::game_session(MenuEntry *entry)
    {
        if ((*g_pointers->m_network_engine)->local_player_id != UINT32_MAX && utilities::get_player_amount(false) > 1)
        {
            std::vector<PlayerInfo> list;

            for (size_t i = 0; i < utilities::get_player_amount(true); i++)
            {
                if ((*g_pointers->m_network_engine)->local_player_id == i)
                    continue;

                auto player_data = utilities::get_network_player_data(i);
                
                std::string name = utilities::parse_name(player_data);

                list.push_back({ i, player_data->loaded, { name, player_data->principal_id } });
            }

            if (!list.empty())
            {
                std::vector<std::string> items;

                for (const PlayerInfo &i : list)
                    items.push_back(i.info.name);
                
                std::string keyboard_message = "";

                keyboard_message += Color::Turquoise << "Select a player\n\n";
                keyboard_message += utilities::format_output("Session ID", Utils::Format("%d", (*g_pointers->m_network_engine)->session_net_z->room_id), true);
                keyboard_message += utilities::format_output("Player Amount", Utils::Format("%d", utilities::get_player_amount(false)), true);
                keyboard_message += utilities::format_output("Room Host", list[0].info.name, true);

                Keyboard keyboard(keyboard_message, items);
                keyboard.CanAbort(true);
                
                int option = keyboard.Open();
                
                if (option != UINT32_MAX)
                {
                    auto player = list[option];

                    if (player.loaded)
                    {
                        std::string message_box{};

                        u32 principal_id = player.info.principal_id;

                        u32 clean_pid = utilities::get_principal_id(player.id);

                        if (clean_pid != principal_id)
                        {
                            message_box += utilities::format_output("Spoofed PID (DEC)", std::to_string(principal_id), false);
                            message_box += utilities::format_output("Spoofed PID (HEX)", "0x" << Utils::ToHex(principal_id), true) + "\n\n";

                            principal_id = clean_pid;
                        }

                        message_box += utilities::format_output("Principal ID (DEC)", std::to_string(principal_id), false);
                        message_box += utilities::format_output("Principal ID (HEX)", "0x" << Utils::ToHex(principal_id), true);
                        message_box += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(principal_id)), true);
                        
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