#include "dettagliwidget.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFont>

namespace {
QLabel* createBoldLabel(const QString& text) {
    QLabel* label = new QLabel(text);
    QFont font = label->font();
    font.setBold(true);
    label->setFont(font);
    return label;
}
}

DettagliWidget::DettagliWidget(QWidget* parent)
    : QWidget(parent) {
    setContentsMargins(0, 0, 0, 0);
}

LavoroDettagliWidget::LavoroDettagliWidget(const QString& priorita, QWidget* parent)
    : DettagliWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);


    QFormLayout* formLayout = new QFormLayout();

    prioritaLabel = new QLabel(priorita);
    formLayout->addRow(createBoldLabel("Priorità:"), prioritaLabel);

    layout->addLayout(formLayout);
    setLayout(layout);
}

PersonaleDettagliWidget::PersonaleDettagliWidget(const QString& categoria,
                                                  int ore,
                                                  int minuti,
                                                  QWidget* parent)
    : DettagliWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    
    QFormLayout* formLayout = new QFormLayout();

    categoriaLabel = new QLabel(categoria);
    durataLabel = new QLabel(QString("%1 h %2 min").arg(ore).arg(minuti));

    formLayout->addRow(createBoldLabel("Categoria:"), categoriaLabel);
    formLayout->addRow(createBoldLabel("Durata prevista:"), durataLabel);

    layout->addLayout(formLayout);
    setLayout(layout);
}

SocialeDettagliWidget::SocialeDettagliWidget(const QString& luogo,
                                             const QString& conChi,
                                             QWidget* parent)
    : DettagliWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    

    QFormLayout* formLayout = new QFormLayout();

    luogoLabel = new QLabel(luogo);
    conChiLabel = new QLabel(conChi);
    conChiLabel->setWordWrap(true);

    formLayout->addRow(createBoldLabel("Luogo:"), luogoLabel);
    formLayout->addRow(createBoldLabel("Con chi:"), conChiLabel);

    layout->addLayout(formLayout);
    setLayout(layout);
}

VisitaMedicaDettagliWidget::VisitaMedicaDettagliWidget(const QString& medico,
                                                       const QString& tipoVisita,
                                                       QWidget* parent)
    : DettagliWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);


    QFormLayout* formLayout = new QFormLayout();

    medicoLabel = new QLabel(medico);
    tipoVisitaLabel = new QLabel(tipoVisita);
    tipoVisitaLabel->setWordWrap(true);

    formLayout->addRow(createBoldLabel("Medico:"), medicoLabel);
    formLayout->addRow(createBoldLabel("Tipo visita:"), tipoVisitaLabel);

    layout->addLayout(formLayout);
    setLayout(layout);
}
