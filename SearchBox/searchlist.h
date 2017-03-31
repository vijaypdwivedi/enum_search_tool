#ifndef SEARCHLIST_H
#define SEARCHLIST_H
#include <QObject>
#include <QMap>
#include <QQmlContext>
#include <QDebug>
#include <QFile>
#include<QList>
class SearchList:public QObject  {
 Q_OBJECT
 public:
   QMap<QString,int> stringToValue;
   QMap<int,QString> valueToString;
   QMap<QString,QString> stringToString;
   QList<QString> valuesList;
   QStringList searchList;
   QString setDataValue;
   Q_INVOKABLE void readFile(QString path);
   Q_INVOKABLE QStringList getSearchList(QString editTextValue);
   Q_INVOKABLE QString getEnumLiteralValue(QString txt);
};



#endif // SEARCHLIST_H
