#include "pannellodettagli.h"
#include "dettaglioattivitavisitor.h"
#include "modello/attivita.h"

#include <QVBoxLayout>
#include <QFont>
#include <QPushButton>
#include <QHBoxLayout>

PannelloDettagli::PannelloDettagli(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    auto makeLabel = [](const QString& title) {
        QLabel* l = new QLabel(title);
        QFont f = l->font();
        f.setBold(true);
        l->setFont(f);
        return l;
    };

    titoloLabel = new QLabel(this);
    descLabel = new QLabel(this);
    descLabel->setWordWrap(true);
    dataOraLabel = new QLabel(this);
    tipoLabel = new QLabel(this);
    specificLabel = new QLabel(this);
    specificLabel->setWordWrap(true);
    editButton = new QPushButton("Modifica", this);
    deleteButton = new QPushButton("Elimina", this);

    layout->addWidget(makeLabel("Titolo"));
    layout->addWidget(titoloLabel);
    layout->addWidget(makeLabel("Descrizione"));
    layout->addWidget(descLabel);
    layout->addWidget(makeLabel("Data e ora"));
    layout->addWidget(dataOraLabel);
    layout->addWidget(makeLabel("Tipo"));
    layout->addWidget(tipoLabel);
    layout->addWidget(makeLabel("Dettagli specifici"));
    layout->addWidget(specificLabel);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    layout->addLayout(buttonsLayout);
    layout->addStretch();

    setLayout(layout);

    connect(editButton, &QPushButton::clicked, this, &PannelloDettagli::editRequested);
    connect(deleteButton, &QPushButton::clicked, this, &PannelloDettagli::deleteRequested);
    pulisci();
}

void PannelloDettagli::mostraDettagli(Attivita* att) {
    if (!att) {
        pulisci();
        return;
    }

    DettaglioAttivitaVisitor visitor;
    att->accept(&visitor);

    titoloLabel->setText(att->titolo());
    descLabel->setText(att->descrizione());
    dataOraLabel->setText(att->data().toString("dd/MM/yyyy") + " " + att->ora().toString("HH:mm"));
    tipoLabel->setText(att->tipo());
    specificLabel->setText(visitor.specific.isEmpty() ? "-" : visitor.specific);

    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void PannelloDettagli::pulisci() {
    titoloLabel->setText("-");
    descLabel->setText("-");
    dataOraLabel->setText("-");
    tipoLabel->setText("-");
    specificLabel->setText("-");
    if (editButton) editButton->setEnabled(false);
    if (deleteButton) deleteButton->setEnabled(false);
}
