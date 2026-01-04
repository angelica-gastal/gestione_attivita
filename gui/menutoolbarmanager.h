#ifndef MENUTOOLBARMANAGER_H
#define MENUTOOLBARMANAGER_H

#include <QObject>

class QMainWindow;
class QAction;

// Gestisce la creazione di menu e toolbar della finestra principale
class MenuToolbarManager : public QObject {
    Q_OBJECT
public:
    explicit MenuToolbarManager(QMainWindow* mainWindow);

    void createMenus();
    void createToolbar();

signals:
    void newFileRequested();
    void openFileRequested();
    void saveFileRequested();
    void saveAsFileRequested();
    void exitRequested();
    void newAttivitaRequested();
    void editAttivitaRequested();
    void deleteAttivitaRequested();
    void viewAttivitaRequested();

private:
    QMainWindow* m_mainWindow;
};

#endif 
