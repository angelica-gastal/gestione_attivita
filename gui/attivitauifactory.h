#ifndef ATTIVITAUIFACTORY_H
#define ATTIVITAUIFACTORY_H

#include <QString>
#include <QWidget>
#include <memory>
#include "modello/attivita.h"

// Factory astratta per costruire l'interfaccia specifica di ciascun tipo di attività
// Implementato dalle concrete factory
class AttivitaUIFactory {
public:
    virtual ~AttivitaUIFactory() {}
    // Costruisce i widget specifici per il tipo di attività
    virtual void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) = 0;
    // Crea un'istanza di Attivita leggendo i valori dai widget del form
    virtual std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) = 0;
};

#endif
