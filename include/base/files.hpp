#pragma once

#include <CTRPluginFramework.hpp>

namespace base
{
	class files
	{
	public:
		explicit files();
		~files();

		static void set_working_directory();

	private:
		friend class logger;
		friend class settings;
		
		CTRPluginFramework::File m_logger;
		CTRPluginFramework::File m_settings;
	};

	inline files *g_files{};
}