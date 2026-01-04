#ifndef GESTIONEATTIVITA_H
#define GESTIONEATTIVITA_H

#include <vector>
#include <memory>
#include <list>

class Attivita;
class InterfacciaRepo;
class GestioneAttivitaObserver;

class GestioneAttivita {
public:
    GestioneAttivita() = default;

    void aggiungi(std::unique_ptr<Attivita> attivita);

    void rimuovi(int indice);

    Attivita* attivita(int indice) const;

    int numeroAttivita() const;

    void aggiorna(int indice, std::unique_ptr<Attivita> attivita);

    void carica(InterfacciaRepo& repo);
    void salva(InterfacciaRepo& repo) const;

    // Observer pattern methods
    void osservatore(GestioneAttivitaObserver* observer);
    void rimuoviOsservatore(GestioneAttivitaObserver* observer);

private:
    void notificaOsservatori(void (GestioneAttivitaObserver::*)());

private:
    std::vector<std::unique_ptr<Attivita>> m_attivita;
    std::list<GestioneAttivitaObserver*> m_osservatori;
};

#endif