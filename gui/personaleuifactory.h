#include <QLabel>
#include <QVBoxLayout>
#include <QComboBox>
#include <QSpinBox>
#ifndef PERSONALEUIFACTORY_H
#define PERSONALEUIFACTORY_H

#include "attivitauifactory.h"
#include "modello/personale.h"

class PersonaleUIFactory : public AttivitaUIFactory {
public:
    PersonaleUIFactory() : categoriaCombo(nullptr), oreSpin(nullptr), minutiSpin(nullptr) {}

    void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) override {
        QLabel* catLabel = new QLabel("Categoria:", parent);
        categoriaCombo = new QComboBox(parent);
        categoriaCombo->addItem("Casa");
        categoriaCombo->addItem("Hobby");
        categoriaCombo->addItem("Sport");
        categoriaCombo->addItem("Commissioni");
        layout->addWidget(catLabel);
        layout->addWidget(categoriaCombo);

        QLabel* oreLabel = new QLabel("Ore previste:", parent);
        oreSpin = new QSpinBox(parent);
        oreSpin->setRange(0, 24);
        layout->addWidget(oreLabel);
        layout->addWidget(oreSpin);

        QLabel* minLabel = new QLabel("Minuti previsti:", parent);
        minutiSpin = new QSpinBox(parent);
        minutiSpin->setRange(0, 59);
        layout->addWidget(minLabel);
        layout->addWidget(minutiSpin);
    }

    std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) override {
        Q_UNUSED(parent);
        int idx = categoriaCombo ? categoriaCombo->currentIndex() : 0;
        Personale::Categoria cat = static_cast<Personale::Categoria>(idx);
        int ore = oreSpin ? oreSpin->value() : 0;
        int min = minutiSpin ? minutiSpin->value() : 0;
        return std::make_unique<Personale>(titolo, descrizione, data, ora, cat, ore, min);
    }

    QComboBox* categoriaCombo;
    QSpinBox* oreSpin;
    QSpinBox* minutiSpin;
};

#endif
