#include <utils.hpp>

namespace CTRPluginFramework
{
    bool    utils::check_process(std::string process_name)
    {
        std::string current_process;

        Process::GetName(current_process);

        return (process_name == current_process);
    }

    std::string     utils::parse_name(NetworkPlayerData *player_data)
    {
        u16 str[(sizeof(player_data->name) / 2) + 2]{};

        memcpy(str, player_data->name, (sizeof(player_data->name) / 2));

        std::string name;
        
        Utils::ConvertUTF16ToUTF8(name, str);

        return ((name.empty() || name == "no name") ? "Player" : name);
    }

    std::string     utils::format_friendcode(u64 friendcode)
    {
        std::string fmt = Utils::Format("%llu", friendcode);

        while (fmt.length() < 12)
            fmt = "0" + fmt;

        std::string output{};
        
        int counter{};

        for (char unicode : fmt)
        {
            if (counter % 4 == 0 && counter != 0)
                output += "-";
            
            output += unicode;

            counter++;
        }

        return output;
    }
}