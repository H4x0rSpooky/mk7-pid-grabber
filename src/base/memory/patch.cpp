#include <base/memory/patch.hpp>

#include <algorithm>

namespace base::memory
{
    patch::patch(void *address, std::vector<std::uint8_t> value)
    :
        m_address(static_cast<std::uint8_t *>(address)),
        m_new_value(std::move(value)),
        m_original_value(m_new_value.size())
    {
        std::copy_n(m_address, m_new_value.size(), m_original_value.data());
    }

    patch::~patch()
    {
        disable();
    }

    void patch::enable()
    {
        std::copy_n(m_new_value.data(), m_new_value.size(), m_address);
    }

    void patch::disable()
    {
        std::copy_n(m_original_value.data(), m_original_value.size(), m_address);
    }
}