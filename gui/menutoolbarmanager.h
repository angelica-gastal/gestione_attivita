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

    // Imposta lo stato delle azioni tema (true = scuro)
    void impostaTemaScuro(bool scuro);

signals:
    void newFileRequested();
    void openFileRequested();
    void saveFileRequested();
    void saveAsFileRequested();
    void exitRequested();
    void newAttivitaRequested();
    void editAttivitaRequested();
    void deleteAttivitaRequested();

    // Tema
    void temaChiaroRichiesto();
    void temaScuroRichiesto();

private:
    QMainWindow* m_mainWindow;
    QAction* m_azioneTemaChiaro = nullptr;
    QAction* m_azioneTemaScuro = nullptr;
};

#endif 
