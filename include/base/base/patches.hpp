#pragma once

#include "memory/patch.hpp"

namespace base
{
    class patches
    {
    public:
        explicit patches();
        ~patches();

        memory::patch m_disable_right_eye_rendering;
        memory::patch m_uncap_bottom_screen_frames;
        memory::patch m_disable_3d_slider_effect;

        memory::patch m_render_mii_face_0;
        memory::patch m_render_mii_face_1;
        memory::patch m_mii_face_on_votes_0;
        memory::patch m_mii_face_on_votes_1;
        memory::patch m_mii_face_on_minimap;
    };

    inline patches *g_patches{};
}