#include "attivitaform.h"
#include "mainwindow.h"
#include "filemanager.h"
#include "pannellodettagli.h"
#include "menutoolbarmanager.h"
#include "attivitacontroller.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QStatusBar>
#include <QApplication>
#include <QMenu>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QAbstractItemView>
#include <QDate>
#include <QTime>
#include <memory>
#include <QStackedWidget>
#include <QMessageBox>
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>
#include <QShortcut>
#include <QModelIndex>

#include "modello/gestioneattivita.h"
#include "modello/attivita.h"
#include "modello/personale.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // ===== MODELLO LOGICO =====
    // Crea l'oggetto centrale che gestisce tutte le attività
    repo = new GestioneAttivita();

    // ===== TABELLA CON PROXY MODEL =====
    tableModel = new AttivitaTableModel(repo, this);
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tableModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1); // Cerca in tutte le colonne
    
    // Configura la vista tabella
    table = new QTableView(this);
    table->setModel(proxyModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setStretchLastSection(false);
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 250);
    table->setColumnWidth(2, 180);
    table->setColumnWidth(3, 115);

    // ===== OBSERVER E FILE MANAGER =====
    repo->osservatore(this);
    
    fileManager = new FileManager(repo, this);

    // ===== COSTRUZIONE INTERFACCIA =====
    createMainPage();

    // Stack widget per navigare tra pagina principale e form
    stack = new QStackedWidget(this);
    stack->addWidget(mainPage);

    // Form polimorfo
    form = new AttivitaForm(this);
    stack->addWidget(form);

    setCentralWidget(stack);

    // ===== MENU, TOOLBAR E CONTROLLER =====
    menuToolbarManager = new MenuToolbarManager(this);
    menuToolbarManager->createMenus();
    menuToolbarManager->createToolbar();

    // Controller che gestisce le operazioni CRUD sulle attività
    attivitaController = new AttivitaController(repo, table, stack, form, mainPage, 
                                                 pannelloDettagli, statusBar(), proxyModel, this);

    // ===== COLLEGAMENTO SEGNALI-SLOT =====
    connect(menuToolbarManager, &MenuToolbarManager::newFileRequested, this, &MainWindow::onNewFile);
    connect(menuToolbarManager, &MenuToolbarManager::openFileRequested, this, &MainWindow::onOpenFile);
    connect(menuToolbarManager, &MenuToolbarManager::saveFileRequested, this, &MainWindow::onSaveFile);
    connect(menuToolbarManager, &MenuToolbarManager::saveAsFileRequested, this, &MainWindow::onSaveAsFile);
    connect(menuToolbarManager, &MenuToolbarManager::exitRequested, this, &MainWindow::onExit);

    // Collegamenti menu/toolbar -> attività operations
    connect(menuToolbarManager, &MenuToolbarManager::newAttivitaRequested, attivitaController, &AttivitaController::onNewAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::editAttivitaRequested, attivitaController, &AttivitaController::onEditAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::deleteAttivitaRequested, attivitaController, &AttivitaController::onDeleteAttivita);

    // Collega i segnali del form al modello
    connect(form, &AttivitaForm::saved, this, [this](Attivita* obj, int index) {
        std::unique_ptr<Attivita> ptr(obj);
        if (index >= 0) {
            repo->aggiorna(index, std::move(ptr));
        } else {
            repo->aggiungi(std::move(ptr));
        }
        stack->setCurrentWidget(mainPage);
    });
    connect(form, &AttivitaForm::cancelled, this, [this]{
        stack->setCurrentWidget(mainPage);
    });

    // Collega le interazioni della tabella (doppio click e selezione)
    connect(table, &QTableView::doubleClicked, attivitaController, &AttivitaController::onViewAttivita);
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, [this](const QModelIndex& current){
        // Quando la selezione diventa vuota, pulisci i dettagli
        if (!current.isValid()) {
            pannelloDettagli->pulisci();
            return;
        }

        // Usa mapToSource per convertire indice visivo → indice modello reale
        int sourceRow = proxyModel->mapToSource(current).row();
        pannelloDettagli->mostraDettagli(sourceRow >= 0 ? repo->attivita(sourceRow) : nullptr);
    });

    setWindowTitle("Gestione Attività");
    resize(900,600);
    statusBar()->showMessage("Pronto");
}

MainWindow::~MainWindow() {
    repo->rimuoviOsservatore(this);
    delete repo;
}

// Costruisce il layout principale con barra ricerca, tabella e pannello dettagli
void MainWindow::createMainPage() {
    mainPage = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(mainPage);

    QHBoxLayout* searchLayout = new QHBoxLayout();
    QLabel* searchLabel = new QLabel("Cerca:", this);
    QLineEdit* searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Digita per cercare attività...");
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    mainLayout->addLayout(searchLayout);

    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

    QSplitter* splitter = new QSplitter(mainPage);
    splitter->setOrientation(Qt::Horizontal);

    splitter->addWidget(table);

    pannelloDettagli = new PannelloDettagli(splitter);
    splitter->addWidget(pannelloDettagli);

    splitter->setStretchFactor(0, 3);
    splitter->setStretchFactor(1, 2);

    mainLayout->addWidget(splitter);
    mainPage->setLayout(mainLayout);
}

void MainWindow::clearSelectionAndDetails() {
    if (table && table->selectionModel()) {
        table->selectionModel()->clearSelection();
        table->setCurrentIndex(QModelIndex());
    }

    if (pannelloDettagli) {
        pannelloDettagli->pulisci();
    }
}

// ===== SLOT OPERAZIONI FILE =====
void MainWindow::onNewFile() {
    if (fileManager->nuovoFile()) {
        clearSelectionAndDetails();
        statusBar()->showMessage("Nuovo file creato", 2000);
    }
}

void MainWindow::onOpenFile() {
    fileManager->apriFile();
    if (!fileManager->currentFilePath().isEmpty()) {
        clearSelectionAndDetails();
        statusBar()->showMessage("File caricato: " + fileManager->currentFilePath(), 3000);
    }
}

void MainWindow::onSaveFile() {
    fileManager->salvaFile();
    if (!fileManager->currentFilePath().isEmpty())
        statusBar()->showMessage("File salvato: " + fileManager->currentFilePath(), 3000);
}

void MainWindow::onSaveAsFile() {
    fileManager->salvaComefile();
    if (!fileManager->currentFilePath().isEmpty())
        statusBar()->showMessage("File salvato: " + fileManager->currentFilePath(), 3000);
}

void MainWindow::onExit() { qApp->quit(); }

// ===== METODI OBSERVER =====
// Implementano GestioneAttivitaObserver per reagire ai cambiamenti del modello, aggiornano la barra di stato e salvano automaticamente

void MainWindow::onAttivitaAggiunta() {
    statusBar()->showMessage("Attività aggiunta", 2000);
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }
}

void MainWindow::onAttivitaRimossa() {
    statusBar()->showMessage("Attività rimossa", 2000);
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }

    if (repo && repo->numeroAttivita() == 0) {
        clearSelectionAndDetails();
    }
}

void MainWindow::onAttivitaModificata() {
    statusBar()->showMessage("Attività modificata", 2000);
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }
}

void MainWindow::onDatiCaricati() {
    statusBar()->showMessage("Dati caricati", 2000);
    clearSelectionAndDetails();
}

// Applica il filtro di ricerca al proxy model mentre l'utente digita
void MainWindow::onSearchTextChanged(const QString& text) {
    if (proxyModel) {
        proxyModel->setFilterWildcard(text);
    }
}
