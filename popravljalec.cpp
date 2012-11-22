#include "popravljalec.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QStringList>

QStringList Popravljalec::codecs = QStringList() \
        // << "Windows-1250" \
       // << "ISO-8859-15" \
       // << "UTF-8";
        << "Windows-1250";



QString newName(QString oldName)
{
    int idx = oldName.lastIndexOf('/');
    int idx2 = oldName.lastIndexOf('\\');
    if (idx2 > idx) idx = idx2;
    if (idx < 0) idx = 0;

    QString newName = QString(oldName);
    newName.insert(idx + 1, "original-");
    return newName;
}


Popravljalec::Popravljalec(QObject *parent) :
    QObject(parent)
{
}

void Popravljalec::obdelajDatoteko(QString path)
{
    qDebug() << "Obdelujemo " << path;

    QFile origFile(path);

    if (!origFile.open(QIODevice::ReadOnly)) {
        emit error(origFile.errorString());
    }

    if (origFile.size() > 5243000)
    {
        emit error("Datoteka prevelika!");
        return;
    }

    QTextCodec *codec;
    QString ch = QString::fromUtf8("č");
    QString sh = QString::fromUtf8("š");
    QString zh = QString::fromUtf8("ž");
    for (int i = 0; i < codecs.size(); ++i)
    {
        QTextStream textStream(&origFile);

        codec = QTextCodec::codecForName(codecs.at(i).toAscii());
        textStream.setCodec(codec);

        QString lines = textStream.readAll();
        origFile.close();

        qDebug() << lines;

        if (lines.indexOf(ch) > -1 && \
                lines.indexOf(sh) > -1 && \
                lines.indexOf(zh) > -1)
        {
            qDebug() << "Found it!" << codecs.at(i);

            // save
            QString fileName = origFile.fileName();
            origFile.rename(newName(origFile.fileName()));

            QFile newFile(fileName);
            if (!newFile.open(QIODevice::WriteOnly | QIODevice::Truncate))
            {
                emit error(origFile.errorString());
            }

            QTextStream streamOut(&newFile);
            streamOut.setCodec("UTF-8");
            streamOut.setGenerateByteOrderMark(true);
            streamOut << lines;
            streamOut.flush();

            newFile.close();

            return;
        }
    }

}

void Popravljalec::obdelajOdgovor(int r)
{

}
