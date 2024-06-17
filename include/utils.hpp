#pragma once

#include <types.hpp>

#define NETWORK_ENGINE 0x663D00
#define TEXT_BASE 0x100000

namespace CTRPluginFramework
{
    class utils
    {
    public:
        static bool check_process(std::string);
        static std::string parse_name(NetworkPlayerData *);
        static std::string format_friendcode(u64);
    };
}