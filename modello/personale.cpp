#include "personale.h"

Personale::Personale(const QString& titolo,
                     const QString& descrizione,
                     const QDate& data,
                     const QTime& ora,
                     Categoria categoria,
                     int ore,
                     int minuti)
    : Attivita(titolo, descrizione, data, ora),
      m_categoria(categoria),
      m_orePreviste(ore),
      m_minutiPrevisti(minuti)
{
}

QString Personale::tipo() const {
    return "Personale";
}

Personale::Categoria Personale::categoria() const {
    return m_categoria;
}

int Personale::orePreviste() const {
    return m_orePreviste;
}

int Personale::minutiPrevisti() const {
    return m_minutiPrevisti;
}
