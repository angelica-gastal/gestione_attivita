#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#ifndef VISITAMEDICAUIFACTORY_H
#define VISITAMEDICAUIFACTORY_H

#include "attivitauifactory.h"
#include <QLineEdit>
#include <QVBoxLayout>
#include "modello/visitamedica.h"

class VisitaMedicaUIFactory : public AttivitaUIFactory {
public:
    VisitaMedicaUIFactory() : medicoEdit(nullptr), tipoVisitaEdit(nullptr) {}

    void buildSpecificUI(QWidget* parent, QVBoxLayout* layout) override {
        QLabel* labelMedico = new QLabel("Medico:", parent);
        medicoEdit = new QLineEdit(parent);
        layout->addWidget(labelMedico);
        layout->addWidget(medicoEdit);

        QLabel* labelTipoVisita = new QLabel("Tipo visita:", parent);
        tipoVisitaEdit = new QLineEdit(parent);
        layout->addWidget(labelTipoVisita);
        layout->addWidget(tipoVisitaEdit);
    }

    std::unique_ptr<Attivita> createFromForm(const QString& titolo, const QString& descrizione, const QDate& data, const QTime& ora, QWidget* parent) override {
        Q_UNUSED(parent);
        QString medico = medicoEdit ? medicoEdit->text() : "";
        QString tipoVisita = tipoVisitaEdit ? tipoVisitaEdit->text() : "";
        return std::make_unique<VisitaMedica>(titolo, descrizione, data, ora, medico, tipoVisita);
    }

    QLineEdit* medicoEdit;
    QLineEdit* tipoVisitaEdit;
};

#endif
