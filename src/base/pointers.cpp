#include <base/pointers.hpp>

#include <base/memory/all.hpp>

#include <base/notifier.hpp>

namespace base
{
	pointers::pointers()
	{
		auto batch = memory::batch();

		batch.add("Net::NetworkPlayerDataManager::getNetworkPlayerData", "A0 20 9F E5 04 40 2D E5 10 20 92 E5 1E 2E 82 E2", [this](memory::handle handle)
		{
			get_network_player_data = reinterpret_cast<decltype(get_network_player_data)>(handle.as<Net::NetworkPlayerData *>());
        });

		batch.add("nn::nex::SelectionIteratorTemplate<nn::nex::Station>::SelectionIteratorTemplate", "F0 47 2D E9 01 20 A0 E3 02 10 A0 E1", [this](memory::handle handle)
		{
            station_selection_iterator_template = reinterpret_cast<decltype(station_selection_iterator_template)>(handle.as<void *>());
        });

        batch.add("nn::nex::IteratorOverDOs::AdvanceToValidItem", "F0 47 2D E9 00 40 A0 E1 01 80 A0 E1 00 10 A0 E3 98 02 9F E5", [this](memory::handle handle)
		{
			iterator_over_DOs_advance_to_valid_item = reinterpret_cast<decltype(iterator_over_DOs_advance_to_valid_item)>(handle.as<void *>());
        });
		
		batch.add("Net::NetworkEngine", "B4 29 00 00 D4 27 00 00 78 78 00 00 F8 05 00 00", [this](memory::handle handle)
		{
			m_network_engine = *handle.add(0x1C).as<decltype(m_network_engine) *>();
		});

		batch.add("Net::NetworkPlayerDataManager::createPlayerDataFromSystemData", "F0 5F 2D E9 03 60 B0 E1 01 70 A0 E1 02 50 A0 E1 ? ? 9F E5 ? ? ? E5 ? ? ? E5", [this](memory::handle handle)
		{
			m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData = handle.as<decltype(m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData)>();
		});

		batch.add("Sequence::RacePage::initControl_WiFiVS", "70 40 2D E9 00 40 A0 E1 ? ? ? EB ? ? ? EB 00 00 50 E3 04 00 A0 E1 01 00 00 0A ? ? ? EB ", [this](memory::handle handle)
		{
			m_Sequence_RacePage_initControl_WiFiVS = handle.as<decltype(m_Sequence_RacePage_initControl_WiFiVS)>();
		});

		batch.add("Sequence::RacePage::initControl_WiFiBattle", "70 40 2D E9 00 40 A0 E1 74 02 90 E5 00 00 50 E3 03 00 00 0A 01 00 50 E3 04 00 A0 01", [this](memory::handle handle)
		{
			m_Sequence_RacePage_initControl_WiFiBattle = handle.as<decltype(m_Sequence_RacePage_initControl_WiFiBattle)>();
		});

		batch.add("Sequence::BaseRacePage::initRankBoard", "F0 4F 2D E9 F4 D0 4D E2 00 40 A0 E1 ? ? ? EB D0 00 8D E5 ? ? ? ? 10 00 90 E5 1E 0E 80 E2 38 10 D0 E5", [this](memory::handle handle)
		{
			init_rankBoard = reinterpret_cast<decltype(init_rankBoard)>(handle.as<void *>());
		});

		batch.run(memory::ranges::c_text);

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}