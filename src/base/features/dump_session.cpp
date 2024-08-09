#include <base/features.hpp>

#include <base/pointers.hpp>
#include <base/logger.hpp>
#include <base/files.hpp>
#include <base/menu.hpp>

#include <base/notifier.hpp>

using namespace CTRPluginFramework;

namespace base
{
    void features::dump_session()
    {
        if (g_menu->m_session_logger_entry->IsActivated())
        {
            auto const network_engine = (*g_pointers->m_network_engine);

            std::string session = "";

            session += std::format("MK7-PID-Grabber for Mario Kart 7 created by {}\nGithub: {}", CREATOR, GITHUB);

            session += std::format("\n\nDate Time: {}\nSession ID: {:d}", g_logger.get_current_date_time_string(true), network_engine->session_net_z->room_id);
            
            session += std::format("\n\nPlayer Amount: {:d}\n\nYou were in Slot: {:d}\n", utilities::get_player_amount(false), network_engine->local_player_id);

            for (size_t i = 0; i < utilities::get_player_amount(false); i++)
            {
                if (utilities::is_local_client(i, false))
                    continue;
                
                auto player_data = utilities::get_network_player_data(i);

                if (player_data->loaded)
                {
                    auto station = utilities::get_station_from_list(g_menu->station_list, utilities::get_station_id(i, true));

                    if (!station)
                        utilities::print_error("Could not fetch the Station\n\nOperation: Logging the Session", true);
                    
                    if (station->station_id != utilities::get_station_id(i, true))
                        utilities::print_error("Could not match the Station ID\n\nOperation: Logging the Session", true);

                    if (auto clean_pid = utilities::get_principal_id(station))
                    {
                        auto slot = (i == 0 ? "0 (Host)" : std::to_string(i));

                        if (player_data->principal_id != clean_pid)
                            session += std::format("\nName: {} - Slot: {} - PID: {:d} (0x{:X}) - Spoofed PID: {:d} (0x{:X})", utilities::parse_name(player_data), slot, clean_pid, clean_pid, player_data->principal_id, player_data->principal_id);
                        else
                            session += std::format("\nName: {} - Slot: {} - PID: {:d} (0x{:X})", utilities::parse_name(player_data), slot, player_data->principal_id, player_data->principal_id);
                    }
                    else
                        utilities::print_error("Could not retrieve the Principal ID\n\nOperation: Logging the Session", true);
                }
                else
                    session += std::format("\nName: {} - Slot: {} - Disconnected (CPU)", utilities::parse_name(player_data), (i == 0 ? "0 (Host)" : std::to_string(i)));
            }

            g_files->m_session_log.Clear();

            g_logger.dump(session);

            g_notifier.send("{} got updated", g_files->m_session_log.GetName());
        }
    }
}