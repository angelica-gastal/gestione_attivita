#ifndef ATTIVITA_TABLE_H
#define ATTIVITA_TABLE_H

#include <QAbstractTableModel>
#include "gestioneattivita.h"
#include "gestioneattivita_observer.h"
#include "attivita.h"

// Adatta i dati di GestioneAttivita per QTableView
// Implementa sia QAbstractTableModel che GestioneAttivitaObserver 
class AttivitaTableModel : public QAbstractTableModel, public GestioneAttivitaObserver
{
    Q_OBJECT

private:
    GestioneAttivita* gestione;

public:
    AttivitaTableModel(GestioneAttivita* g, QObject* parent = nullptr);
    ~AttivitaTableModel();

    // Qt Model interface - implementati per visualizzare i dati nella tabella
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // GestioneAttivitaObserver - aggiorna la tabella quando i dati cambiano
    void onAttivitaAggiunta() override;
    void onAttivitaRimossa() override;
    void onAttivitaModificata() override;
    void onDatiCaricati() override;
};

#endif 
