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
#include <QComboBox>
#include <QShortcut>
#include <QModelIndex>
#include <QTimer>

#include "modello/gestioneattivita.h"
#include "modello/attivita.h"
#include "modello/personale.h"
#include "tema.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // ===== MODELLO LOGICO =====
    // Crea l'oggetto centrale che gestisce tutte le attività
    repo = new GestioneAttivita();

    // ===== TABELLA CON PROXY MODEL =====
    tableModel = new AttivitaTableModel(repo, this);
    proxyModel = new FiltroProxyModelCombinato(this);
    proxyModel->setSourceModel(tableModel);
    
    // Configura la vista tabella
    table = new QTableView(this);
    table->setModel(proxyModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAutoFillBackground(true);
    table->setWordWrap(false);
    table->setTextElideMode(Qt::ElideRight);
    table->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    table->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    
    // Tutte le colonne in Stretch mode con proporzioni 130:260:140:115
    QHeaderView* header = table->horizontalHeader();
    header->setStretchLastSection(false);
    header->setSectionResizeMode(QHeaderView::Stretch);
    
    // Imposta larghezze iniziali che definiscono le proporzioni
    header->resizeSection(0, 130);
    header->resizeSection(1, 260);
    header->resizeSection(2, 140);
    header->resizeSection(3, 115);

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

    // Tema: connessioni menu
    connect(menuToolbarManager, &MenuToolbarManager::temaChiaroRichiesto, this, [this]{
        TemaUtil::applicaTema(TemaUtil::Tema::Chiaro);
        TemaUtil::salvaTema(TemaUtil::Tema::Chiaro);
        statusBar()->showMessage("Tema chiaro applicato", 1500);
    });
    connect(menuToolbarManager, &MenuToolbarManager::temaScuroRichiesto, this, [this]{
        TemaUtil::applicaTema(TemaUtil::Tema::Scuro);
        TemaUtil::salvaTema(TemaUtil::Tema::Scuro);
        statusBar()->showMessage("Tema scuro applicato", 1500);
    });

    // Collegamenti menu/toolbar -> attività operations
    connect(menuToolbarManager, &MenuToolbarManager::newAttivitaRequested, attivitaController, &AttivitaController::onNewAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::editAttivitaRequested, attivitaController, &AttivitaController::onEditAttivita);
    connect(menuToolbarManager, &MenuToolbarManager::deleteAttivitaRequested, attivitaController, &AttivitaController::onDeleteAttivita);

    // Pulsanti nel pannello dettagli -> operazioni attività
    connect(pannelloDettagli, &PannelloDettagli::editRequested, attivitaController, &AttivitaController::onEditAttivita);
    connect(pannelloDettagli, &PannelloDettagli::deleteRequested, attivitaController, &AttivitaController::onDeleteAttivita);

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

    // Imposta stato iniziale del menu tema in base alle impostazioni
    const auto tema = TemaUtil::caricaTema();
    menuToolbarManager->impostaTemaScuro(tema == TemaUtil::Tema::Scuro);
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
    QLabel* typeLabel = new QLabel("Tipo:", this);
    QComboBox* typeCombo = new QComboBox(this);
    typeCombo->addItem("Tutti");
    typeCombo->addItem("Sociale");
    typeCombo->addItem("Personale");
    typeCombo->addItem("Lavoro");
    typeCombo->addItem("Visita Medica");
    searchEdit->setPlaceholderText("Digita per cercare attività...");
    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    searchLayout->addSpacing(12);
    searchLayout->addWidget(typeLabel);
    searchLayout->addWidget(typeCombo);
    mainLayout->addLayout(searchLayout);

    connect(searchEdit, &QLineEdit::textChanged, this, [this](const QString& text){
        auto* proxy = static_cast<FiltroProxyModelCombinato*>(proxyModel);
        proxy->setTextFilter(text);
    });
    connect(typeCombo, &QComboBox::currentTextChanged, this, [this](const QString& type){
        auto* proxy = static_cast<FiltroProxyModelCombinato*>(proxyModel);
        proxy->setTypeFilter(type);
    });

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
