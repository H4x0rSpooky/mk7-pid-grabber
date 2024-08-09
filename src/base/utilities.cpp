#include <base/utilities.hpp>

#include <base/pointers.hpp>

#include <CTRPluginFramework.hpp>

using namespace CTRPluginFramework;

namespace base
{
    bool utilities::check_process(std::string process_name)
    {
        std::string current_process{};

        Process::GetName(current_process);

        return (process_name == current_process);
    }
    
    void utilities::print_error(std::string error, bool report)
    {
        if (report)
            error += Color::Red << "\n\nInform " << CREATOR << " about it";

        MessageBox(Color::Orange << "An error occurred", error, DialogType::DialogOk, ClearScreen::Both)();

        if (report)
        {
            Sleep(Seconds(1));

            Process::ReturnToHomeMenu();
        }
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

    std::string utilities::parse_name(Net::NetworkPlayerData *player_data)
    {
        std::string name{};

        Process::ReadString((u32)player_data->name, name, std::size(player_data->name) + 1, StringFormat::Utf16);
        
        return ((name.empty() || name == GUEST_NAME) ? DEFAULT_NAME : name);
    }

    Net::NetworkPlayerData * utilities::get_network_player_data(u8 player_id)
    {
        return g_pointers->get_network_player_data((*g_pointers->m_network_engine)->network_player_data_mgr, player_id);
    }

    u32 utilities::get_station_id(u8 player_id, bool padding)
    {
        auto list = (*g_pointers->m_network_engine)->station_buffer_mgr->racers;

        if (player_id >= std::size(list->entries))
            return {};
        
        if (auto station_info = list->entries[player_id].station_info)
            return (padding ? station_info->padded_station_id : station_info->station_id);

        return {};
    }

    nn::nex::Station * utilities::get_station(u32 station_id)
    {
        static SelectionIteratorTemplate selector{};

        g_pointers->station_selection_iterator_template(selector.iterator);
        
        while (selector.available)
        {
            auto station = reinterpret_cast<nn::nex::Station *>(selector.station);

            if ((station->station_id & 0x3FFFFF) == station_id)
                return station;
            
            g_pointers->iterator_over_DOs_advance_to_valid_item(selector.iterator, false);
        }

        return {};
    }

    std::vector<nn::nex::Station *> utilities::get_station_list()
    {
        std::vector<nn::nex::Station *> list{};

        static SelectionIteratorTemplate selector{};

        g_pointers->station_selection_iterator_template(selector.iterator);
        
        while (selector.available)
        {
            auto station = reinterpret_cast<nn::nex::Station *>(selector.station);

            list.push_back(station);
            
            g_pointers->iterator_over_DOs_advance_to_valid_item(selector.iterator, false);
        }

        return list;
    }
    
    nn::nex::Station * utilities::get_station_from_list(std::vector<nn::nex::Station *> list, u32 station_id)
    {
        if (station_id && !list.empty())
            for (auto station : list)
                if (station)
                    if (station->station_id == station_id)
                        return station;
        
        return {};
    }

    u32 utilities::get_principal_id(nn::nex::Station *station)
    {
       if (station && station->station_url)
        {
            std::string str{};

            u32 length = *(u32 *)(station->station_url - 4);

            if (Process::ReadString(station->station_url, str, (length * sizeof(u32)), StringFormat::Utf16))
            {
                std::string target = "PID";

                size_t start = str.find(target + "=") + std::size(target + "=");
                size_t end = str.find(";", start);
                
                return stoi(str.substr(start, end - start));
            }
        }
        
        return {};
    }

    u32 utilities::get_principal_id(u8 player_id)
    {
        if (auto station_id = utilities::get_station_id(player_id, false))
        {
            if (auto station = utilities::get_station(station_id))
            {
                if (station->station_url)
                {
                    std::string str{};

                    u32 length = *(u32 *)(station->station_url - 4);

                    if (Process::ReadString(station->station_url, str, (length * sizeof(u32)), StringFormat::Utf16))
                    {
                        std::string target = "PID";

                        size_t start = str.find(target + "=") + std::size(target + "=");
                        size_t end = str.find(";", start);
                        
                        return stoi(str.substr(start, end - start));
                    }
                }
            }
        }
        
        return {};
    }

    u32 utilities::get_my_principal_id()
    {
        if (R_SUCCEEDED(frdInit()))
        {
            FriendKey key;

            if (R_SUCCEEDED(FRD_GetMyFriendKey(&key)))
            {
                frdExit();

                return key.principalId;
            }
            
            frdExit();
        }

        return {};
    }

    u32 utilities::get_player_amount(bool exclude_local_client)
    {
        u32 amount = (*g_pointers->m_network_engine)->station_buffer_mgr->peer_amount;

        return (exclude_local_client ? (amount - 1): amount);
    }

    bool utilities::is_local_client(u32 id, bool is_station)
    {
        return (id == (is_station ? (*g_pointers->m_network_engine)->local_station_id : (*g_pointers->m_network_engine)->local_player_id));
    }
}