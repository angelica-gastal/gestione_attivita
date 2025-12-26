#ifndef VISITAMEDICA_H
#define VISITAMEDICA_H

#include "attivita.h"

class VisitaMedica : public Attivita {
public:
    VisitaMedica(const QString& titolo,
                 const QString& descrizione,
                 const QDate& data,
                 const QTime& ora,
                 const QString& medico,
                 const QString& tipoVisita);

    QString tipo() const override;

    QString medico() const;
    QString tipoVisita() const;

private:
    QString m_medico;
    QString m_tipoVisita;
};

#endif
