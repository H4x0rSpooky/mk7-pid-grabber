#include <base/menu.hpp>

#include <base/entries.hpp>
#include <base/hooking.hpp>
#include <base/settings.hpp>
#include <base/patches.hpp>
#include <base/files.hpp>

#include <base/services/rainbow_service.hpp>

#define DEFAULT_ENTRY [](MenuEntry *) {}

#ifdef _DEBUG
    #define MENU_TYPE 0
#else
    #define MENU_TYPE 1
#endif

#define GAME_SESSION_NOTE Color::SkyBlue << "This fetches the current players inside an active game session or current lobby.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define OPPONENT_LIST_NOTE Color::SkyBlue << "This fetches only the opponent list from your save data, excluding the friend list.\n\n" << Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID."
#define RENDER_OPTIMIZATIONS_NOTE Color::SkyBlue << "This entry disables the 3D and uncaps the FPS on the bottom screen during races."
#define SESSION_LOGGER_NOTE Color::SkyBlue << "This entry creates a detailed dump of the latest game session you played in.\n\n" << Color::DodgerBlue << "SD:luma\\plugins\\00040000" << Utils::ToHex(Process::GetTitleID()) << "\\" << NAME << "\\" << g_files->m_logger.GetName()

namespace base
{
    using namespace CTRPluginFramework;
    
    menu::menu()
    :
        m_plugin_menu(new PluginMenu(NAME, std::stoi(MAJOR), std::stoi(MINOR), std::stoi(REV), ABOUT, MENU_TYPE)),

        m_game_session_entry(new MenuEntry("Game Session", nullptr, entries::game_session, GAME_SESSION_NOTE)),
        m_opponent_list_entry(new MenuEntry("Opponent List", nullptr, entries::opponent_list, OPPONENT_LIST_NOTE)),
        m_render_optimizations_entry(new MenuEntry("Render Optimizations", entries::render_optimizations, RENDER_OPTIMIZATIONS_NOTE)),
        m_load_rankboard_in_spectate_entry(new MenuEntry("Load Rankboard In Spectate", DEFAULT_ENTRY)),
        m_show_mii_heads_entry(new MenuEntry("Show Mii Heads", entries::show_mii_heads)),
        m_session_logger_entry(new MenuEntry("Session Logger", entries::session_logger, SESSION_LOGGER_NOTE))
    {
        m_plugin_menu->SynchronizeWithFrame(true);
        m_plugin_menu->ShowWelcomeMessage(false);

        auto settings = FwkSettings::Get();

#ifdef _DEBUG
        m_plugin_menu->SetHexEditorState(true);

        settings.AllowActionReplay = true;
		settings.AllowSearchEngine = true;
#else
        m_plugin_menu->SetHexEditorState(false);

        settings.AllowActionReplay = false;
		settings.AllowSearchEngine = false;
#endif

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
        *m_plugin_menu += m_session_logger_entry;
        *m_plugin_menu += m_render_optimizations_entry;
    }

    void menu::finalize()
    {
        m_load_rankboard_in_spectate_entry->Enable();
        m_show_mii_heads_entry->Enable(); // the crash fix might cause issues

        if (g_settings.m_options.render_optimizations)
            m_render_optimizations_entry->Enable();
        
        if (g_settings.m_options.session_logger)
            m_session_logger_entry->Enable();
    }
}