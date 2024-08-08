#pragma once

#include <base/types.hpp>

using GetNetworkPlayerData_t = Net::NetworkPlayerData * (*)(Net::NetworkPlayerDataManager *, u8);
using StationSelectionIteratorTemplate_t = void (*)(u32 **);
using IteratorOverDOsAdvanceToValidItem_t = void (*)(u32 **, bool);
using InitRankboard_t = void (*)(u32);
using GetStationURL_t = u32 (*)(nn::nex::Station *, u8);

#define CTRPF_hid_settings 0x1FF81000

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
		InitRankboard_t init_rankBoard;
		GetStationURL_t get_station_url;

        Net::NetworkEngine **m_network_engine;
		void *m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData;
		void *m_Sequence_RacePage_initControl_WiFiVS;
		void *m_Sequence_RacePage_initControl_WiFiBattle;
		void *m_System_ProjectGameFramework_procDraw;
		void *m_System_ProjectGameFramework_procFrame;
		void *m_Mii_MiiEngine_createMiiFace;
		void *m_Sequence_Menu_UpBarController_setTex;
		void *m_Sequence_BaseRacePage_initMapIcon;
		void *m_CourseVoteListSetTexture; // unknown symbol
		void *m_Sequence_MenuWiFi_Confirm_onPageEnter;
	};

	inline pointers *g_pointers{};
}