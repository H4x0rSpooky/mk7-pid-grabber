#pragma once

#include <base/types.hpp>

namespace base
{
	struct hooks
	{
		static bool Net_NetworkPlayerDataManager_createPlayerDataFromSystemData(Net::NetworkPlayerDataManager *, Net::NetworkPlayerData *, u8, Net::NetworkEngine *, bool);
	};
}