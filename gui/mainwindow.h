#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onNewFile();
    void onOpenFile();
    void onSaveFile();
    void onSaveAsFile();
    void onExit();

    void onNewAttivita();
    void onEditAttivita();
    void onDeleteAttivita();

private:
    void createMenus();
    void createToolbar();
};

#endif
