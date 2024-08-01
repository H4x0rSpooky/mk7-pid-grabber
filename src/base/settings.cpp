#include <base/settings.hpp>

#include <base/files.hpp>
#include <base/logger.hpp>

#include <glaze/glaze.hpp>

#include <CTRPluginFramework.hpp>

namespace base
{
	using namespace CTRPluginFramework;

	bool settings::load()
	{
		return load_impl() ? true : reset();
	}

	bool settings::store()
	{
		if (g_files->m_settings.Clear() == File::OPResult::SUCCESS)
		{
			if (auto const expect = glz::write_json(m_options); expect.has_value())
			{
				auto const dump = expect.value();

				return g_files->m_settings.Write(dump.data(), dump.size()) == File::OPResult::SUCCESS;
			}
		}

		return false;
	}

	bool settings::reset()
	{
		if (g_files->m_settings.Clear() == File::OPResult::SUCCESS)
		{
			auto const opts = options{};

			if (auto const expect = glz::write_json(opts); expect.has_value())
			{
				auto const dump = expect.value();

				if (g_files->m_settings.Write(dump.data(), dump.size()) == File::OPResult::SUCCESS)
				{
					m_options = opts;
					
					return true;
				}
			}
		}

        return false;
	}

	bool settings::load_impl()
	{
		if (auto const size = g_files->m_settings.GetSize(); size > 0)
		{
			if (auto const buffer = std::make_unique<char []>(size))
			{
				if (g_files->m_settings.Read(buffer.get(), size) == File::OPResult::SUCCESS)
				{
					if (auto const expect = glz::read_json<options>(buffer.get()); expect.has_value())
					{
						m_options = expect.value();
						
						return true;
					}
				}
			}
		}

        return false;
	}
}