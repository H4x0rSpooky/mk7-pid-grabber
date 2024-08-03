#include <base/services/rainbow_service.hpp>

#include <math.h>

#define PACK_U8(x) (static_cast<u8>(x * std::numeric_limits<u8>::max()))

namespace base
{
    rainbow_service::rainbow_service()
    {
        g_rainbow_service = this;
    }

    rainbow_service::~rainbow_service()
    {
        g_rainbow_service = nullptr;
    }

    void rainbow_service::run()
    {
        m_hue += (1.f / 600.f);
    }

    rainbow_service::rgb rainbow_service::get_color()
    {
        return hsv{ m_hue, 1.f, 1.f }.to_rgb();
    }

    CTRPluginFramework::Color rainbow_service::get_ctrpf_color()
    {
        return get_color().as_u32();
    }

    u32 rainbow_service::rgb::as_u32()
    {
        return (PACK_U8(r) << 24) | (PACK_U8(g) << 16) | (PACK_U8(b) << 8) | std::numeric_limits<u8>::max();
    }
    
    rainbow_service::rgb rainbow_service::hsv::to_rgb()
    {
        if (s == 0.f)
            return { v, v, v };

        auto result = rgb{};

        h = std::fmod(h, 1.f) / (60.f / 360.f);
        auto i = static_cast<int>(h);
        auto f = h - static_cast<float>(i);
        auto p = v * (1.f - s);
        auto q = v * (1.f - s * f);
        auto t = v * (1.f - s * (1.f - f));

        switch (i)
        {
            case 0: result.r = v; result.g = t; result.b = p; break;
            case 1: result.r = q; result.g = v; result.b = p; break;
            case 2: result.r = p; result.g = v; result.b = t; break;
            case 3: result.r = p; result.g = q; result.b = v; break;
            case 4: result.r = t; result.g = p; result.b = v; break;
            case 5: default: result.r = v; result.g = p; result.b = q; break;
        }

        return result;
    }
}