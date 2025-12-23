#include "modello/gestioneattivita.h"
#include "modello/lavoro.h"
#include <QDebug>

int main() {
    GestioneAttivita gestione;

    gestione.aggiungi(
        std::make_unique<Lavoro>(
            "Rixunionee",
            "Sprint planning",
            QDate::currentDate(),
            QTime::currentTime(),
            Lavoro::Priorita::Alta
        )
    );

    qDebug() << gestione.numeroAttivita();
    qDebug() << gestione.attivita(0)->tipo();
}
