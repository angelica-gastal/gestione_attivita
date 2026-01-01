#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QString>
#include <QWidget>

class GestioneAttivita;

class FileManager {
public:
    explicit FileManager(GestioneAttivita* repo, QWidget* parent);

    void nuovoFile();
    void apriFile();
    void salvaFile();
    void salvaComefile();

    QString currentFilePath() const { return m_currentFilePath; }

private:
    GestioneAttivita* m_repo;
    QWidget* m_parent;
    QString m_currentFilePath;
};

#endif // FILEMANAGER_H
