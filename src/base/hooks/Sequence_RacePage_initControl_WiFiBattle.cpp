#include <base/hooking.hpp>

namespace base
{
    void hooks::Sequence_RacePage_initControl_WiFiBattle(u32 _this)
    {
        g_hooking->m_Sequence_RacePage_initControl_WiFiBattle_hook.call_original<bool>(_this);

        features::spectator_rankboard(_this);
    }
}