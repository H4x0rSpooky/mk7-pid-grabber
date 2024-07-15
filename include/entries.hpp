#pragma once

#include <utilities.hpp>

// entry attributes
#define SESSION_NAME Color::SkyBlue << "Game Session"
#define SESSION_NOTE Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID.\n\n" << Color::SkyBlue << "This fetches the current players inside an active game session or current lobby."

#define OPPONENT_NAME Color::SkyBlue << "Opponent List"
#define OPPONENT_NOTE Color::DodgerBlue << "Press \uE000 and select a player name to display their current Principal ID.\n\n" << Color::SkyBlue << "This fetches only the opponent list from your save data, excluding the friend list."

namespace CTRPluginFramework::entries
{
    void game_session(MenuEntry *);
    void opponent_list(MenuEntry *);
}