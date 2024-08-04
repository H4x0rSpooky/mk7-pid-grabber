#pragma once

#include "fwddec.hpp"

#include "handle.hpp"

#include <CTRPluginFramework.hpp>

namespace base::memory
{
	class range
	{
	public:
		range(handle base, std::size_t size);

		handle begin();
		handle end();
		std::size_t size();

		bool contains(handle h);

		handle scan(pattern const &sig);
		
	protected:
		handle m_base;
		std::size_t m_size;
	};

	struct ranges
	{
		inline static auto const c_text = range(handles::c_text_start, CTRPluginFramework::Process::GetTextSize());
	};
}