#include "popravljalec.h"
#include <QDebug>
#include <QTextStream>
#include <QFile>
#include <QTextCodec>
#include <QStringList>
#include <QMessageBox>

QStringList Popravljalec::codecs = QStringList() \
        << "Windows-1250" \
        << "ISO-8859-15" \
        << "UTF-8";



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
    if (path.indexOf(":") != -1) path = path.mid(1);
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

            emit info(trUtf8("Uspešno pretvorjeno"), trUtf8("Podnapisi uspešno pretvorjeni!"));
            emit reset();

            return;
        }
    }

    emit error(trUtf8("Nisem uspel pretvoriti podnapisov."));
    emit reset();
}

void Popravljalec::obdelajOdgovor(int r)
{

}
