#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>
#include <QHash>
#include <QQmlPropertyMap>

typedef QString SettingName;

class Setting : public QObject
{
    friend class SettingsCreator;
    Q_OBJECT
    Q_PROPERTY(QVariant value READ value WRITE set NOTIFY valueChanged)
    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
        
public:
    Setting(const SettingName& name, const QVariant& defaultValue = QVariant());
    
    const QVariant& value() const { return value_; }
    const SettingName& name() const { return name_; }
    
    void set(const QVariant& value) { value_ = value; emit valueChanged(value_);}
        
signals:
    void valueChanged(const QVariant& value);
    void nameChanged(const QString& name);
    
public slots:
    
private:
    QVariant value_;
    SettingName name_;
};

class SettingsCreator : public QObject
{
    Q_OBJECT
public:
    static Setting& create(const SettingName& setting, const QVariant& defaultValue = QVariant());
    static Setting& get(const SettingName& setting);
    static QQmlPropertyMap* qmlSettingMap();
    
private slots:
    void cppChanged(const QVariant& newValue);
    void qmlChanged(const QString& setting, const QVariant& newValue);
    
private:
    SettingsCreator();
    static SettingsCreator& Instance();
    QHash<SettingName, Setting*> settings;
    QQmlPropertyMap propertyMap;
};

#define KROMOPHONE_SETTING(n, d) inline Setting& n() { return SettingsCreator::create(QStringLiteral(#n), d); } \
    namespace { Setting& _ ## n = n(); }

namespace Settings {
    KROMOPHONE_SETTING(sweep, false)
    KROMOPHONE_SETTING(sweepSize, 100)
    KROMOPHONE_SETTING(average, false)
    KROMOPHONE_SETTING(averageSize, 10)
    KROMOPHONE_SETTING(hiddenDisplay, false)
}

#endif // SETTINGS_H