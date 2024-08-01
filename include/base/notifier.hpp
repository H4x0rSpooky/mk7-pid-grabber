#pragma once

#include <format>

namespace base
{
    class notifier
    {
    public:
        template <typename ...args_t>
		void send(std::format_string<args_t ...>, args_t &&...);

    private:
        void notify(std::string);
    };

    template <typename ...args_t>
    inline void notifier::send(std::format_string<args_t ...> fmt, args_t &&...args)
    {
        auto str = std::format(fmt, std::forward<args_t>(args)...);
        notify(str);
    }

    inline notifier g_notifier;
}