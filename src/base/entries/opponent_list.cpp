#include <base/entries.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void entries::opponent_list(MenuEntry *entry)
    {
        auto opponent_list = *reinterpret_cast<OpponentList **>(OPPONENT_LIST);
        
        if (!opponent_list)
            return;

        std::vector<OpponentInfo> list;

        for (size_t i = 0; i < std::size(opponent_list->opponents); i++)
        {
            auto player_data = &opponent_list->opponents[i];

            if (player_data->check)
                list.push_back({ utilities::parse_name(player_data), player_data->principal_id });
        }

        if (!list.empty())
        {
            std::vector<std::string> items;

            for (const OpponentInfo &i : list)
                items.push_back(i.name);
            
            Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Opponent Amount", Utils::Format("%d", list.size()), false), items);
            keyboard.CanAbort(true);
            
            int option = keyboard.Open();
            
            if (option != UINT32_MAX)
            {
                auto player = list[option];

                std::string message_box{};

                message_box += utilities::format_output("Principal ID (DEC)", std::to_string(player.principal_id), false);
                message_box += utilities::format_output("Principal ID (HEX)", "0x" << Utils::ToHex(player.principal_id), true);
                message_box += utilities::format_output("Friend Code", utilities::format_friendcode(utilities::pid_to_fc(player.principal_id)), true);

                MessageBox(Color::DodgerBlue << player.name, message_box, DialogType::DialogOk, ClearScreen::Both)();
            }
        }
    }
}