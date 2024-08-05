#include <base/hooking.hpp>

#include <base/features.hpp>

namespace base
{
    void hooks::Sequence_MenuWiFi_Confirm_onPageEnter(u32 _this)
    {
        g_hooking->m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.call_original<void>(_this);

        features::session_logger();

        features::clean_principal_id();
    }
}