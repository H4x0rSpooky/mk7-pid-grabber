#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/logger.hpp>
#include <base/files.hpp>

#include <base/notifier.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::session_logger()
    {
        g_files->m_logger.Clear();

        auto const network_engine = (*g_pointers->m_network_engine);

        std::string session = "";

        session += std::format("MK7-PID-Grabber for Mario Kart 7 created by H4x0rSpooky\nGithub: {}", GITHUB);

        session += std::format("\n\nDate Time: {}\nSession ID: {:d}", g_logger.get_current_date_time_string(true), network_engine->session_net_z->room_id);
        
        session += std::format("\n\nPlayer Amount: {:d}\n\nYou were in Slot: {:d}\n", utilities::get_player_amount(), network_engine->local_player_id);

        for (size_t i = 0; i < utilities::get_player_amount(); i++)
        {
            if (i == network_engine->local_player_id)
                continue;

            auto player_data = utilities::get_network_player_data(i);

            auto slot = (i == 0 ? "0 (Host)" : std::to_string(i));

            u32 principal_id = utilities::get_principal_id(i);

            if (player_data->principal_id != principal_id)
                session += std::format("\nPlayer: {} - Slot: {} - Real PID: {:d} (0x{:X}) - Spoofed PID: {:d} (0x{:X})", utilities::parse_name(player_data), slot, principal_id, principal_id, player_data->principal_id, player_data->principal_id);
            else
                session += std::format("\nPlayer: {} - Slot: {} - PID: {:d} (0x{:X})", utilities::parse_name(player_data), slot, principal_id, principal_id);
        }

        g_logger.info("{}", session);

        g_notifier.send("{} got updated", g_files->m_logger.GetName());
    }
}