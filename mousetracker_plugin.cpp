#include "mousetracker_plugin.h"
#include "mousetracker.h"

#include <qqml.h>

void MousetrackerPlugin::registerTypes(const char *uri)
{
    // @uri com.mousetrackeritem
    qmlRegisterType<MouseTracker>(uri, 1, 0, "MouseTrackerItem");
}

