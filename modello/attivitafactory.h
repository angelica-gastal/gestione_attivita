#ifndef ATTIVITAFACTORY_H
#define ATTIVITAFACTORY_H

#include <memory>
#include <QString>
#include <QDate>
#include <QTime>
#include "lavoro.h"
#include "personale.h"
#include "sociale.h"
#include "visitamedica.h"

class Attivita;

class AttivitaFactory {
public:
    static std::unique_ptr<Attivita> creaLavoro(
        const QString& titolo,
        const QString& descrizione,
        const QDate& data,
        const QTime& ora,
        Lavoro::Priorita priorita
    );

    static std::unique_ptr<Attivita> creaPersonale(
        const QString& titolo,
        const QString& descrizione,
        const QDate& data,
        const QTime& ora,
        Personale::Categoria categoria,
        int ore = 0,
        int minuti = 0
    );

    static std::unique_ptr<Attivita> creaSociale(
        const QString& titolo,
        const QString& descrizione,
        const QDate& data,
        const QTime& ora,
        const QString& luogo,
        const QString& conChi = {}
    );

    static std::unique_ptr<Attivita> creaVisitaMedica(
        const QString& titolo,
        const QString& descrizione,
        const QDate& data,
        const QTime& ora,
        const QString& medico,
        const QString& tipoVisita
    );

    virtual void accept(AttivitaVisitor* v) = 0;
};

#endif
