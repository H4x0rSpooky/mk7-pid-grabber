#include <base/entries.hpp>

#include <base/patches.hpp>
#include <base/settings.hpp>

namespace base
{
    void entries::render_optimizations(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            if (!g_settings.m_options.render_optimizations)
                g_settings.m_options.render_optimizations = true;

            g_patches->m_disable_right_eye_rendering.enable();
            g_patches->m_uncap_bottom_screen_frames.enable();
            g_patches->m_disable_3d_slider_effect.enable();
        }
        
        if (!entry->IsActivated())
        {
            if (g_settings.m_options.render_optimizations)
                g_settings.m_options.render_optimizations = false;

            g_patches->m_disable_right_eye_rendering.disable();
            g_patches->m_uncap_bottom_screen_frames.disable();
            g_patches->m_disable_3d_slider_effect.disable();
        }
    }
}