#pragma once

#include <CTRPluginFramework.hpp>
#include <base/utilities.hpp>

namespace base
{
	struct entries
	{
		static void game_session(CTRPluginFramework::MenuEntry *);
		static void opponent_list(CTRPluginFramework::MenuEntry *);
	};
}