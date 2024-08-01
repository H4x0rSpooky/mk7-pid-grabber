#include <base/pointers.hpp>

#include <base/memory/all.hpp>

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
		
		batch.run(memory::ranges::c_text);

		g_pointers = this;
	}

	pointers::~pointers()
	{
		g_pointers = nullptr;
	}
}
