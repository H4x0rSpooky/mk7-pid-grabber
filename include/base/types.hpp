#pragma once

#include <Unicode.h>
#include <plgldr.h>
#include <types.h>
#include <3ds.h>

#include <string>
#include <vector>

#define DEFAULT_NAME "Player"
#define GUEST_NAME "no name"

namespace nn::nex
{
    struct StationInfo
    {
        u32 magic; // always 1
        u32 unkn0; // always 0
        u32 station_id;
        u32 index; // station id but with 0xC000000
        u32 unkn1; // random
    };
    static_assert(sizeof(StationInfo) == 0x14);

    struct StationListEntry
    {
        StationInfo *station_info;
        u32 player_id;
        u32 index; // same as the player id
    };
    static_assert(sizeof(StationListEntry) == 0xC);

    struct StationList
    {
        StationListEntry entries[0x11];
    };

    struct Station
    {
        u8 gap0[0x58];
        u32 station_id; // 0x58
        u8 gap1[0x30];
        u32 station_url; // + 0x80 + 0xC
    };
    static_assert(sizeof(Station) == 0x90);
}

namespace Net
{
    struct NetworkPlayerData
    {
        u8 gap0[0x30];
        u32 principal_id;
        u8 gap1[0x22];
        u16 name[0x14];
        u16 null_terminator;
        u8 gap2[0x20];
        bool check;
        u8 gap3[3];
        bool loaded;
    };
    static_assert(sizeof(NetworkPlayerData) == 0xA8);

    struct NetworkPlayerDataManager
    {
        NetworkPlayerData players[8];
    };
    static_assert(sizeof(NetworkPlayerDataManager) == 0x540);

    struct StationBufferManager
    {
        u8 gap0[0x80];
        nn::nex::StationList *racers;
        u8 gap1[0x50];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD8);

    struct NetworkEngine
    {
        u8 gap0[0x25C];
        StationBufferManager *station_buffer_mgr;
        u8 gap1[8];
        u32 local_player_id;
        u8 gap2[0x4C];
        NetworkPlayerDataManager *network_player_data_mgr;
    };
    static_assert(sizeof(NetworkEngine) == 0x2BC);
}

struct SelectionIteratorTemplate
{
    u32 *iterator[3];
    u32 station;
    u32 available;
};

struct StationTemplate
{
    u32 target_station_id;
    nn::nex::Station station;
    bool valid;
};

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
    u32 id;
    bool loaded;
    OpponentInfo info;
};