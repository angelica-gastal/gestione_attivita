#ifndef JSONREPO_H
#define JSONREPO_H

#include "interfaccia_repo.h"
#include <QString>

// Implementazione del Repository pattern per JSON
class JsonRepo : public InterfacciaRepo {
public:
    explicit JsonRepo(const QString& path);

    std::vector<std::unique_ptr<Attivita>> carica() override;
    void salva(const std::vector<std::unique_ptr<Attivita>>& data) override;

private:
    QString m_path;
};

#endif 
