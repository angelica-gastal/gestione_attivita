#include "attivitacontroller.h"
#include "modello/gestioneattivita.h"
#include "modello/attivita.h"
#include "pannellodettagli.h"
#include "attivitaform.h"

#include <QTableView>
#include <QStackedWidget>
#include <QStatusBar>
#include <QMessageBox>

AttivitaController::AttivitaController(GestioneAttivita* repo,
                                       QTableView* table,
                                       QStackedWidget* stack,
                                       AttivitaForm* form,
                                       QWidget* mainPage,
                                       PannelloDettagli* pannello,
                                       QStatusBar* statusBar,
                                       QObject* parent)
    : QObject(parent)
    , m_repo(repo)
    , m_table(table)
    , m_stack(stack)
    , m_form(form)
    , m_mainPage(mainPage)
    , m_pannello(pannello)
    , m_statusBar(statusBar)
{}

void AttivitaController::onNewAttivita() {
    m_stack->setCurrentWidget(m_form);
    m_form->loadForCreate();
}

void AttivitaController::onEditAttivita() {
    QModelIndex idx = m_table->currentIndex();
    if (!idx.isValid()) {
        m_statusBar->showMessage("Nessuna attività selezionata", 2000);
        return;
    }

    int row = idx.row();
    Attivita* att = m_repo->attivita(row);
    m_stack->setCurrentWidget(m_form);
    m_form->loadForEdit(row, att);
}

void AttivitaController::onDeleteAttivita() {
    QModelIndex idx = m_table->currentIndex();
    if (!idx.isValid()) {
        m_statusBar->showMessage("Nessuna attività selezionata", 2000);
        return;
    }
    const int row = idx.row();
    auto ret = QMessageBox::question(nullptr, "Conferma eliminazione", "Eliminare l'attività selezionata?");
    if (ret != QMessageBox::Yes)
        return;

    m_repo->rimuovi(row);
}

void AttivitaController::onViewAttivita() {
    QModelIndex idx = m_table->currentIndex();
    if (!idx.isValid()) {
        m_statusBar->showMessage("Nessuna attività selezionata", 2000);
        return;
    }
    m_pannello->mostraDettagli(m_repo->attivita(idx.row()));
}
