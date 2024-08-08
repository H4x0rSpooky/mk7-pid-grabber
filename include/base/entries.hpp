#pragma once

#include <CTRPluginFramework.hpp>
#include <base/utilities.hpp>

namespace base
{
	struct entries
	{
		static void game_session(CTRPluginFramework::MenuEntry *);
		static void opponent_list(CTRPluginFramework::MenuEntry *);
		static void render_optimizations(CTRPluginFramework::MenuEntry *);
		static void show_mii_heads(CTRPluginFramework::MenuEntry *);
		static void session_logger(CTRPluginFramework::MenuEntry *);
	};
}