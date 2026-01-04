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

#include "modello/gestioneattivita.h"
#include "modello/attivita.h"
#include "modello/personale.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Modello logico
    repo = new GestioneAttivita();

    // Tabella + model Qt
    tableModel = new AttivitaTableModel(repo, this);
    
    // Proxy model per la ricerca e ordinamento
    proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(tableModel);
    proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    proxyModel->setFilterKeyColumn(-1); // Cerca in tutte le colonne
    
    table = new QTableView(this);
    table->setModel(proxyModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setStretchLastSection(false);
    table->setColumnWidth(0, 100);
    table->setColumnWidth(1, 250);
    table->setColumnWidth(2, 180);
    table->setColumnWidth(3, 115);

    repo->osservatore(this);

    fileManager = new FileManager(repo, this);

    createMainPage();

    stack = new QStackedWidget(this);
    stack->addWidget(mainPage);

    // Form polimorfo
    form = new AttivitaForm(this);
    stack->addWidget(form);

    setCentralWidget(stack);

    // Controllers
    menuToolbarManager = new MenuToolbarManager(this);
    menuToolbarManager->createMenus();
    menuToolbarManager->createToolbar();

    attivitaController = new AttivitaController(repo, table, stack, form, mainPage, 
                                                 pannelloDettagli, statusBar(), proxyModel, this);

    // Collegamenti menu/toolbar -> file operations
    connect(menuToolbarManager, &MenuToolbarManager::newFileRequested, this, &MainWindow::onNewFile);
    connect(menuToolbarManager, &MenuToolbarManager::openFileRequested, this, &MainWindow::onOpenFile);
    connect(menuToolbarManager, &MenuToolbarManager::saveFileRequested, this, &MainWindow::onSaveFile);
    connect(menuToolbarManager, &MenuToolbarManager::saveAsFileRequested, this, &MainWindow::onSaveAsFile);
    connect(menuToolbarManager, &MenuToolbarManager::exitRequested, this, &MainWindow::onExit);

    // Collegamenti menu/toolbar -> attività operations
    connect(menuToolbarManager, &MenuToolbarManager::newAttivitaRequested, attivitaController, &AttivitaController::onNewAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::editAttivitaRequested, attivitaController, &AttivitaController::onEditAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::deleteAttivitaRequested, attivitaController, &AttivitaController::onDeleteAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::viewAttivitaRequested, attivitaController, &AttivitaController::onViewAttivita);

    // Form signals
    connect(form, &AttivitaForm::saved, this, [this](Attivita* obj, int index) {
        std::unique_ptr<Attivita> ptr(obj);
        if (index >= 0) {
            // Modifica di un'attività esistente
            repo->aggiorna(index, std::move(ptr));
        } else {
            // Creazione di una nuova attività
            repo->aggiungi(std::move(ptr));
        }
        stack->setCurrentWidget(mainPage);
    });
    connect(form, &AttivitaForm::cancelled, this, [this]{
        stack->setCurrentWidget(mainPage);
    });

    // Table interactions
    connect(table, &QTableView::doubleClicked, attivitaController, &AttivitaController::onViewAttivita);
    connect(table->selectionModel(), &QItemSelectionModel::currentChanged, this, [this](const QModelIndex& current){
        // Convertire l'indice del proxy model all'indice del modello sorgente
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

void MainWindow::createMainPage() {
    mainPage = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(mainPage);

    // Barra di ricerca
    QHBoxLayout* searchLayout = new QHBoxLayout();
    QLabel* searchLabel = new QLabel("Cerca:", this);
    QLineEdit* searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Digita per cercare attività...");
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    mainLayout->addLayout(searchLayout);

    // Connessione per la ricerca
    connect(searchEdit, &QLineEdit::textChanged, this, &MainWindow::onSearchTextChanged);

    // Splitter con tabella e dettagli
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

// ---- SLOT -----
void MainWindow::onNewFile() {
    fileManager->nuovoFile();
    statusBar()->showMessage("Nuovo file creato", 2000);
}

void MainWindow::onOpenFile() {
    fileManager->apriFile();
    if (!fileManager->currentFilePath().isEmpty())
        statusBar()->showMessage("File caricato: " + fileManager->currentFilePath(), 3000);
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

void MainWindow::onAttivitaAggiunta() {
    statusBar()->showMessage("Attività aggiunta", 2000);
    // Salvataggio automatico se il file è già stato aperto e non stiamo caricando
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }
}

void MainWindow::onAttivitaRimossa() {
    statusBar()->showMessage("Attività rimossa", 2000);
    // Salvataggio automatico se il file è già stato aperto e non stiamo caricando
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }
}

void MainWindow::onAttivitaModificata() {
    statusBar()->showMessage("Attività modificata", 2000);
    // Salvataggio automatico se il file è già stato aperto e non stiamo caricando
    if (!fileManager->currentFilePath().isEmpty() && !fileManager->isLoading()) {
        fileManager->salvaFile();
    }
}

void MainWindow::onDatiCaricati() {
    statusBar()->showMessage("Dati caricati", 2000);
}

void MainWindow::onSearchTextChanged(const QString& text) {
    if (proxyModel) {
        proxyModel->setFilterWildcard(text);
    }
}
