#ifndef POPRAVLJALEC_H
#define POPRAVLJALEC_H

#include <QObject>
#include <QStringList>

class Popravljalec : public QObject
{
    Q_OBJECT
public:
    explicit Popravljalec(QObject *parent = 0);
    
signals:
    void popravkiNaVoljo(QStringList *popravki);
    void error(QString description);
    void finished();
public slots:
    void obdelajDatoteko(QString path);
    void obdelajOdgovor(int r);

private:
    static QStringList codecs;
};

#endif // POPRAVLJALEC_H
