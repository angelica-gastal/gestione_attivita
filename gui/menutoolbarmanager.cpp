#include "menutoolbarmanager.h"
#include <QMainWindow>
#include <QMenuBar>
#include <QToolBar>
#include <QAction>
#include <QMenu>
#include <QKeySequence>
#include <QActionGroup>

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

    // shortcut da tastiera ai menu File
    newAct->setShortcut(QKeySequence::New);           // Ctrl+N
    openAct->setShortcut(QKeySequence::Open);         // Ctrl+O
    saveAct->setShortcut(QKeySequence::Save);         // Ctrl+S
    saveAsAct->setShortcut(QKeySequence::SaveAs);     // Ctrl+Shift+S
    exitAct->setShortcut(QKeySequence::Quit);         // Ctrl+Q

    newAct->setShortcutContext(Qt::ApplicationShortcut);
    openAct->setShortcutContext(Qt::ApplicationShortcut);
    saveAct->setShortcutContext(Qt::ApplicationShortcut);
    saveAsAct->setShortcutContext(Qt::ApplicationShortcut);
    exitAct->setShortcutContext(Qt::ApplicationShortcut);

    m_mainWindow->addAction(newAct);
    m_mainWindow->addAction(openAct);
    m_mainWindow->addAction(saveAct);
    m_mainWindow->addAction(saveAsAct);
    m_mainWindow->addAction(exitAct);

    connect(newAct, &QAction::triggered, this, &MenuToolbarManager::newFileRequested);
    connect(openAct, &QAction::triggered, this, &MenuToolbarManager::openFileRequested);
    connect(saveAct, &QAction::triggered, this, &MenuToolbarManager::saveFileRequested);
    connect(saveAsAct, &QAction::triggered, this, &MenuToolbarManager::saveAsFileRequested);
    connect(exitAct, &QAction::triggered, this, &MenuToolbarManager::exitRequested);

    QMenu *attivitaMenu = m_mainWindow->menuBar()->addMenu("Attività");
    QAction *newAtt = attivitaMenu->addAction("Nuova");
    QAction *editAtt = attivitaMenu->addAction("Modifica");
    QAction *deleteAtt = attivitaMenu->addAction("Elimina");

    //shortcut da tastiera al menu Attività
    newAtt->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_N);  // Ctrl+Shift+N
    editAtt->setShortcut(Qt::CTRL | Qt::Key_E);              // Ctrl+E

    newAtt->setShortcutContext(Qt::ApplicationShortcut);
    editAtt->setShortcutContext(Qt::ApplicationShortcut);

    m_mainWindow->addAction(newAtt);
    m_mainWindow->addAction(editAtt);

    connect(newAtt, &QAction::triggered, this, &MenuToolbarManager::newAttivitaRequested);
    connect(editAtt, &QAction::triggered, this, &MenuToolbarManager::editAttivitaRequested);
    connect(deleteAtt, &QAction::triggered, this, &MenuToolbarManager::deleteAttivitaRequested);

    // Menu Aspetto -> Tema
    QMenu *aspettoMenu = m_mainWindow->menuBar()->addMenu("Aspetto");
    QMenu *temaMenu = aspettoMenu->addMenu("Tema");

    QActionGroup* gruppoTema = new QActionGroup(this);
    gruppoTema->setExclusive(true);

    m_azioneTemaChiaro = new QAction("Chiaro", this);
    m_azioneTemaChiaro->setCheckable(true);
    m_azioneTemaScuro = new QAction("Scuro", this);
    m_azioneTemaScuro->setCheckable(true);

    gruppoTema->addAction(m_azioneTemaChiaro);
    gruppoTema->addAction(m_azioneTemaScuro);

    temaMenu->addAction(m_azioneTemaChiaro);
    temaMenu->addAction(m_azioneTemaScuro);

    connect(m_azioneTemaChiaro, &QAction::triggered, this, &MenuToolbarManager::temaChiaroRichiesto);
    connect(m_azioneTemaScuro, &QAction::triggered, this, &MenuToolbarManager::temaScuroRichiesto);
}

void MenuToolbarManager::createToolbar() {
    QToolBar *tb = m_mainWindow->addToolBar("Main");
    QAction *newAct = new QAction("Nuovo file");
    QAction *openAct = new QAction("Apri");
    QAction *saveAct = new QAction("Salva");
    QAction *newAtt = new QAction("Nuova Attività");

    tb->addAction(newAct);
    tb->addAction(openAct);
    tb->addAction(saveAct);
    tb->addSeparator();
    tb->addAction(newAtt);

    connect(newAct, &QAction::triggered, this, &MenuToolbarManager::newFileRequested);
    connect(openAct, &QAction::triggered, this, &MenuToolbarManager::openFileRequested);
    connect(saveAct, &QAction::triggered, this, &MenuToolbarManager::saveFileRequested);
    connect(newAtt, &QAction::triggered, this, &MenuToolbarManager::newAttivitaRequested);
}

void MenuToolbarManager::impostaTemaScuro(bool scuro) {
    if (m_azioneTemaChiaro && m_azioneTemaScuro) {
        m_azioneTemaScuro->setChecked(scuro);
        m_azioneTemaChiaro->setChecked(!scuro);
    }
}
