#include "attivita_table.h"

AttivitaTableModel::AttivitaTableModel(GestioneAttivita* g, QObject* parent)
    : QAbstractTableModel(parent), gestione(g)
{
    if (gestione)
        gestione->osservatore(this);
}

AttivitaTableModel::~AttivitaTableModel() {
    if (gestione)
        gestione->rimuoviOsservatore(this);
}

int AttivitaTableModel::rowCount(const QModelIndex&) const {
    return gestione ? gestione->numeroAttivita() : 0;
}

int AttivitaTableModel::columnCount(const QModelIndex&) const {
    return 4; 
}

QVariant AttivitaTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    Attivita* a = gestione ? gestione->attivita(index.row()) : nullptr;
    if (!a) return {};

    switch (index.column()) {
        case 0: return a->tipo();
        case 1: return a->titolo();
        case 2: return a->data().toString("dd/MM/yyyy");
        case 3: return a->ora().toString("HH:mm");
    }
    return {};
}

QVariant AttivitaTableModel::headerData(int section, Qt::Orientation o, int role) const {
    if (o == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
            case 0: return "Tipo";
            case 1: return "Titolo";
            case 2: return "Data";
            case 3: return "Ora";
        }
    }
    return {};
}

void AttivitaTableModel::onAttivitaAggiunta() {
    beginResetModel();
    endResetModel();
}

void AttivitaTableModel::onAttivitaRimossa() {
    beginResetModel();
    endResetModel();
}

void AttivitaTableModel::onAttivitaModificata() {
    beginResetModel();
    endResetModel();
}

void AttivitaTableModel::onDatiCaricati() {
    beginResetModel();
    endResetModel();
}
