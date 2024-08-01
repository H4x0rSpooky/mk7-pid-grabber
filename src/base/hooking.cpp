#include <base/hooking.hpp>

#include <base/pointers.hpp>

namespace base
{
    hooking::hooking()
	:
		m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData_hook("Net::NetworkPlayerDataManager::createPlayerDataFromSystemData", g_pointers->m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData, reinterpret_cast<void *>(&hooks::Net_NetworkPlayerDataManager_createPlayerDataFromSystemData))
	{
		g_hooking = this;
	}

	hooking::~hooking()
	{
		g_hooking = nullptr;

		if (m_enabled)
			disable();
	}

    void hooking::enable()
	{
		m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_Net_NetworkPlayerDataManager_createPlayerDataFromSystemData_hook.disable();

		m_enabled = false;
	}
}