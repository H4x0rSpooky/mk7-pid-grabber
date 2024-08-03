#include <3ds.h>

#include <base/files.hpp>
#include <base/settings.hpp>
#include <base/menu.hpp>
#include <base/pointers.hpp>
#include <base/hooking.hpp>
#include <base/patches.hpp>

#include <base/services/rainbow_service.hpp>

namespace CTRPluginFramework
{
    using namespace base;

    int main()
    {
        auto files_instance = std::make_unique<files>();

        g_settings.load();

        auto pointers_instance = std::make_unique<pointers>();
        
        auto hooking_instance = std::make_unique<hooking>();

        auto patches_instance = std::make_unique<patches>();
       
        auto menu_instance = std::make_unique<menu>();
        
        auto rainbow_service_instance = std::make_unique<rainbow_service>();
        
        g_hooking->enable();
        
        g_menu->run();

        g_hooking->disable();
        
        rainbow_service_instance.reset();

        menu_instance.reset();

        patches_instance.reset();
        
        hooking_instance.reset();
        
        pointers_instance.reset();
        
        g_settings.store();
        
        files_instance.reset();

        return EXIT_SUCCESS;
    }

    void PatchProcess(FwkSettings &settings)
    {
        settings.ThreadPriority = 0x3E;
        settings.WaitTimeToBoot = Time::Zero;

        settings.CachedDrawMode = false;
        settings.TryLoadSDSounds = false;
		settings.AllowActionReplay = false;
		settings.AllowSearchEngine = false;

        settings.UseGameHidMemory = true;

        settings.SetThemeDefault();

        files::set_working_directory();
    }
}
