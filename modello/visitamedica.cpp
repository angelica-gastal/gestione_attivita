#include "visitamedica.h"

VisitaMedica::VisitaMedica(const QString& titolo,
                           const QString& descrizione,
                           const QDate& data,
                           const QTime& ora,
                           const QString& medico,
                           const QString& tipoVisita)
    : Attivita(titolo, descrizione, data, ora),
      m_medico(medico),
      m_tipoVisita(tipoVisita)
{
}

QString VisitaMedica::tipo() const {
    return "Visita Medica";
}

QString VisitaMedica::medico() const {
    return m_medico;
}

QString VisitaMedica::tipoVisita() const {
    return m_tipoVisita;
}
