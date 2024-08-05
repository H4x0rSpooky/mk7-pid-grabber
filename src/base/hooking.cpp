#include <base/hooking.hpp>

#include <base/pointers.hpp>

namespace base
{
    hooking::hooking()
	:
		m_Sequence_RacePage_initControl_WiFiVS_hook("Sequence::RacePage::initControl_WiFiVS", g_pointers->m_Sequence_RacePage_initControl_WiFiVS, reinterpret_cast<void *>(&hooks::Sequence_RacePage_initControl_WiFiVS)),
		m_Sequence_RacePage_initControl_WiFiBattle_hook("Sequence::RacePage::initControl_WiFiVS", g_pointers->m_Sequence_RacePage_initControl_WiFiBattle, reinterpret_cast<void *>(&hooks::Sequence_RacePage_initControl_WiFiBattle)),
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook("Sequence::MenuWiFi_Confirm::onPageEnter", g_pointers->m_Sequence_MenuWiFi_Confirm_onPageEnter, reinterpret_cast<void *>(&hooks::Sequence_MenuWiFi_Confirm_onPageEnter))
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
		m_Sequence_RacePage_initControl_WiFiVS_hook.enable();
		m_Sequence_RacePage_initControl_WiFiBattle_hook.enable();
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.enable();

		m_enabled = true;
	}

	void hooking::disable()
	{
		m_Sequence_RacePage_initControl_WiFiVS_hook.disable();
		m_Sequence_RacePage_initControl_WiFiBattle_hook.disable();
		m_Sequence_MenuWiFi_Confirm_onPageEnter_hook.disable();

		m_enabled = false;
	}
}