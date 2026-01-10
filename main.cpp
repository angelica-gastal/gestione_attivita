#include <QApplication>
#include <QCoreApplication>
#include "gui/mainwindow.h"
#include "gui/tema.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCoreApplication::setOrganizationName("GestioneAttivita");
    QCoreApplication::setApplicationName("GestioneAttivita");

    // Applica il tema salvato all'avvio
    TemaUtil::applicaTema(TemaUtil::caricaTema());

    MainWindow w;
    w.show();

    return a.exec();
}
