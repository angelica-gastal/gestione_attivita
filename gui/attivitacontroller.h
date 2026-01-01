#ifndef ATTIVITACONTROLLER_H
#define ATTIVITACONTROLLER_H

#include <QObject>

class GestioneAttivita;
class QTableView;
class QStackedWidget;
class AttivitaForm;
class PannelloDettagli;
class QWidget;
class QStatusBar;

class AttivitaController : public QObject {
    Q_OBJECT
public:
    AttivitaController(GestioneAttivita* repo, 
                       QTableView* table,
                       QStackedWidget* stack,
                       AttivitaForm* form,
                       QWidget* mainPage,
                       PannelloDettagli* pannello,
                       QStatusBar* statusBar,
                       QObject* parent = nullptr);

public slots:
    void onNewAttivita();
    void onEditAttivita();
    void onDeleteAttivita();
    void onViewAttivita();

private:
    GestioneAttivita* m_repo;
    QTableView* m_table;
    QStackedWidget* m_stack;
    AttivitaForm* m_form;
    QWidget* m_mainPage;
    PannelloDettagli* m_pannello;
    QStatusBar* m_statusBar;
};

#endif // ATTIVITACONTROLLER_H
