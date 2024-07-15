#include <entries.hpp>

namespace CTRPluginFramework::entries
{
    void opponent_list(MenuEntry *entry)
    {
        // fetch the opponent list instance from memory
        auto opponent_list = *reinterpret_cast<OpponentList **>(OPPONENT_LIST);
        
        // cancel the entry if the opponent list couldn't be fetched
        if (!opponent_list)
            return;

        std::vector<OpponentInfo> list;

        // iterate through all opponents and add them to a list
        for (size_t i = 0; i < std::size(opponent_list->opponents); i++)
        {
            // get the opponent data
            auto player_data = &opponent_list->opponents[i];

            // add the player to the list
            if (player_data->check)
                list.push_back({ utilities::parse_name(player_data), player_data->principal_id });
        }

        if (!list.empty())
        {
            std::vector<std::string> items;

            // create a list for the user to pick from
            for (const OpponentInfo &i : list)
                items.push_back(i.name);
            
            // create a selection for the user to navigate through the list
            Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Current Amount", Utils::Format("%d", list.size()), false), items);
            keyboard.CanAbort(true);
            
            // get the user choice
            int option = keyboard.Open();
            
            // check if a opponent was selected
            if (option != UINT32_MAX)
            {
                auto player = list[option];

                std::string message_box{};

                // format and add the principal id
                message_box += utilities::format_output("Principal ID", std::to_string(player.principal_id), false);
                
                // convert the pid to the friend code
                u64 friendcode = utilities::pid_to_fc(player.principal_id);

                // check if the fc is valid, if yes, format and add the friend code
                if (friendcode && utilities::is_valid_fc(friendcode))
                    message_box += utilities::format_output("Friend Code", utilities::format_friendcode(friendcode), true);
                else // let the user know the pid is invalid
                    message_box += Color::Orange << "\n\nThe Principal ID is invalid";

                // display the message box string
                MessageBox(Color::DodgerBlue << player.name, message_box, DialogType::DialogOk, ClearScreen::Both)();
            }
        }
    }
}