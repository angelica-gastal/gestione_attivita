#include "pannellodettagli.h"
#include "creawidgetdettaglivisitor.h"
#include "dettagliwidget.h"
#include "modello/attivita.h"

#include <QVBoxLayout>
#include <QFont>
#include <QPushButton>
#include <QHBoxLayout>

PannelloDettagli::PannelloDettagli(QWidget* parent) 
    : QWidget(parent), currentWidget(nullptr) {
    mainLayout = new QVBoxLayout(this);

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
    editButton = new QPushButton("Modifica", this);
    deleteButton = new QPushButton("Elimina", this);

    mainLayout->addWidget(makeLabel("Titolo"));
    mainLayout->addWidget(titoloLabel);
    mainLayout->addWidget(makeLabel("Descrizione"));
    mainLayout->addWidget(descLabel);
    mainLayout->addWidget(makeLabel("Data e ora"));
    mainLayout->addWidget(dataOraLabel);
    mainLayout->addWidget(makeLabel("Tipo"));
    mainLayout->addWidget(tipoLabel);
    mainLayout->addWidget(makeLabel("Dettagli specifici"));
    
    
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(editButton, &QPushButton::clicked, this, &PannelloDettagli::editRequested);
    connect(deleteButton, &QPushButton::clicked, this, &PannelloDettagli::deleteRequested);
    pulisci();
}

void PannelloDettagli::mostraDettagli(Attivita* att) {
    if (!att) {
        pulisci();
        return;
    }

    // Rimuovi il widget precedente se esiste
    if (currentWidget) {
        mainLayout->removeWidget(currentWidget);
        currentWidget->deleteLater();
        currentWidget = nullptr;
    }

    // Crea il widget specifico usando il visitor
    CreaWidgetDettagliVisitor visitor;
    att->accept(&visitor);
    currentWidget = visitor.prendiWidget();

    titoloLabel->setText(att->titolo());
    descLabel->setText(att->descrizione());
    dataOraLabel->setText(att->data().toString("dd/MM/yyyy") + " " + att->ora().toString("HH:mm"));
    tipoLabel->setText(att->tipo());
    
    // Inserisci il nuovo widget nella posizione corretta (prima dei bottoni)
    if (currentWidget) {
        mainLayout->insertWidget(mainLayout->count() - 2, currentWidget);
    }

    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
}

void PannelloDettagli::pulisci() {
    // Rimuovi il widget specifico se esiste
    if (currentWidget) {
        mainLayout->removeWidget(currentWidget);
        currentWidget->deleteLater();
        currentWidget = nullptr;
    }
    
    titoloLabel->setText("-");
    descLabel->setText("-");
    dataOraLabel->setText("-");
    tipoLabel->setText("-");
    if (editButton) editButton->setEnabled(false);
    if (deleteButton) deleteButton->setEnabled(false);
}
