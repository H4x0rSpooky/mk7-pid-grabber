#pragma once

#include <base/utilities.hpp>
#include <base/types.hpp>

namespace base
{
	struct features
	{
		static void clean_principal_id(Net::NetworkPlayerData *, u8);
		static void spectator_rankboard(u32);
	};
}