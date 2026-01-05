#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QWidget>

class GestioneAttivita;

// Gestisce le operazioni sui file
// Coordina dialogo con l'utente e JsonRepo
class FileManager {
public:
    explicit FileManager(GestioneAttivita* repo, QWidget* parent);

    bool nuovoFile();
    void apriFile();
    void salvaFile();
    void salvaComefile();

    QString currentFilePath() const { return m_currentFilePath; }  // Percorso del file corrente
    bool isLoading() const { return m_isLoading; }                 // True durante il caricamento (evita salvataggi automatici)

private:
    GestioneAttivita* m_repo;
    QWidget* m_parent;
    QString m_currentFilePath;
    bool m_isLoading = false;
};

#endif
