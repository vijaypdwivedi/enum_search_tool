#include "searchlist.h"
#include <QUrl>

void SearchList::readFile(QString path)
{
    int count = 0;
    QUrl url = path;
    bool isOpen = false;
    bool isGCIproxy = false;
    if(path.contains("GCIPROXY.H",Qt::CaseInsensitive))
        isGCIproxy = true;
    QFile file(url.toLocalFile());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Fail to read";
        return;
    }
    else
        qDebug()<<"Successfully we can read";
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if(line.contains("{"))
        {
            isOpen = true;
            continue;
        }

        if(line.contains("};"))
        {
            isOpen = false;
            count = 0;
            if(isGCIproxy)
                break;
        }

        if(!isOpen)
            qDebug()<<"Enum OutSide Lines:"<<line;

        if(isOpen) {
            //Inserting ENUM Literals into Map
            if(count == 0) {
                bool ok = false;
                line = line.trimmed();
                QStringList keyStr = line.split('=');
                QString beginLiteral = keyStr.takeFirst();
                QString enumStartValue = keyStr.takeLast();
                enumStartValue = enumStartValue.left(enumStartValue.length()-1);
                count = enumStartValue.toInt(&ok, 16);
                if(!ok)
                    count = enumStartValue.toInt(&ok, 10);

                if(!ok)
                    count = 0;
                beginLiteral = beginLiteral.trimmed();
                stringToValue.insert(beginLiteral,count);
                valueToString.insert(count,beginLiteral);
                stringToString.insert(QString::number(count,10),beginLiteral);
                qDebug()<<"Enum First Literalinfo:"<<beginLiteral<<" "<<count;
                count++;
                continue;

            }else {
                line = line.left(line.length()-1);//remove last character ","
                line = line.trimmed();
                stringToValue.insert(line,count);
                valueToString.insert(count,line);
                stringToString.insert(QString::number(count,10),line);
                qDebug()<<"Enum Remaining Literalinfo:"<<line<<" "<<count;
                count++;
            }

        }

    }
}

QStringList SearchList::getSearchList(QString editTextValue)
{

    bool isInt = false;
    int searchCount = 0;
    int enumLiteralIntValue = 0;
    QStringList List;
    List.clear();
    enumLiteralIntValue = editTextValue.toInt(&isInt,10);
    if(isInt) {
        qDebug()<<"Inside isInt";
        QMapIterator<QString,QString> i(stringToString);
        while (i.hasNext()) {
            i.next();

            if(i.key().contains(editTextValue,Qt::CaseInsensitive)) {
                List.append(i.key());
                searchCount++;
                qDebug()<<"Inside isInt while Key:"<<i.key()<<" Value:"<<i.value();
            }
            if(searchCount == 10)
                break;

        }

    }
    else {
        qDebug()<<"Inside isnotInt";
        QMapIterator<QString, int> i(stringToValue);
        while (i.hasNext()) {
            i.next();
            //qDebug()<<"Inside isNotInt while compare Key:"<<i.key()<<" Value:"<<editTextValue;
            if(i.key().contains(editTextValue,Qt::CaseInsensitive)) {
                List.append(i.key());
                searchCount++;
                qDebug()<<"Inside isNotInt while Key:"<<i.key()<<" Value:"<<i.value();
            }
            if(searchCount == 10)
                break;

        }
    }

    qDebug() << "Message from QML: "<<editTextValue;
    return List;

}

QString SearchList::getEnumLiteralValue(QString txt)
{
    bool isInt = false;
    int enumLiteralIntValue = txt.toInt(&isInt,10);

    if(isInt) {
        if(valueToString.contains(enumLiteralIntValue))
            return valueToString.value(enumLiteralIntValue);
        else
            return "No Such Enumliteral";

    }
    else {
        if(stringToValue.contains(txt))
            return QString::number(stringToValue.value(txt));
        else
            return "No Such Enumliteral";
    }

}
