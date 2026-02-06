#include "attivita.h"

Attivita::Attivita(const QString& titolo,
                   const QString& descrizione,
                   const QDate& data,
                   const QTime& ora)
    : m_titolo(titolo),
      m_descrizione(descrizione),
      m_data(data),
      m_ora(ora)
{
}

Attivita::~Attivita() = default;

QString Attivita::titolo() const {
    return m_titolo;
}

QString Attivita::descrizione() const {
    return m_descrizione;
}

QDate Attivita::data() const {
    return m_data;
}

QTime Attivita::ora() const {
    return m_ora;
}
