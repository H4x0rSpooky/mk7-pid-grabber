#include <base/entries.hpp>

#include <base/patches.hpp>

namespace base
{
    void entries::show_mii_heads(CTRPluginFramework::MenuEntry *entry)
    {
        if (entry->WasJustActivated())
        {
            g_patches->m_render_mii_face_0.enable();
            g_patches->m_render_mii_face_1.enable();
            g_patches->m_render_mii_face_2.enable();
            g_patches->m_mii_face_on_votes_0.enable();
            g_patches->m_mii_face_on_votes_1.enable();
            g_patches->m_mii_face_on_minimap.enable();
        }
        
        if (!entry->IsActivated())
        {
            g_patches->m_render_mii_face_0.disable();
            g_patches->m_render_mii_face_1.disable();
            g_patches->m_render_mii_face_2.disable();
            g_patches->m_mii_face_on_votes_0.disable();
            g_patches->m_mii_face_on_votes_1.disable();
            g_patches->m_mii_face_on_minimap.disable();
        }
    }
}