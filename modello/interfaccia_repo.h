#ifndef INTERFACCIA_REPO_H
#define INTERFACCIA_REPO_H

#include <vector>
#include <memory>

class Attivita;

class InterfacciaRepo {
public:
    virtual ~InterfacciaRepo() = default;

    /// Carica attività dal file restituisce vettore pronto a sostituire quello in memoria
    virtual std::vector<std::unique_ptr<Attivita>> carica() = 0;

    /// Salva attività nel file
    virtual void salva(const std::vector<std::unique_ptr<Attivita>>& data) = 0;
};

#endif 
