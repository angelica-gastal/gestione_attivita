#include "attivitaform.h"
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
#include <QStackedWidget>

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
    table->horizontalHeader()->setStretchLastSection(false);
    table->setColumnWidth(0, 150);
    table->setColumnWidth(1, 450);
    table->setColumnWidth(2, 180);
    table->setColumnWidth(3, 113);

    repo->osservatore(this);

    stack = new QStackedWidget(this);
    stack->addWidget(table);

    // Form polimorfo
    form = new AttivitaForm(this);
    stack->addWidget(form);

    setCentralWidget(stack);

    connect(form, &AttivitaForm::saved, this, [this](Attivita* obj, int /*index*/) {
        std::unique_ptr<Attivita> ptr(obj);
        repo->aggiungi(std::move(ptr));
        stack->setCurrentWidget(table);
    });
    connect(form, &AttivitaForm::cancelled, this, [this]{
        stack->setCurrentWidget(table);
    });

    createMenus();
    createToolbar();
    setWindowTitle("Gestione Attività");
    resize(900,600);
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

void MainWindow::onNewAttivita() {
    stack->setCurrentWidget(form);
    form->loadForCreate();
}

void MainWindow::onEditAttivita() {
    QModelIndex idx = table->currentIndex();
    if (!idx.isValid()) {
        statusBar()->showMessage("Nessuna attività selezionata", 2000);
        return;
    }

    int row = idx.row();
    Attivita* att = repo->attivita(row);
    stack->setCurrentWidget(form);
    form->loadForEdit(row, att);
}

void MainWindow::onDeleteAttivita() {
    QModelIndex idx = table->currentIndex();
    if (!idx.isValid()) {
        statusBar()->showMessage("Nessuna attività selezionata", 2000);
        return;
    }
    repo->rimuovi(idx.row());
}

// ---- SLOT -----
void MainWindow::onNewFile()     { statusBar()->showMessage("Nuovo file", 2000); }
void MainWindow::onOpenFile()    { statusBar()->showMessage("Apri file", 2000); }
void MainWindow::onSaveFile()    { statusBar()->showMessage("Salva file", 2000); }
void MainWindow::onSaveAsFile()  { statusBar()->showMessage("Salva come", 2000); }
void MainWindow::onExit()        { qApp->quit(); }
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
