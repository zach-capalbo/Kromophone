#include "ArgParser.h"
#include "Settings.h"

#include <QDebug>

ArgParser::ArgParser(const QStringList& arguments)
{
    parse(arguments);
}

QVariant ArgParser::operator[](const QString& key)
{
    return otherArgs[key];
}

bool ArgParser::contains(const QString &key)
{
    return otherArgs.contains(key);
}

void ArgParser::parse(QStringList args)
{
    QSet<QString> settingNames = SettingsCreator::qmlSettingMap()->keys().toSet();
    
    while (!args.empty())
    {
        QString p = args.takeFirst();
        
        if (!p.startsWith("--"))
        {
            qDebug() << "Unknown argument: " << p;
            continue;
        }
        
        p = p.right(p.size() - 2);
        QVariant val(true);
        
        if (!args.empty() && !args.first().startsWith("--"))
        {
            val = args.takeFirst();
        }
        
        if (settingNames.contains(p))
        {
            SettingsCreator::get(p).set(val);
        }
        else
        {
            otherArgs[p] = val;
        }
    }
}
