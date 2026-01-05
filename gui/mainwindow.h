#include "attivitaform.h"
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QStackedWidget>
#include <QSortFilterProxyModel>
#include "modello/gestioneattivita_observer.h"
#include "modello/attivita_table.h"
#include "modello/gestioneattivita.h"

class AttivitaForm;
class FileManager;
class PannelloDettagli;
class MenuToolbarManager;
class AttivitaController;

// Finestra principale dell'applicazione
// Gestisce layout, menu, toolbar e coordina i vari componenti (tabella, form, dettagli)
// Implementa Observer per reagire ai cambiamenti nel modello
class MainWindow : public QMainWindow, public GestioneAttivitaObserver
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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
    void onSearchTextChanged(const QString& text);
private:
    void createMainPage();
    void clearSelectionAndDetails();

private:
    GestioneAttivita* repo;
    QTableView* table;
    AttivitaTableModel* tableModel;
    QSortFilterProxyModel* proxyModel;
    AttivitaForm* form;
    QStackedWidget* stack;
    QWidget* mainPage;
    FileManager* fileManager;
    PannelloDettagli* pannelloDettagli;
    MenuToolbarManager* menuToolbarManager;
    AttivitaController* attivitaController;
};

#endif
