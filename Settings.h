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
    void toggle() { value_ = !value_.toBool(); emit valueChanged(value_); }
    void increment(int amount) { value_ = value_.toInt() + amount; emit valueChanged(value_); }
    void decrement(int amount) { increment(- amount); }
        
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
    static Setting& create(const SettingName& setting, const QVariant& defaultValue = QVariant(), bool display = false);
    static Setting& get(const SettingName& setting);
    static QQmlPropertyMap* qmlSettingMap();
    static QStringList displayedSettings();
    static QList<Setting *> settingsList();
    
private slots:
    void cppChanged(const QVariant& newValue);
    void qmlChanged(const QString& setting, const QVariant& newValue);
    
private:
    SettingsCreator();
    static SettingsCreator& Instance();
    QQmlPropertyMap* createPropertyMap();
    QStringList displayedSettings_;
    QHash<SettingName, Setting*> settings;
    QQmlPropertyMap* propertyMap;
};

#define BASE_KROMOPHONE_SETTING_DECL(n, d, v) inline Setting& n() { return SettingsCreator::create(QStringLiteral(#n), d, v); }

#ifdef KROMOPHONE_IMPLEMENT_SETTING
#define BASE_KROMOPHONE_SETTING(n, d, v) BASE_KROMOPHONE_SETTING_DECL(n, d, v) namespace { Setting& _ ## n = n(); }
#else
#define BASE_KROMOPHONE_SETTING(n, d, v) BASE_KROMOPHONE_SETTING_DECL(n, d, v)
#endif

#define KROMOPHONE_SETTING(n, d) BASE_KROMOPHONE_SETTING(n, d, true)

#define HIDDEN_KROMOPHONE_SETTING(n, d) BASE_KROMOPHONE_SETTING(n, d, false)
#define ADVANCED_KROMOPHONE_SETTING(n, d) HIDDEN_KROMOPHONE_SETTING(n, d)

namespace Settings {
    KROMOPHONE_SETTING(sweep, false)
    KROMOPHONE_SETTING(sweepSize, 100)
    KROMOPHONE_SETTING(average, false)
    KROMOPHONE_SETTING(averageSize, 10)
    KROMOPHONE_SETTING(lockExposure, false)
    KROMOPHONE_SETTING(saturation, 30)
    KROMOPHONE_SETTING(hue, 0)
    KROMOPHONE_SETTING(adjustSaturation, true)

    ADVANCED_KROMOPHONE_SETTING(saturationAdjustment, 1.0)
    
    HIDDEN_KROMOPHONE_SETTING(hiddenDisplay, false)
    HIDDEN_KROMOPHONE_SETTING(headless, false)
    HIDDEN_KROMOPHONE_SETTING(audioDevice, "default")
    HIDDEN_KROMOPHONE_SETTING(v4lDevice, "/dev/video0")
    HIDDEN_KROMOPHONE_SETTING(forceCameraDriver, false)
    HIDDEN_KROMOPHONE_SETTING(bgr, false)
    HIDDEN_KROMOPHONE_SETTING(rotate, 0)
}

#endif // SETTINGS_H
