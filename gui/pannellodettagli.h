#ifndef PANNELLODETTAGLI_H
#define PANNELLODETTAGLI_H

#include <QWidget>
#include <QLabel>

class Attivita;

class PannelloDettagli : public QWidget {
    Q_OBJECT
public:
    explicit PannelloDettagli(QWidget* parent = nullptr);

    void mostraDettagli(Attivita* att);
    void pulisci();

private:
    QLabel* titoloLabel;
    QLabel* descLabel;
    QLabel* dataOraLabel;
    QLabel* tipoLabel;
    QLabel* specificLabel;
};

#endif // PANNELLODETTAGLI_H
