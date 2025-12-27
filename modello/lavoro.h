#ifndef LAVORO_H
#define LAVORO_H

#include "attivita.h"

class AttivitaVisitor;

class Lavoro: public Attivita {
public:
    enum class Priorita { Alta, Media, Bassa };

    Lavoro(const QString& titolo,
                 const QString& descrizione,
                 const QDate& data,
                 const QTime& ora,
                 Priorita priorita);

    QString tipo() const override;
    void accept(AttivitaVisitor* v) override;

    Priorita priorita() const;

private:
    Priorita m_priorita;
};



#endif