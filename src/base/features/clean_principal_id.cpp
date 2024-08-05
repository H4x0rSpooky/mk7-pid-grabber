#include <base/features.hpp>

#include <base/pointers.hpp>

namespace base
{
    void features::clean_principal_id()
    {
        auto network_engine = (*g_pointers->m_network_engine);
        
        for (size_t i = 0; i < utilities::get_player_amount(); i++)
        {
            if (network_engine->local_player_id == i)
                continue;
            
            auto player_data = utilities::get_network_player_data(i);
            
            u32 clean_pid = utilities::get_principal_id(i);

            if (player_data->principal_id != clean_pid)
                player_data->principal_id = clean_pid;
        }
    }
}