#include <base/hook_types/vmt_hook.hpp>

#include <base/logger.hpp>

namespace base::hook_types
{	
    vmt_hook::vmt_hook(std::string_view name, void *obj, size_t num_funcs)
    :
		m_name(std::move(name)),
		m_object(static_cast<void ***>(obj)),
		m_num_funcs(num_funcs + 1),
		m_original_table(*m_object),
		m_new_table(std::make_unique<void *[]>(m_num_funcs))
	{
		std::copy_n(m_original_table - 1, m_num_funcs, m_new_table.get());
	}

	vmt_hook::~vmt_hook()
	{
	}

	void vmt_hook::hook(size_t index, void *func)
	{
		m_new_table[index + 1] = func;
	}

	void vmt_hook::unhook(size_t index)
	{
		m_new_table[index + 1] = m_original_table[index];
	}

	void vmt_hook::enable()
	{
		*m_object = m_new_table.get() + 1;
	}

	void vmt_hook::disable()
	{
		*m_object = m_original_table;
	}
}