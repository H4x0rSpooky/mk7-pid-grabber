#pragma once

#include <cstdint>
#include <vector>

namespace base::memory
{
    class patch
    {
    public:
        patch(void *address, std::vector<std::uint8_t> value);
        ~patch();

        void enable();
        void disable();

    private:
        std::uint8_t *m_address;
        std::vector<std::uint8_t> m_new_value;
        std::vector<std::uint8_t> m_original_value;
    };
}