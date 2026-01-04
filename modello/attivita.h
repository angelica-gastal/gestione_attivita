#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <QString>
#include <QDate>
#include <QTime>
#include "attivitavisitor.h"

class Attivita {
public:
    Attivita(const QString& titolo,
             const QString& descrizione,
             const QDate& data,
             const QTime& ora);

    virtual ~Attivita();

    QString titolo() const;
    QString descrizione() const;
    QDate data() const;
    QTime ora() const;

    virtual QString tipo() const = 0;
    virtual void accept(AttivitaVisitor* v) = 0;

protected:
    QString m_titolo; //membri m_
    QString m_descrizione;
    QDate m_data;
    QTime m_ora;
};



#endif