#include <base/features.hpp>

#include <base/pointers.hpp>

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
            
            if (auto clean_pid = utilities::get_principal_id(i))
            {
                if (player_data->principal_id != clean_pid)
                    player_data->principal_id = clean_pid;
            }
            else
            {
                utilities::print_error("Could not retrieve the Principal ID\n\nOperation: Cleaning the PID", true);

                return;
            }
        }
    }
}