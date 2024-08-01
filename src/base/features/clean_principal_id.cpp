#include <base/features.hpp>

namespace base
{
    void features::clean_principal_id(Net::NetworkPlayerData *player_data, u8 player_id)
    {
        u32 clean_pid = utilities::get_principal_id(player_id);

        if (player_data->principal_id != clean_pid)
            player_data->principal_id = clean_pid;
    }
}