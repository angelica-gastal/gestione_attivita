#include "attivitacontroller.h"
#include "modello/gestioneattivita.h"
#include "modello/attivita.h"
#include "pannellodettagli.h"
#include "attivitaform.h"

#include <QTableView>
#include <QStackedWidget>
#include <QStatusBar>
#include <QMessageBox>
#include <QSortFilterProxyModel>

AttivitaController::AttivitaController(GestioneAttivita* repo,
                                       QTableView* table,
                                       QStackedWidget* stack,
                                       AttivitaForm* form,
                                       QWidget* mainPage,
                                       PannelloDettagli* pannello,
                                       QStatusBar* statusBar,
                                       QSortFilterProxyModel* proxyModel,
                                       QObject* parent)
    : QObject(parent)
    , m_repo(repo)
    , m_table(table)
    , m_stack(stack)
    , m_form(form)
    , m_mainPage(mainPage)
    , m_pannello(pannello)
    , m_statusBar(statusBar)
    , m_proxyModel(proxyModel)
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

    // Convertire l'indice del proxy model all'indice del modello sorgente
    int sourceRow = m_proxyModel->mapToSource(idx).row();
    if (sourceRow < 0) {
        m_statusBar->showMessage("Errore nella selezione", 2000);
        return;
    }

    Attivita* att = m_repo->attivita(sourceRow);
    m_stack->setCurrentWidget(m_form);
    m_form->loadForEdit(sourceRow, att);
}

void AttivitaController::onDeleteAttivita() {
    QModelIndex idx = m_table->currentIndex();
    if (!idx.isValid()) {
        m_statusBar->showMessage("Nessuna attività selezionata", 2000);
        return;
    }
    
    // Convertire l'indice del proxy model all'indice del modello sorgente
    int sourceRow = m_proxyModel->mapToSource(idx).row();
    if (sourceRow < 0) {
        m_statusBar->showMessage("Errore nella selezione", 2000);
        return;
    }
    
    auto ret = QMessageBox::question(nullptr, "Conferma eliminazione", "Eliminare l'attività selezionata?");
    if (ret != QMessageBox::Yes)
        return;

    m_repo->rimuovi(sourceRow);
}

void AttivitaController::onViewAttivita() {
    QModelIndex idx = m_table->currentIndex();
    if (!idx.isValid()) {
        m_statusBar->showMessage("Nessuna attività selezionata", 2000);
        return;
    }
    
    // Convertire l'indice del proxy model all'indice del modello sorgente
    int sourceRow = m_proxyModel->mapToSource(idx).row();
    if (sourceRow >= 0) {
        m_pannello->mostraDettagli(m_repo->attivita(sourceRow));
    }
}
