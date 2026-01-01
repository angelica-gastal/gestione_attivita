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

    while (m_repo->numeroAttivita() > 0)
        m_repo->rimuovi(0);

    m_currentFilePath.clear();
}

void FileManager::apriFile() {
    QString path = QFileDialog::getOpenFileName(m_parent, "Apri file", "", 
        "File JSON (*.json);;Tutti i file (*)");
    if (path.isEmpty())
        return;

    JsonRepo jsonRepo(path);
    try {
        m_repo->carica(jsonRepo);
        m_currentFilePath = path;
    } catch (...) {
        QMessageBox::critical(m_parent, "Errore", "Impossibile caricare il file.");
    }
}

void FileManager::salvaFile() {
    if (m_currentFilePath.isEmpty()) {
        salvaComefile();
        return;
    }

    JsonRepo jsonRepo(m_currentFilePath);
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

    m_currentFilePath = path;
    salvaFile();
}
