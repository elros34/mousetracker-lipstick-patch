#ifndef MOUSETRACKER_PLUGIN_H
#define MOUSETRACKER_PLUGIN_H

#include <QQmlExtensionPlugin>

class MousetrackerPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri) override;
};

#endif // MOUSETRACKER_PLUGIN_H
