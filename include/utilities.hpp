#pragma once

#include <types.hpp>

#define NETWORK_ENGINE 0x663D00
#define SAVE_DATA 0x6673C8
#define TEXT_BASE 0x100000

#define DEFAULT_NAME "Player"
#define GUEST_NAME "no name"

namespace CTRPluginFramework
{
    class utilities
    {
    public:
        static bool check_process(std::string);
        static std::string parse_name(Net::NetworkPlayerData *);
        static std::string format_output(std::string, std::string, bool);
        static std::string format_friendcode(u64);
        static u64 pid_to_fc(u32);
        static bool is_valid_fc(u64);
    };
}