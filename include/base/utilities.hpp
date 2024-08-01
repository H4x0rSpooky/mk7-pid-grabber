#pragma once

#include <base/types.hpp>

#define OPPONENT_LIST 0x659B44

namespace base
{
    class utilities
    {
    public:
        static bool check_process(std::string);
        static std::string parse_name(Net::NetworkPlayerData *);
        static std::string format_output(std::string, std::string, bool);
        static std::string format_friendcode(u64);
        static u64 pid_to_fc(u32);
        static Net::NetworkPlayerData * get_network_player_data(u8);
        static nn::nex::Station * get_station(u32);
        static u32 get_station_id(u8);
        static u32 get_principal_id(u8);
    };
}