#include <base/menu.hpp>

#include <base/entries.hpp>
#include <base/hooking.hpp>
#include <base/settings.hpp>

#include <base/services/rainbow_service.hpp>

#define DEFAULT_ENTRY [](MenuEntry *) {}
#define MENU_TYPE 1

#define GAME_SESSION_NOTE Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID.\n\n" << Color::SkyBlue << "This fetches the current players inside an active game session or current lobby."
#define OPPONENT_LIST_NOTE Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID.\n\n" << Color::SkyBlue << "This fetches only the opponent list from your save data, excluding the friend list."

namespace base
{
    using namespace CTRPluginFramework;
    
    menu::menu()
    :
        m_plugin_menu(new PluginMenu(NAME, ABOUT, MENU_TYPE)),

        m_game_session_entry(new MenuEntry(Color::SkyBlue << "Game Session", nullptr, entries::game_session, GAME_SESSION_NOTE)),
        m_opponent_list_entry(new MenuEntry(Color::SkyBlue << "Opponent List", nullptr, entries::opponent_list, OPPONENT_LIST_NOTE))
    {
        m_plugin_menu->SynchronizeWithFrame(true);
        m_plugin_menu->ShowWelcomeMessage(false);
        m_plugin_menu->SetHexEditorState(false);

        m_plugin_menu->OnNewFrame = [](Time)
        {
            g_rainbow_service->run();

            auto const color = g_rainbow_service->get_ctrpf_color();

            g_menu->m_plugin_menu->Title() = color << NAME;
        };

        m_plugin_menu->OnClosing = []() { g_settings.store(); };

        create();
        
        finalize();

        g_menu = this;
    }

    menu::~menu()
    {
        g_menu = nullptr;

        delete m_plugin_menu;
    }

    void menu::run()
    {
        m_plugin_menu->Run();
    }

    void menu::create()
    {
        *m_plugin_menu += m_game_session_entry;
        *m_plugin_menu += m_opponent_list_entry;
    }

    void menu::finalize()
    {
    }
}