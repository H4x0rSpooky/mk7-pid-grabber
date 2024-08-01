#include <base/hook_types/detour_hook.hpp>

#include <base/logger.hpp>

#include <utility>

namespace base::hook_types
{
    using namespace CTRPluginFramework;
    
	detour_hook::detour_hook(std::string_view name, void *target, void *detour)
    :
		m_name(std::move(name)),
        m_hook(std::move(Hook().InitializeForMitm(reinterpret_cast<u32>(target), reinterpret_cast<u32>(detour))))
	{
	}

	detour_hook::~detour_hook()
	{
	}

	void detour_hook::enable()
	{
        if (auto result = m_hook.Enable(); result != HookResult::Success)
            abort();
	}

	void detour_hook::disable()
	{
        if (auto result = m_hook.Disable(); result != HookResult::Success)
            abort();
	}
}