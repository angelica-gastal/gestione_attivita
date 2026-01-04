#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#ifndef SOCIALEUIFACTORY_H
#define SOCIALEUIFACTORY_H

#include "attivitauifactory.h"
#include "modello/sociale.h"

// Factory concreta per costruire l'interfaccia specifica di Sociale
class SocialeUIFactory : public AttivitaUIFactory {
public:
    SocialeUIFactory() : luogoEdit(nullptr), conChiEdit(nullptr) {}

    void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) override {
        QLabel* luogoLabel = new QLabel("Luogo:", parent);
        luogoEdit = new QLineEdit(parent);
        layout->addWidget(luogoLabel);
        layout->addWidget(luogoEdit);

        QLabel* conChiLabel = new QLabel("Con chi:", parent);
        conChiEdit = new QLineEdit(parent);
        layout->addWidget(conChiLabel);
        layout->addWidget(conChiEdit);
    }

    std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) override {
        Q_UNUSED(parent);
        QString luogo = luogoEdit ? luogoEdit->text() : "";
        QString conChi = conChiEdit ? conChiEdit->text() : "";
        return std::make_unique<Sociale>(titolo, descrizione, data, ora, luogo, conChi);
    }

    QLineEdit* luogoEdit;
    QLineEdit* conChiEdit;
};

#endif
