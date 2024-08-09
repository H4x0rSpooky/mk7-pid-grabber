#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/menu.hpp>

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

#include <base/logger.hpp>

namespace base
{
    void features::clean_principal_id()
    {
        auto list = utilities::get_player_list(true, true);

        if (list.empty())
            utilities::print_error("Could not fetch the player list\n\nOperation: Reading the target", true);
        
        for (auto player : list)
        {
            if (player.loaded)
            {
                u32 station_id = utilities::get_station_id(player.id, true);

                auto station = utilities::get_station_from_list(g_menu->station_list, station_id);

                if (!station)
                    utilities::print_error("Could not fetch Station\n\nOperation: Cleaning the PID", true);

                if (station->station_id != station_id)
                    utilities::print_error("Could not match the Station ID\n\nOperation: Cleaning the PID", true);
                
                if (auto clean_pid = utilities::get_principal_id(station))
                {
                    if (player.info.principal_id != clean_pid)
                        player.instance->principal_id = clean_pid;
                }
                else
                    utilities::print_error("Could not retrieve the Principal ID\n\nOperation: Cleaning the PID", true);
            }
        }
    }
}