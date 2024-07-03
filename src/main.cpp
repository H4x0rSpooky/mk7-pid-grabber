#include <utilities.hpp>

// menu attributes
#define TITLE "MK7 PID Grabber CTRPF"
#define ABOUT "Made by H4x0rSpooky"
#define TYPE 1

// entry attributes
#define NAME Color::SkyBlue << "Grab Principal ID"
#define NOTE Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID." << Color::Orange << "\n\nIf selecting an entry doesn't work, they haven't loaded yet or disconnected."

namespace CTRPluginFramework
{
    int		main(void)
	{
        // check if the game is Mario Kart 7
        if (!utilities::check_process("MarioKar"))
        {
            Sleep(Seconds(1));

            Process::ReturnToHomeMenu();
        }

        const std::vector<u8> pattern =
        {
            0xA0, 0x20, 0x9F, 0xE5,
            0x04, 0x40, 0x2D, 0xE5,
            0x10, 0x20, 0x92, 0xE5,
            0x1E, 0x2E, 0x82, 0xE2
        };

        // get the sig for Net::NetworkPlayerDataManager::getNetworkPlayerData
        u32 getNetworkPlayerData = Utils::Search(TEXT_BASE, Process::GetTextSize(), pattern);

        // abort if the function wasn't found
        if (!getNetworkPlayerData)
            abort();

        // prepare the function call for Net::NetworkPlayerDataManager::getNetworkPlayerData
        static auto GetNetworkPlayerData = reinterpret_cast<Net::NetworkPlayerData * (*)(u32, u32)>(getNetworkPlayerData);

        // create the plugin menu
        auto menu = new PluginMenu(TITLE, ABOUT, TYPE);

        // set the menu attributes
        menu->SynchronizeWithFrame(true);
        menu->ShowWelcomeMessage(false);
        menu->SetHexEditorState(false);

        // create the pid grabber entry and add it to the menu
        *menu += new MenuEntry(NAME, nullptr, [](MenuEntry *entry)
        {
            // fetch the network engine instance from memory
            auto network_engine = *reinterpret_cast<Net::NetworkEngine **>(NETWORK_ENGINE);

            if (!network_engine)
                return;

            // check if you are connected to a lobby by comparing your client id and the lobby peer amount (you count as one)
            if (network_engine->client_peer_id != UINT32_MAX && network_engine->station_buffer_mgr->peer_amount > 1)
            {
                std::vector<PlayerLog> list;

                // iterate through all peers and add them to a list
                for (size_t i = 0; i < network_engine->station_buffer_mgr->peer_amount; i++)
                {
                    // skip if it's ourselves
                    if (network_engine->client_peer_id == i)
                        continue;

                    // get the player data
                    auto player_data = GetNetworkPlayerData(network_engine->network_player_data_mgr, i);

                    // convert the name into the right format
                    std::string name = utilities::parse_name(player_data);

                    // add the player to the list
                    list.push_back({ name, player_data->principal_id, player_data->connected });
                }

                if (!list.empty())
                {
                    std::vector<std::string> items;

                    // create a list for the user to pick from
                    for (const PlayerLog &i : list)
                        items.push_back(i.name);
                    
                    // create a selection for the user to navigate through the list
                    Keyboard keyboard(Color::Turquoise << "Select a player" << Color::White << " | " << utilities::format_output("Current Amount", Utils::Format("%d", (network_engine->station_buffer_mgr->peer_amount - 1)), false), items);
                    keyboard.CanAbort(true);
                    
                    // get the user choice
                    int option = keyboard.Open();
                    
                    // check if a peer was selected
                    if (option != UINT32_MAX)
                    {
                        auto player = list[option];

                        // check if the selected peer is connected 
                        if (player.connected)
                        {
                            static std::string message_box{};

                            // format and add the principal id
                            message_box += utilities::format_output("Principal ID", "0x" << Utils::ToHex(player.principal_id), false);
                            
                            u64 friendcode = utilities::pid_to_fc(player.principal_id);

                            // check if the fc is valid, if yes, format and add the friend code
                            if (friendcode && utilities::is_valid_fc(friendcode))
                                message_box += utilities::format_output("Friend Code", utilities::format_friendcode(friendcode), true);
                            else // let the user know the pid is invalid
                                message_box += Color::Orange << "\n\nThe Principal ID is invalid.";

                            // display the message box string
                            MessageBox(Color::DodgerBlue << player.name, message_box, DialogType::DialogOk, ClearScreen::Both)();

                            message_box.clear();
                        }
                    }
                }
            }
        }, NOTE);

        // run the plugin
        menu->Run();
    	
        return EXIT_SUCCESS;
	}

    void    PatchProcess(FwkSettings &settings)
    {
        settings.CachedDrawMode = false;
        settings.TryLoadSDSounds = false;
		settings.AllowActionReplay = false;
		settings.AllowSearchEngine = false;

        settings.UseGameHidMemory = true;

        settings.SetThemeDefault();
    }
}