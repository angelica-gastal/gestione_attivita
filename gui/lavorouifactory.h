#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#ifndef LAVOROUIFACTORY_H
#define LAVOROUIFACTORY_H

#include "attivitauifactory.h"
#include "modello/lavoro.h"

class LavoroUIFactory : public AttivitaUIFactory {
public:
    LavoroUIFactory() : prioritaCombo(nullptr) {}

    void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) override {
        QLabel* prioritaLabel = new QLabel("Priorità:", parent);
        prioritaCombo = new QComboBox(parent);
        prioritaCombo->addItem("Alta");
        prioritaCombo->addItem("Media");
        prioritaCombo->addItem("Bassa");
        layout->addWidget(prioritaLabel);
        layout->addWidget(prioritaCombo);
    }

    std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) override {
        Q_UNUSED(parent);
        int idx = prioritaCombo ? prioritaCombo->currentIndex() : 0;
        Lavoro::Priorita priorita = static_cast<Lavoro::Priorita>(idx); // Assumendo enum 0=bassa,1=media,2=alta
        return std::make_unique<Lavoro>(titolo, descrizione, data, ora, priorita);
    }

    QComboBox* prioritaCombo;
};

#endif
