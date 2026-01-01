// SPDX-License-Identifier: MIT
#include "attivitaform.h"

#include <QDate>
#include <QHBoxLayout>
#include <QLabel>
#include <QLayoutItem>
#include <QPushButton>
#include <QVBoxLayout>

#include "compilaformvisitor.h"

AttivitaForm::AttivitaForm(QWidget* parent) : QWidget(parent) {
    titoloEdit = new QLineEdit(this);
    descEdit = new QTextEdit(this);
    dataEdit = new QDateEdit(QDate::currentDate(), this);
    oraEdit = new QTimeEdit(QTime::currentTime(), this);
    tipoCombo = new QComboBox(this);

    tipoCombo->addItem("Personale");
    tipoCombo->addItem("Lavoro");
    tipoCombo->addItem("Sociale");
    tipoCombo->addItem("VisitaMedica");

    specificContainer = new QWidget(this);
    specificLayout = new QVBoxLayout(specificContainer);
    specificContainer->setLayout(specificLayout);

    QPushButton* saveBtn = new QPushButton("Salva", this);
    QPushButton* cancelBtn = new QPushButton("Annulla", this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Titolo:"));
    mainLayout->addWidget(titoloEdit);
    mainLayout->addWidget(new QLabel("Descrizione:"));
    mainLayout->addWidget(descEdit);
    mainLayout->addWidget(new QLabel("Data:"));
    mainLayout->addWidget(dataEdit);
    mainLayout->addWidget(new QLabel("Ora:"));
    mainLayout->addWidget(oraEdit);
    mainLayout->addWidget(new QLabel("Tipo attività:"));
    mainLayout->addWidget(tipoCombo);
    mainLayout->addWidget(specificContainer);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(cancelBtn);
    mainLayout->addLayout(btnLayout);
    setLayout(mainLayout);

    connect(tipoCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &AttivitaForm::onTipoChanged);
    connect(saveBtn, &QPushButton::clicked, this, &AttivitaForm::onSaveClicked);
    connect(cancelBtn, &QPushButton::clicked, this, &AttivitaForm::onCancelClicked);
}

void AttivitaForm::onTipoChanged(int) {
    clearSpecificUI();
    buildSpecificUI(tipoCombo->currentText());
}

void AttivitaForm::onSaveClicked() {
    const QString tipo = tipoCombo->currentText();
    const QString titolo = titoloEdit->text();
    const QString descrizione = descEdit->toPlainText();
    const QDate data = dataEdit->date();
    const QTime ora = oraEdit->time();

    if (!activeFactory) return;

    auto nuova = activeFactory->createFromForm(titolo, descrizione, data, ora, this);
    emit saved(nuova.release(), editingIndex);
}

void AttivitaForm::onCancelClicked() {
    emit cancelled();
}

void AttivitaForm::loadForCreate() {
    editingIndex = -1;
    titoloEdit->clear();
    descEdit->clear();
    dataEdit->setDate(QDate::currentDate());
    oraEdit->setTime(QTime::currentTime());
    tipoCombo->setCurrentIndex(0);
    clearSpecificUI();
    buildSpecificUI(tipoCombo->currentText());
}

void AttivitaForm::loadForEdit(int index, Attivita* existing) {
    editingIndex = index;
    if (!existing) return;

    CompilaFormVisitor visitor(this);
    existing->accept(&visitor);
}

void AttivitaForm::buildSpecificUI(QString tipo) {
    if (tipo == "Lavoro") {
        lavoroFactory = std::make_unique<LavoroUIFactory>();
        activeFactory = lavoroFactory.get();
        activeFactory->buildSpecificUI(specificContainer, specificLayout);
    } else if (tipo == "Personale") {
        personaleFactory = std::make_unique<PersonaleUIFactory>();
        activeFactory = personaleFactory.get();
        activeFactory->buildSpecificUI(specificContainer, specificLayout);
    } else if (tipo == "Sociale") {
        socialeFactory = std::make_unique<SocialeUIFactory>();
        activeFactory = socialeFactory.get();
        activeFactory->buildSpecificUI(specificContainer, specificLayout);
    } else if (tipo == "VisitaMedica") {
        visitaMedicaFactory = std::make_unique<VisitaMedicaUIFactory>();
        activeFactory = visitaMedicaFactory.get();
        activeFactory->buildSpecificUI(specificContainer, specificLayout);
    } else {
        activeFactory = nullptr;
    }
}

void AttivitaForm::clearSpecificUI() {
    QLayoutItem* item = nullptr;
    while ((item = specificLayout->takeAt(0)) != nullptr) {
        if (item->widget()) item->widget()->deleteLater();
        delete item;
    }

    activeFactory = nullptr;
    lavoroFactory.reset();
    personaleFactory.reset();
    socialeFactory.reset();
    visitaMedicaFactory.reset();
}
