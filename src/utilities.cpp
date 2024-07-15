#include <utilities.hpp>

namespace CTRPluginFramework
{
    bool utilities::check_process(std::string process_name)
    {
        std::string current_process{};

        Process::GetName(current_process);

        return (process_name == current_process);
    }

    std::string utilities::parse_name(Net::NetworkPlayerData *player_data)
    {
        u16 str[std::size(player_data->name) + std::size(player_data->null_terminator)]{};

        memcpy(str, player_data->name, std::size(player_data->name));

        std::string name{};
        
        Utils::ConvertUTF16ToUTF8(name, str);

        return ((name.empty() || name == GUEST_NAME) ? DEFAULT_NAME : name);
    }

    std::string utilities::format_output(std::string name, std::string value, bool linebreak)
    {
        return Color::SkyBlue << (linebreak ? "\n" << name : name) << Color::White << ": " << Color::LimeGreen << value;
    }

    std::string utilities::format_friendcode(u64 friendcode)
    {
        return Utils::Format("%012llu", friendcode).insert(4, 1, '-').insert(9, 1, '-');
    }

    u64 utilities::pid_to_fc(u32 principal_id)
    {
        if (R_SUCCEEDED(frdInit()))
        {
            u64 friendcode{};
            
            bool res = R_SUCCEEDED(FRD_PrincipalIdToFriendCode(principal_id, &friendcode));
            
            frdExit();

            return (res ? friendcode : 0);
        }

        return {};
    }

    bool utilities::is_valid_fc(u64 friendcode)
    {
        if (R_SUCCEEDED(frdInit()))
        {
            bool is_valid = false;

            bool res = R_SUCCEEDED(FRD_IsValidFriendCode(friendcode, &is_valid));
            
            frdExit();

            return (res && is_valid);
        }

        return false;
    }

    Net::NetworkPlayerData * utilities::get_network_player_data(u8 player_id)
    {
        auto network_engine = *reinterpret_cast<Net::NetworkEngine **>(NETWORK_ENGINE);

        return &network_engine->network_player_data_mgr->players[player_id];
    }
}