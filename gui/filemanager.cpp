#include "filemanager.h"
#include "modello/gestioneattivita.h"
#include "modello/jsonrepo.h"

#include <QFileDialog>
#include <QMessageBox>

FileManager::FileManager(GestioneAttivita* repo, QWidget* parent)
    : m_repo(repo), m_parent(parent) {}

void FileManager::nuovoFile() {
    auto ret = QMessageBox::question(m_parent, "Nuovo file", 
        "Creare un nuovo file? I dati non salvati andranno persi.");
    if (ret != QMessageBox::Yes)
        return;

    // Cancella il path PRIMA di rimuovere le attività per evitare salvataggi automatici
    m_currentFilePath.clear();
    
    while (m_repo->numeroAttivita() > 0)
        m_repo->rimuovi(0);
}

void FileManager::apriFile() {
    QString path = QFileDialog::getOpenFileName(m_parent, "Apri file", "", 
        "File JSON (*.json);;Tutti i file (*)");
    if (path.isEmpty())
        return;

    JsonRepo jsonRepo(path);
    try {
        // Imposta prima il nuovo percorso per evitare salvataggi sul file sbagliato
        m_currentFilePath = path;
        m_isLoading = true;
        m_repo->carica(jsonRepo);
        m_isLoading = false;
    } catch (...) {
        m_isLoading = false;
        QMessageBox::critical(m_parent, "Errore", "Impossibile caricare il file.");
        m_currentFilePath.clear();
    }
}

void FileManager::salvaFile() {
    if (m_currentFilePath.isEmpty()) {
        salvaComefile();
        return;
    }

    // Assicurati che il file abbia estensione .json
    QString filePath = m_currentFilePath;
    if (!filePath.endsWith(".json", Qt::CaseInsensitive)) {
        filePath += ".json";
        m_currentFilePath = filePath;
    }

    JsonRepo jsonRepo(filePath);
    try {
        m_repo->salva(jsonRepo);
    } catch (...) {
        QMessageBox::critical(m_parent, "Errore", "Impossibile salvare il file.");
    }
}

void FileManager::salvaComefile() {
    QString path = QFileDialog::getSaveFileName(m_parent, "Salva come", "", 
        "File JSON (*.json);;Tutti i file (*)");
    if (path.isEmpty())
        return;

    // Assicurati che il file abbia estensione .json
    if (!path.endsWith(".json", Qt::CaseInsensitive)) {
        path += ".json";
    }

    m_currentFilePath = path;
    salvaFile();
}
