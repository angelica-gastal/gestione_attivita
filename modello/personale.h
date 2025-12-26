#ifndef PERSONALE_H
#define PERSONALE_H

#include "attivita.h"

class Personale : public Attivita {
public:
    enum class Categoria { Casa, Hobby, Sport, Commissioni };

    Personale(const QString& titolo,
              const QString& descrizione,
              const QDate& data,
              const QTime& ora,
              Categoria categoria,
              int ore = 0,
              int minuti = 0);

    QString tipo() const override;

    Categoria categoria() const;
    int orePreviste() const;
    int minutiPrevisti() const;

private:
    Categoria m_categoria;
    int m_orePreviste;
    int m_minutiPrevisti;
};

#endif
