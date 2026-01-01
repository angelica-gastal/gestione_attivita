#include "pannellodettagli.h"
#include "dettaglioattivitavisitor.h"
#include "modello/attivita.h"

#include <QVBoxLayout>
#include <QFont>

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
    layout->addStretch();

    setLayout(layout);
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
}

void PannelloDettagli::pulisci() {
    titoloLabel->setText("-");
    descLabel->setText("-");
    dataOraLabel->setText("-");
    tipoLabel->setText("-");
    specificLabel->setText("-");
}
