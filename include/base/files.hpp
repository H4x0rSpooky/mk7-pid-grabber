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
		friend class menu;
		friend class logger;
		friend class settings;
		friend struct features;
		
		CTRPluginFramework::File m_logger;
		CTRPluginFramework::File m_settings;
		CTRPluginFramework::File m_session_log;
	};

	inline files *g_files{};
}