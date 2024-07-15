#pragma once

#include <CTRPluginFramework.hpp>
#include <3ds.h>

#include <Unicode.h>
#include <plgldr.h>
#include <types.h>
#include <csvc.h>

#include <string>
#include <vector>

namespace Net
{
    struct NetworkPlayerData
    {
        u8 gap0[0x30];
        u32 principal_id;
        u8 gap1[0x22];
        u16 name[0x14];
        u16 null_terminator[2];
        u8 gap2[0x1E];
        bool check;
        u8 gap3[3];
        bool loaded;
    };
    static_assert(sizeof(NetworkPlayerData) == 0xA8);

    struct NetworkPlayerDataManager
    {
        Net::NetworkPlayerData players[8];
    };
    static_assert(sizeof(NetworkPlayerDataManager) == 0x540);

    struct StationBufferManager
    {
        u8 gap0[0xD0];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD4);

    struct NetworkEngine
    {
        u8 gap0[0x25C];
        Net::StationBufferManager *station_buffer_mgr;
        u8 gap1[8];
        u32 local_player_id;
        u8 gap2[0x4C];
        Net::NetworkPlayerDataManager *network_player_data_mgr;
    };
    static_assert(sizeof(NetworkEngine) == 0x2BC);
}

struct OpponentList
{
    u8 gap0[0x9F0];
    Net::NetworkPlayerData opponents[100];
};

struct OpponentInfo
{
    std::string name;
    u32 principal_id;
};

struct PlayerInfo
{
    OpponentInfo info;
    bool loaded;
};