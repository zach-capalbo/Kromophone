#include "Settings.h"

Setting::Setting(const SettingName &name, const QVariant &defaultValue)
{
    value_ = defaultValue;
    name_ = name;
}

Setting& SettingsCreator::create(const SettingName& setting, const QVariant& defaultValue)
{
    auto& settings = SettingsCreator::Instance().settings;
    // Should do locking etc here...
    if (!settings.contains(setting)) {
        settings[setting] = new Setting(setting, defaultValue);
        Instance().propertyMap.insert(setting, defaultValue);
        
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
    return &SettingsCreator::Instance().propertyMap;
}

void SettingsCreator::cppChanged(const QVariant& newValue)
{
    Setting* setting = (Setting*) QObject::sender();
    propertyMap.insert(setting->name(), newValue);
}

void SettingsCreator::qmlChanged(const QString& setting, const QVariant& newValue)
{
    settings[setting]->set(newValue);
}

SettingsCreator::SettingsCreator() : QObject()
{
    connect(&propertyMap, SIGNAL(valueChanged(QString,QVariant)), this, SLOT(qmlChanged(QString,QVariant)));
}

SettingsCreator& SettingsCreator::Instance()
{
    static SettingsCreator* instance = new SettingsCreator;
    return *instance;
}
