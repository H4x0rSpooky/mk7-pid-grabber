#include <entries.hpp>

namespace CTRPluginFramework::entries
{
    void game_session(MenuEntry *entry)
    {
        // fetch the network engine instance from memory
        auto network_engine = *reinterpret_cast<Net::NetworkEngine **>(NETWORK_ENGINE);
        
        // cancel the entry if the network engine couldn't be fetched
        if (!network_engine)
            return;

        // check if you are connected to a lobby by comparing your client id and the lobby peer amount (you count as one)
        if (network_engine->local_player_id != UINT32_MAX && network_engine->station_buffer_mgr->peer_amount > 1)
        {
            std::vector<PlayerInfo> list;

            // iterate through all peers and add them to a list
            for (size_t i = 0; i < network_engine->station_buffer_mgr->peer_amount; i++)
            {
                // skip if it's ourselves
                if (network_engine->local_player_id == i)
                    continue;

                // get the player data
                if (auto player_data = utilities::get_network_player_data(i))
                {
                    // convert the name into the right format
                    std::string name = utilities::parse_name(player_data);

                    // add the player to the list
                    list.push_back({ { name, player_data->principal_id }, player_data->loaded });
                }
            }

            if (!list.empty())
            {
                std::vector<std::string> items;

                // create a list for the user to pick from
                for (const PlayerInfo &i : list)
                    items.push_back(i.info.name);
                
                // create a selection for the user to navigate through the list
                Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Current Amount", Utils::Format("%d", (network_engine->station_buffer_mgr->peer_amount - 1)), false), items);
                keyboard.CanAbort(true);
                
                // get the user choice
                int option = keyboard.Open();
                
                // check if a peer was selected
                if (option != UINT32_MAX)
                {
                    auto player = list[option];

                    // check if the selected peer got loaded 
                    if (player.loaded)
                    {
                        std::string message_box{};

                        // format and add the principal id
                        message_box += utilities::format_output("Principal ID", std::to_string(player.info.principal_id), false);
                        
                        // convert the pid to the friend code
                        u64 friendcode = utilities::pid_to_fc(player.info.principal_id);

                        // check if the fc is valid, if yes, format and add the friend code
                        if (friendcode && utilities::is_valid_fc(friendcode))
                            message_box += utilities::format_output("Friend Code", utilities::format_friendcode(friendcode), true);
                        else // let the user know the pid is invalid
                            message_box += Color::Orange << "\n\nThe Principal ID is invalid";

                        // display the message box string
                        MessageBox(Color::DodgerBlue << player.info.name, message_box, DialogType::DialogOk, ClearScreen::Both)();
                    }
                    else // let the user know that the peer didn't load properly
                        MessageBox(Color::Orange << "An error occurred", Color::DodgerBlue << player.info.name << Color::White << " is unavailable", DialogType::DialogOk, ClearScreen::Both)();
                }
            }
        }
        else // let the user know the requirements to use this entry
            MessageBox(Color::Orange << "An error occurred", Color::White << "Make sure you're online & in a lobby", DialogType::DialogOk, ClearScreen::Both)();
    }
}