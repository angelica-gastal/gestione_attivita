#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QWidget>

class GestioneAttivita;

// Gestisce le operazioni sui file, tra utente e json repo
class FileManager {
public:
    explicit FileManager(GestioneAttivita* repo, QWidget* parent);

    bool nuovoFile();
    void apriFile();
    void salvaFile();
    void salvaComefile();

    QString currentFilePath() const { return m_currentFilePath; }  // Percorso del file corrente
    void setCurrentFilePath(const QString& path) { m_currentFilePath = path; }  // Imposta il percorso del file
    bool isLoading() const { return m_isLoading; }                 // True durante il caricamento (evita salvataggi automatici)
    void setIsLoading(bool loading) { m_isLoading = loading; }     // Imposta lo stato di caricamento

private:
    GestioneAttivita* m_repo;
    QWidget* m_parent;
    QString m_currentFilePath;
    bool m_isLoading = false;
};

#endif
