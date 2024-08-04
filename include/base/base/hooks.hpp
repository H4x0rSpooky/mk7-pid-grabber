#pragma once

#include <base/types.hpp>

namespace base
{
	struct hooks
	{
		static bool Net_NetworkPlayerDataManager_createPlayerDataFromSystemData(Net::NetworkPlayerDataManager *, Net::NetworkPlayerData *, u8, Net::NetworkEngine *, bool);
		static void Sequence_RacePage_initControl_WiFiVS(u32);
		static void Sequence_RacePage_initControl_WiFiBattle(u32);
		static void Sequence_MenuWiFi_Confirm_onPageEnter(u32);
	};
}