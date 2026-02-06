#ifndef INTERFACCIA_REPO_H
#define INTERFACCIA_REPO_H

#include <vector>
#include <memory>

class Attivita;

// Repository pattern: astrae la persistenza dei dati 
class InterfacciaRepo {
public:
    virtual ~InterfacciaRepo() = default;

    // Carica attività dalla sorgente dati
    virtual std::vector<std::unique_ptr<Attivita>> carica() = 0;

    // Salva attività nella sorgente dati
    virtual void salva(const std::vector<std::unique_ptr<Attivita>>& data) = 0;
};

#endif 
