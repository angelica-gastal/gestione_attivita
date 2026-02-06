#include "sociale.h"
#include "attivitavisitor.h"

Sociale::Sociale(const QString& titolo,
                 const QString& descrizione,
                 const QDate& data,
                 const QTime& ora,
                 const QString& luogo,
                 const QString& conChi)
    : Attivita(titolo, descrizione, data, ora),
      m_luogo(luogo),
      m_conChi(conChi)
{
}

QString Sociale::tipo() const {
    return "Sociale";
}

void Sociale::accept(AttivitaVisitor* v) {
    v->visit(this);
}

QString Sociale::luogo() const {
    return m_luogo;
}

QString Sociale::conChi() const {
    return m_conChi;
}
