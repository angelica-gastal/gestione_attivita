#include "mainwindow.h"
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QDebug>
#include <QStatusBar>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    createMenus();
    createToolbar();
    setWindowTitle("Gestione Attività");
    resize(900, 600);
    statusBar()->showMessage("Pronto");
}

MainWindow::~MainWindow() {}

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

    QAction *newAct = new QAction("Nuovo");
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

// ---- SLOT -----
void MainWindow::onNewFile()     { statusBar()->showMessage("Nuovo file", 2000); }
void MainWindow::onOpenFile()    { statusBar()->showMessage("Apri file", 2000); }
void MainWindow::onSaveFile()    { statusBar()->showMessage("Salva file", 2000); }
void MainWindow::onSaveAsFile()  { statusBar()->showMessage("Salva come", 2000); }
void MainWindow::onExit()        { qApp->quit(); }

void MainWindow::onNewAttivita()   { statusBar()->showMessage("Nuova attività", 2000); }
void MainWindow::onEditAttivita()  { statusBar()->showMessage("Modifica attività", 2000); }
void MainWindow::onDeleteAttivita(){ statusBar()->showMessage("Elimina attività", 2000); }
