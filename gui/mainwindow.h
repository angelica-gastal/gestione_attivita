#include "attivitaform.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStackedWidget>
#include "modello/gestioneattivita_observer.h"
#include "modello/attivita_table.h"
#include "modello/gestioneattivita.h"

class AttivitaForm;
class FileManager;
class PannelloDettagli;
class MenuToolbarManager;
class AttivitaController;

class MainWindow : public QMainWindow, public GestioneAttivitaObserver
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Observer methods
    void onAttivitaAggiunta() override;
    void onAttivitaRimossa() override;
    void onAttivitaModificata() override;
    void onDatiCaricati() override;

private:
private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();
    void onSaveAsFile();
    void onExit();
private:
    void createMainPage();

private:
    GestioneAttivita* repo;
    QTableView* table;
    AttivitaTableModel* tableModel;
    AttivitaForm* form;
    QStackedWidget* stack;
    QWidget* mainPage;
    FileManager* fileManager;
    PannelloDettagli* pannelloDettagli;
    MenuToolbarManager* menuToolbarManager;
    AttivitaController* attivitaController;
};

#endif
