#include <base/entries.hpp>

#include <base/patches.hpp>
#include <base/settings.hpp>

namespace base
{
    void entries::session_logger(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
            if (!g_settings.m_options.session_logger)
                g_settings.m_options.session_logger = true;
        
        if (!entry->IsActivated())
            if (g_settings.m_options.session_logger)
                g_settings.m_options.session_logger = false;
    }
}