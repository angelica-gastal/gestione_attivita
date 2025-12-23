#include "lavoro.h"

Lavoro::Lavoro(const QString& titolo,
               const QString& descrizione,
               const QDate& data,
               const QTime& ora,
               Priorita priorita)
    : Attivita(titolo, descrizione, data, ora),
      m_priorita(priorita)
{
}

QString Lavoro::tipo() const {
    return "Lavoro";
}

Lavoro::Priorita Lavoro::priorita() const {
    return m_priorita;
}
