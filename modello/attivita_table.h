#ifndef ATTIVITA_TABLE_H
#define ATTIVITA_TABLE_H

#include <QAbstractTableModel>
#include "gestioneattivita.h"
#include "gestioneattivita_observer.h"
#include "attivita.h"

class AttivitaTableModel : public QAbstractTableModel, public GestioneAttivitaObserver
{
    Q_OBJECT

private:
    GestioneAttivita* gestione;

public:
    AttivitaTableModel(GestioneAttivita* g, QObject* parent = nullptr);
    ~AttivitaTableModel();

    // Qt Model interface
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    // GestioneAttivitaObserver
    void onAttivitaAggiunta() override;
    void onAttivitaRimossa() override;
    void onAttivitaModificata() override;
    void onDatiCaricati() override;
};

#endif 
