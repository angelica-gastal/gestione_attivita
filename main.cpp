#include "modello/gestioneattivita.h"
#include "modello/lavoro.h"
#include "modello/personale.h"
#include "modello/sociale.h"
#include "modello/visitamedica.h"
#include <QDebug>

int main()
{
    GestioneAttivita gestione;

    gestione.aggiungi(
        std::make_unique<Lavoro>(
            "Rixunionee",
            "Sprint planning",
            QDate::currentDate(),
            QTime::currentTime(),
            Lavoro::Priorita::Alta));
    gestione.aggiungi(std::make_unique<Personale>(
        "Allenamento",
        "Palestra",
        QDate::currentDate(),
        QTime::currentTime(),
        Personale::Categoria::Sport,
        1, 30));

    gestione.aggiungi(std::make_unique<Sociale>(
        "Cena",
        "Pizza",
        QDate::currentDate(),
        QTime::currentTime(),
        "Ristorante",
        "Amici"));

    gestione.aggiungi(std::make_unique<VisitaMedica>(
        "Controllo",
        "Annuale",
        QDate::currentDate(),
        QTime::currentTime(),
        "Dr. Rossi",
        "Cardiologica"));

    for (int i = 0; i < gestione.numeroAttivita(); ++i)
    {
        qDebug() << gestione.attivita(i)->tipo();
    }
}
