#include <base/notifier.hpp>

#include <CTRPluginFramework.hpp>

namespace base
{
    void notifier::notify(std::string str)
    {
        CTRPluginFramework::OSD::Notify(str);
    }
}