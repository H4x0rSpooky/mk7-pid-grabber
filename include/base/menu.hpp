#pragma once

#include <CTRPluginFramework.hpp>

#include <map>

namespace base
{
    class menu
    {
    public:
		explicit menu();
		~menu();

        void run();

    private:
        friend struct entries;
        friend class features;
        
        void create();
        void finalize();

        inline static std::map<bool, std::string> s_toggles =
        {
            { false, (CTRPluginFramework::Color(255, 0, 0) << "OFF") + (CTRPluginFramework::Color::White << "") },
            { true, (CTRPluginFramework::Color(0, 255, 0) << "ON") + (CTRPluginFramework::Color::White << "") }
        };

        CTRPluginFramework::PluginMenu *m_plugin_menu;

        CTRPluginFramework::MenuEntry *m_game_session_entry;
        CTRPluginFramework::MenuEntry *m_opponent_list_entry;
    };

    inline menu *g_menu{};
}