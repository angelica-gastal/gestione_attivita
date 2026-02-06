#ifndef SOCIALE_H
#define SOCIALE_H

#include "attivita.h"

class AttivitaVisitor;

class Sociale : public Attivita {
public:
    Sociale(const QString& titolo,
            const QString& descrizione,
            const QDate& data,
            const QTime& ora,
            const QString& luogo,
            const QString& conChi = {});

    QString tipo() const override;
    void accept(AttivitaVisitor* v) override;

    QString luogo() const;
    QString conChi() const;

private:
    QString m_luogo;
    QString m_conChi;
};

#endif
