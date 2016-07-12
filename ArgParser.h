#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <QStringList>
#include <QVariantHash>

class ArgParser
{
public:
    ArgParser(const QStringList& arguments = QStringList());
    void parse(QStringList arguments);
    
    bool contains(const QString& key);
    QVariant operator[](const QString& key);
    
private:
    QVariantHash otherArgs;
};

#endif // ARGPARSER_H
