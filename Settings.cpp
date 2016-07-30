#define KROMOPHONE_IMPLEMENT_SETTING
#include "Settings.h"

Setting::Setting(const SettingName &name, const QVariant &defaultValue)
{
    value_ = defaultValue;
    name_ = name;
}

Setting& SettingsCreator::create(const SettingName& setting, const QVariant& defaultValue, bool display)
{
    auto& settings = SettingsCreator::Instance().settings;
    // Should do locking etc here...
    if (!settings.contains(setting)) {
        settings[setting] = new Setting(setting, defaultValue);
        
        
        if (display)
        {
            Instance().displayedSettings_.append(setting);
        }
        
        QObject::connect(settings[setting], SIGNAL(valueChanged(QVariant)), &Instance(), SLOT(cppChanged(QVariant)));
    }
    
    return *settings[setting];
}

Setting& SettingsCreator::get(const SettingName& setting)
{
    return *Instance().settings[setting];
}

QQmlPropertyMap* SettingsCreator::qmlSettingMap()
{
    // For android, the settings map needs to be in the QML Engine's thread, and
    // we can't use move to thread to get it there, so we'll create it when it's
    // called for by qml.
    static QQmlPropertyMap* qmlMap = SettingsCreator::Instance().createPropertyMap();
    return SettingsCreator::Instance().propertyMap;
}

QStringList SettingsCreator::displayedSettings()
{
    return Instance().displayedSettings_;
}

QList<Setting *> SettingsCreator::settingsList()
{
    return Instance().settings.values();
}

void SettingsCreator::cppChanged(const QVariant& newValue)
{
    Setting* setting = (Setting*) QObject::sender();
    
    if (propertyMap != nullptr)
    {
        propertyMap->insert(setting->name(), newValue);
    }
}

void SettingsCreator::qmlChanged(const QString& setting, const QVariant& newValue)
{
    settings[setting]->set(newValue);
}

SettingsCreator::SettingsCreator() : QObject(), propertyMap(nullptr)
{
}

SettingsCreator& SettingsCreator::Instance()
{
    static SettingsCreator* instance = new SettingsCreator;
    return *instance;
}

QQmlPropertyMap* SettingsCreator::createPropertyMap()
{
    QQmlPropertyMap* map = new QQmlPropertyMap;
    
    foreach (const Setting* setting, settings.values())
    {
        map->insert(setting->name(), setting->value());
    }
    
    this->propertyMap = map;
    
    connect(propertyMap, SIGNAL(valueChanged(QString,QVariant)), this, SLOT(qmlChanged(QString,QVariant)));
    return map;
}
