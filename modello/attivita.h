#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <QString>
#include <QDate>
#include <QTime>

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

    void setTitolo(const QString& t);
    void setDescrizione(const QString& d);

    virtual QString tipo() const = 0;

protected:
    QString m_titolo; //membri m_
    QString m_descrizione;
    QDate m_data;
    QTime m_ora;
};



#endif