#include <base/hooking.hpp>

#include <base/features.hpp>

namespace base
{
    void hooks::Sequence_MenuWiFi_Confirm_onPageEnter(u32 _this)
    {
        g_hooking->m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.call_original<void>(_this);

        std::vector<u32> station_id_list{};

        for (size_t i = 0; i < utilities::get_player_amount(false); i++)
        {
            if (utilities::is_local_client(i, false))
                continue;

            if (auto station_id = utilities::get_station_id(i, false))
                station_id_list.push_back(station_id);
        }

        if (!station_id_list.size())
            utilities::print_error("Could not compile the Station ID list", true);
        
        auto const list = utilities::get_station_list(station_id_list);
        
        if (!list.size())
            utilities::print_error("Could not fetch the Station list", true);

        features::clean_principal_id(list);

        features::print_session(list);
    }
}