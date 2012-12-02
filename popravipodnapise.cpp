#include "popravipodnapise.h"
#include "ui_popravipodnapise.h"
#include <QtGui/QDropEvent>
#include <QtCore/QMimeData>
#include <QtCore/QUrl>
#include <QtCore/QList>
#include <QDebug>
#include <QMessageBox>

PopraviPodnapise::PopraviPodnapise(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PopraviPodnapise)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
}

PopraviPodnapise::~PopraviPodnapise()
{
    delete ui;
}

void PopraviPodnapise::dragEnterEvent(QDragEnterEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}

void PopraviPodnapise::dragMoveEvent(QDragMoveEvent* event)
{
    // if some actions should not be usable, like move, this code must be adopted
    event->acceptProposedAction();
}


void PopraviPodnapise::dragLeaveEvent(QDragLeaveEvent* event)
{
    event->accept();
}

void PopraviPodnapise::dropEvent(QDropEvent * event)
{
    const QMimeData* mimeData = event->mimeData();

    if (mimeData->hasUrls())
    {
        QList<QUrl> urlList = mimeData->urls();

        if (urlList.size() > 1)
        {
            QMessageBox::information(this, trUtf8("Preveč datotek"), trUtf8("Prenesli ste preveč datotek, popravite lahko le en podnapis naenkrat."));
            return;
        }

        if (urlList.size() < 1)
        {
            QMessageBox::information(this, trUtf8("Datoteka ne obstaja"), trUtf8("Prosimo, uporabite veljavno datoteko."));
            return;
        }

        this->setAcceptDrops(false);
        emit datotekaIzbrana(urlList.at(0).path());
    }
}

void PopraviPodnapise::prikaziPopravke(QStringList *popravki)
{
    this->ui->stackedWidget->setCurrentIndex(1);
}

void PopraviPodnapise::reset()
{
    this->setAcceptDrops(true);
    this->ui->stackedWidget->setCurrentIndex(0);
}

void PopraviPodnapise::error(QString message)
{
    QMessageBox::information(this, trUtf8("Napaka"), message);
    reset();
}

void PopraviPodnapise::info(QString naslov, QString message)
{
    QMessageBox::information(this, naslov, message);
}
