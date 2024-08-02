#include <base/features.hpp>

#include <base/pointers.hpp>

namespace base
{
    void features::spectator_rankboard(u32 race_page)
    {
        g_pointers->init_rankBoard(race_page);
    }
}