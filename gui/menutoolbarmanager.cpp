#include "menutoolbarmanager.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMenu>

MenuToolbarManager::MenuToolbarManager(QMainWindow* mainWindow)
    : QObject(mainWindow), m_mainWindow(mainWindow) {}

void MenuToolbarManager::createMenus() {
    QMenu *fileMenu = m_mainWindow->menuBar()->addMenu("File");
    QAction *newAct = fileMenu->addAction("Nuovo");
    QAction *openAct = fileMenu->addAction("Apri");
    QAction *saveAct = fileMenu->addAction("Salva");
    QAction *saveAsAct = fileMenu->addAction("Salva come");
    fileMenu->addSeparator();
    QAction *exitAct = fileMenu->addAction("Esci");

    connect(newAct, &QAction::triggered, this, &MenuToolbarManager::newFileRequested);
    connect(openAct, &QAction::triggered, this, &MenuToolbarManager::openFileRequested);
    connect(saveAct, &QAction::triggered, this, &MenuToolbarManager::saveFileRequested);
    connect(saveAsAct, &QAction::triggered, this, &MenuToolbarManager::saveAsFileRequested);
    connect(exitAct, &QAction::triggered, this, &MenuToolbarManager::exitRequested);

    QMenu *attivitaMenu = m_mainWindow->menuBar()->addMenu("Attività");
    QAction *newAtt = attivitaMenu->addAction("Nuova");
    QAction *editAtt = attivitaMenu->addAction("Modifica");
    QAction *deleteAtt = attivitaMenu->addAction("Elimina");
    QAction *viewAtt = attivitaMenu->addAction("Dettagli");

    connect(newAtt, &QAction::triggered, this, &MenuToolbarManager::newAttivitaRequested);
    connect(editAtt, &QAction::triggered, this, &MenuToolbarManager::editAttivitaRequested);
    connect(deleteAtt, &QAction::triggered, this, &MenuToolbarManager::deleteAttivitaRequested);
    connect(viewAtt, &QAction::triggered, this, &MenuToolbarManager::viewAttivitaRequested);
}

void MenuToolbarManager::createToolbar() {
    QToolBar *tb = m_mainWindow->addToolBar("Main");
    QAction *newAct = new QAction("Nuovo file");
    QAction *openAct = new QAction("Apri");
    QAction *saveAct = new QAction("Salva");
    QAction *newAtt = new QAction("Nuova Attività");
    QAction *viewAtt = new QAction("Dettagli");

    tb->addAction(newAct);
    tb->addAction(openAct);
    tb->addAction(saveAct);
    tb->addSeparator();
    tb->addAction(newAtt);
    tb->addAction(viewAtt);

    connect(newAct, &QAction::triggered, this, &MenuToolbarManager::newFileRequested);
    connect(openAct, &QAction::triggered, this, &MenuToolbarManager::openFileRequested);
    connect(saveAct, &QAction::triggered, this, &MenuToolbarManager::saveFileRequested);
    connect(newAtt, &QAction::triggered, this, &MenuToolbarManager::newAttivitaRequested);
    connect(viewAtt, &QAction::triggered, this, &MenuToolbarManager::viewAttivitaRequested);
}
