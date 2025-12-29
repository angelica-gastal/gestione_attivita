#include "mainwindow.h"
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
    table = new QTableView(this);
    table->setModel(tableModel);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->horizontalHeader()->setStretchLastSection(true);

    // Registriamo anche questa finestra per mostrare messaggi di stato
    repo->osservatore(this);

    setCentralWidget(table);

    createMenus();
    createToolbar();
    setWindowTitle("Gestione Attività");
    resize(900, 600);
    statusBar()->showMessage("Pronto");
}


MainWindow::~MainWindow() {
    repo->rimuoviOsservatore(this);
    delete repo;
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu("File");

    QAction *newAct = fileMenu->addAction("Nuovo");
    QAction *openAct = fileMenu->addAction("Apri");
    QAction *saveAct = fileMenu->addAction("Salva");
    QAction *saveAsAct = fileMenu->addAction("Salva come");
    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction("Esci");

    connect(newAct, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(openAct, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::onSaveAsFile);
    connect(exitAct, &QAction::triggered, this, &MainWindow::onExit);

    // --- MENU ATTIVITÀ ---
    QMenu *attivitaMenu = menuBar()->addMenu("Attività");

    QAction *newAtt = attivitaMenu->addAction("Nuova");
    QAction *editAtt = attivitaMenu->addAction("Modifica");
    QAction *deleteAtt = attivitaMenu->addAction("Elimina");

    connect(newAtt, &QAction::triggered, this, &MainWindow::onNewAttivita);
    connect(editAtt, &QAction::triggered, this, &MainWindow::onEditAttivita);
    connect(deleteAtt, &QAction::triggered, this, &MainWindow::onDeleteAttivita);
}

void MainWindow::createToolbar()
{
    QToolBar *tb = addToolBar("Main");

    QAction *newAct = new QAction("Nuovo file");
    QAction *openAct = new QAction("Apri");
    QAction *saveAct = new QAction("Salva");
    QAction *newAtt = new QAction("Nuova Attività");

    tb->addAction(newAct);
    tb->addAction(openAct);
    tb->addAction(saveAct);
    tb->addSeparator();
    tb->addAction(newAtt);

    connect(newAct, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(openAct, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(saveAct, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(newAtt, &QAction::triggered, this, &MainWindow::onNewAttivita);
}

void MainWindow::onAttivitaAggiunta() {
    statusBar()->showMessage("Attività aggiunta", 2000);
}

void MainWindow::onAttivitaRimossa() {
    statusBar()->showMessage("Attività rimossa", 2000);
}

void MainWindow::onAttivitaModificata() {
    statusBar()->showMessage("Attività modificata", 2000);
}

void MainWindow::onDatiCaricati() {
    statusBar()->showMessage("Dati caricati", 2000);
}

void MainWindow::onNewAttivita() {
    // Aggiunge una attività di prova
    repo->aggiungi(std::make_unique<Personale>(
        QString("Nuova"),
        QString("Creata"),
        QDate::currentDate(),
        QTime::currentTime(),
        Personale::Categoria::Hobby));
}

void MainWindow::onEditAttivita() {
    statusBar()->showMessage("Modifica attività (non implementato)", 2000);
}

void MainWindow::onDeleteAttivita() {
    QModelIndex idx = table->currentIndex();
    if (!idx.isValid()) {
        statusBar()->showMessage("Nessuna attività selezionata", 2000);
        return;
    }

    int row = idx.row();
    repo->rimuovi(row);
}


// ---- SLOT -----
void MainWindow::onNewFile()     { statusBar()->showMessage("Nuovo file", 2000); }
void MainWindow::onOpenFile()    { statusBar()->showMessage("Apri file", 2000); }
void MainWindow::onSaveFile()    { statusBar()->showMessage("Salva file", 2000); }
void MainWindow::onSaveAsFile()  { statusBar()->showMessage("Salva come", 2000); }
void MainWindow::onExit()        { qApp->quit(); }
