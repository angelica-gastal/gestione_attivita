#ifndef PANNELLODETTAGLI_H
#define PANNELLODETTAGLI_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Attivita;
class QPushButton;
class DettagliWidget;

// Pannello laterale che mostra i dettagli dell'attività selezionata
// Usa CreaWidgetDettagliVisitor per creare widget specifici
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
    QVBoxLayout* mainLayout;
    DettagliWidget* currentWidget;
    QPushButton* editButton;
    QPushButton* deleteButton;
};

#endif
