#include <base/files.hpp>

#include <base/logger.hpp>

namespace base
{
	using namespace CTRPluginFramework;

	files::files()
	{
        auto logger_path = "session.log";
            
        if (File::Open(m_logger, logger_path, File::Mode::WRITE | File::Mode::CREATE | File::Mode::SYNC) != File::OPResult::SUCCESS)
            abort();
        
        m_logger.Clear();

        auto settings_path = "settings.json";
        
        if (File::Open(m_settings, settings_path, File::Mode::READ | File::Mode::WRITE | File::Mode::CREATE | File::Mode::SYNC) != File::OPResult::SUCCESS)
            abort();

        g_files = this;
	}

	files::~files()
	{
        g_files = nullptr;

        m_settings.Close();
		m_logger.Close();
	}

    void files::set_working_directory()
    {        
        auto path = std::string("/luma/plugins");

        // Start from the root
        Directory::ChangeWorkingDirectory("");

        // https://gitlab.com/thepixellizeross/ctrpluginframework/-/blob/develop/Library/source/pluginInit.cpp#L157
        if (FwkSettings::Header->isDefaultPlugin)
        {
            path += "/ActionReplay";

            if (!Directory::IsExists(path))
                Directory::Create(path);

            path += Utils::Format("/%016llX", Process::GetTitleID());

            if (!Directory::IsExists(path))
                Directory::Create(path);
        }
        else
        {
            // Exists already to run the plugin
            path += Utils::Format("/%016llX", Process::GetTitleID());
        }

        path += "/" NAME;

        if (!Directory::IsExists(path))
            Directory::Create(path);

        Directory::ChangeWorkingDirectory(path + "/");
    }
}