#include <base/hooking.hpp>

#include <base/features.hpp>
#include <base/menu.hpp>

#include <base/logger.hpp>

namespace base
{
    void hooks::Sequence_MenuWiFi_Confirm_onPageEnter(u32 _this)
    {
        g_hooking->m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.call_original<void>(_this);

        g_menu->station_list = utilities::get_station_list();

        if (!g_menu->station_list.size())
            utilities::print_error("Could not fetch the Station list", true);

        features::clean_principal_id();

        features::dump_session();
    }
}