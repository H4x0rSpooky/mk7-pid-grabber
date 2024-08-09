#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::clean_principal_id()
    {
        for (size_t i = 0; i < utilities::get_player_amount(false); i++)
        {
            if (utilities::is_local_client(i, false))
                continue;
            
            auto player_data = utilities::get_network_player_data(i);

            if (player_data->loaded)
            {
                auto station = utilities::get_station_from_list(g_menu->station_list, utilities::get_station_id(i, true));

                if (!station)
                    utilities::print_error("Could not fetch Station\n\nOperation: Cleaning the PID", true);

                if (station->station_id != utilities::get_station_id(i, true))
                    utilities::print_error("Could not match the Station ID\n\nOperation: Cleaning the PID", true);
                
                if (auto clean_pid = utilities::get_principal_id(station))
                {
                    if (player_data->principal_id != clean_pid)
                        player_data->principal_id = clean_pid;
                }
                else
                    utilities::print_error("Could not retrieve the Principal ID\n\nOperation: Cleaning the PID", true);
            }
        }
    }
}