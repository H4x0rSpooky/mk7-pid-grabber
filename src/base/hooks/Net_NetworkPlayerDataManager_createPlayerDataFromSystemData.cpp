#include <base/hooking.hpp>

namespace base
{
    bool hooks::Net_NetworkPlayerDataManager_createPlayerDataFromSystemData(Net::NetworkPlayerDataManager *_this, Net::NetworkPlayerData *player_data, u8 player_id, Net::NetworkEngine *network_engine, bool flag)
    {
        bool result = g_hooking->m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData_hook.call_original<bool>(_this, player_data, player_id, network_engine, flag);

        if (result)
            features::clean_principal_id(player_data, player_id);
        
        return result;
    }
}