#include "attivitafactory.h"
#include "lavoro.h"
#include "personale.h"
#include "sociale.h"
#include "visitamedica.h"

std::unique_ptr<Attivita> AttivitaFactory::creaLavoro(
    const QString& titolo,
    const QString& descrizione,
    const QDate& data,
    const QTime& ora,
    Lavoro::Priorita priorita
) {
    return std::make_unique<Lavoro>(titolo, descrizione, data, ora, priorita);
}

std::unique_ptr<Attivita> AttivitaFactory::creaPersonale(
    const QString& titolo,
    const QString& descrizione,
    const QDate& data,
    const QTime& ora,
    Personale::Categoria categoria,
    int ore,
    int minuti
) {
    return std::make_unique<Personale>(titolo, descrizione, data, ora, categoria, ore, minuti);
}

std::unique_ptr<Attivita> AttivitaFactory::creaSociale(
    const QString& titolo,
    const QString& descrizione,
    const QDate& data,
    const QTime& ora,
    const QString& luogo,
    const QString& conChi
) {
    return std::make_unique<Sociale>(titolo, descrizione, data, ora, luogo, conChi);
}

std::unique_ptr<Attivita> AttivitaFactory::creaVisitaMedica(
    const QString& titolo,
    const QString& descrizione,
    const QDate& data,
    const QTime& ora,
    const QString& medico,
    const QString& tipoVisita
) {
    return std::make_unique<VisitaMedica>(titolo, descrizione, data, ora, medico, tipoVisita);
}
