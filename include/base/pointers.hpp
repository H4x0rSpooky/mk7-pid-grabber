#pragma once

#include <base/types.hpp>

using GetNetworkPlayerData_t = Net::NetworkPlayerData * (*)(Net::NetworkPlayerDataManager *, u8);
using StationSelectionIteratorTemplate_t = void (*)(u32 **);
using IteratorOverDOsAdvanceToValidItem_t = void (*)(u32 **, bool);

namespace base
{
	class pointers
	{
	public:
		explicit pointers();
		~pointers();
	public:
		GetNetworkPlayerData_t get_network_player_data;
        StationSelectionIteratorTemplate_t station_selection_iterator_template;
        IteratorOverDOsAdvanceToValidItem_t iterator_over_DOs_advance_to_valid_item;

        Net::NetworkEngine **m_network_engine;
		u32 *m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData;
	};

	inline pointers *g_pointers{};
}