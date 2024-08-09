#pragma once

#include <Unicode.h>
#include <plgldr.h>
#include <types.h>
#include <3ds.h>

#include <string>
#include <vector>
#include <format>

#define DEFAULT_NAME "Player"
#define GUEST_NAME "no name"

namespace nn::nex
{
    struct StationInfo
    {
        u32 magic;
        u32 unkn0;
        u32 station_id;
        u32 padded_station_id; // 0x00C0XXXX padded, used as the station's station id
        u32 unkn1;
    };
    static_assert(sizeof(StationInfo) == 0x14);

    struct StationListEntry
    {
        StationInfo *station_info;
        u32 player_id;
        u32 index;
    };
    static_assert(sizeof(StationListEntry) == 0xC);

    struct StationList
    {
        StationListEntry entries[0x11];
    };

    struct Station
    {
        u8 gap0[0x58];
        u32 station_id;
        u8 gap1[0x30];
        u32 station_url;
    };
    static_assert(sizeof(Station) == 0x90);
}

namespace Net
{
    struct SessionNetZ
    {
        u8 gap0[0x44];
        u32 room_id;
    };
    static_assert(sizeof(SessionNetZ) == 0x48);

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
        u8 gap1[0x4C];
        u32 peer_amount;
    };
    static_assert(sizeof(StationBufferManager) == 0xD4);

    struct NetworkEngine
    {
        u8 gap0[0x13C];
        SessionNetZ *session_net_z;
        u8 gap1[0x11C];
        StationBufferManager *station_buffer_mgr;
        u8 gap2[4];
        u32 local_station_id;
        u32 local_player_id;
        u8 gap3[0x4C];
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
    size_t id;
    bool loaded;
    OpponentInfo info;

    constexpr bool operator==(PlayerInfo const &player) const
    {
        return (player.info.name == info.name && player.info.principal_id == info.principal_id);
    }
};