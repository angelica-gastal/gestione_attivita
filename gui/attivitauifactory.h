#ifndef ATTIVITAUIFACTORY_H
#define ATTIVITAUIFACTORY_H

#include <QString>
#include <QWidget>
#include <memory>
#include "modello/attivita.h"

class AttivitaUIFactory {
public:
    virtual ~AttivitaUIFactory() {}
    virtual void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) = 0;
    virtual std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) = 0;
};

#endif
