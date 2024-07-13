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
        u8 padding0x0[0x30];
        u32 principal_id;
        u8 padding0[0x22];
        u16 name[0x14];
        u16 null_terminator[2];
        u8 padding1[0x1E];
        bool check;
        u8 padding2[3];
        bool loaded;
    };
    static_assert(sizeof(NetworkPlayerData) == 0xA8);

    struct StationBufferManager
    {
        u8 padding0[0xD0];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD4);

    struct NetworkEngine
    {
        u8 padding0[0x25C];
        StationBufferManager *station_buffer_mgr;
        u8 padding1[0x8];
        u32 client_peer_id;
        u8 padding2[0x4C];
        u32 network_player_data_mgr;
    };
    static_assert(sizeof(NetworkEngine) == 0x2BC);
}

struct SaveData
{
    u8 padding0[0x249C];
    Net::NetworkPlayerData opponents[100];
};

struct OpponentLog
{
    std::string name;
    u32 principal_id;
};

struct PlayerLog
{
    OpponentLog info;
    bool loaded;
};