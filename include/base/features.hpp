#pragma once

#include <base/utilities.hpp>
#include <base/types.hpp>

namespace base
{
	struct features
	{
		static void spectator_rankboard(u32);
		static void clean_principal_id();
		static void dump_session();
	};
}