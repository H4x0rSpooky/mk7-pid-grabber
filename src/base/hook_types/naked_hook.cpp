#include <base/hook_types/naked_hook.hpp>

#include <base/logger.hpp>

#include <utility>

namespace base::hook_types
{
    using namespace CTRPluginFramework;
    
	naked_hook::naked_hook(std::string_view name, void *target, void *callback, u32 flags)
    :
		m_name(std::move(name)),
        m_hook(std::move(Hook().Initialize(reinterpret_cast<u32>(target), reinterpret_cast<u32>(callback)).SetFlags(flags)))
	{
	}

	naked_hook::~naked_hook()
	{
	}

	void naked_hook::enable()
	{
        if (auto result = m_hook.Enable(); result != HookResult::Success)
           abort();
	}

	void naked_hook::disable()
	{
        if (auto result = m_hook.Disable(); result != HookResult::Success)
            abort();
	}
}