#ifndef GESTIONEATTIVITA_H
#define GESTIONEATTIVITA_H

#include <vector>
#include <memory>

class Attivita;
class InterfacciaRepo;

class GestioneAttivita {
public:
    GestioneAttivita() = default;

    void aggiungi(std::unique_ptr<Attivita> attivita);

    void rimuovi(int indice);

    Attivita* attivita(int indice) const;

    int numeroAttivita() const;

    void carica(InterfacciaRepo& repo);
    void salva(InterfacciaRepo& repo) const;

private:
    std::vector<std::unique_ptr<Attivita>> m_attivita;
};

#endif