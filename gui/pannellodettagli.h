#ifndef PANNELLODETTAGLI_H
#define PANNELLODETTAGLI_H

#include <QWidget>
#include <QLabel>

class Attivita;
class QPushButton;

// Pannello laterale che mostra i dettagli dell'attività selezionata
// Usa DettaglioAttivitaVisitor
class PannelloDettagli : public QWidget {
    Q_OBJECT
public:
    explicit PannelloDettagli(QWidget* parent = nullptr);

    void mostraDettagli(Attivita* att);
    void pulisci();

signals:
    void editRequested();
    void deleteRequested();

private:
    QLabel* titoloLabel;
    QLabel* descLabel;
    QLabel* dataOraLabel;
    QLabel* tipoLabel;
    QLabel* specificLabel;
    QPushButton* editButton;
    QPushButton* deleteButton;
};

#endif
