#include <entries.hpp>

// menu attributes
#define TITLE "MK7 PID Grabber CTRPF"
#define ABOUT "Made by H4x0rSpooky"
#define TYPE 1

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

        // create the plugin menu
        auto menu = new PluginMenu(TITLE, ABOUT, TYPE);

        // set the menu attributes
        menu->SynchronizeWithFrame(true);
        menu->ShowWelcomeMessage(false);
        menu->SetHexEditorState(false);

        // create an entry and add it to the menu
        *menu += new MenuEntry(SESSION_NAME, nullptr, entries::game_session, SESSION_NOTE);

        // create the opponent list entry and add it to the menu
        *menu += new MenuEntry(OPPONENT_NAME, nullptr, entries::opponent_list, OPPONENT_NOTE);

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

        // fixes crashes with the hid module
        settings.UseGameHidMemory = true;

        settings.SetThemeDefault();
    }
}