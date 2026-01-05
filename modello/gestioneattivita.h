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

    // Aggiorna un'attività esistente all'indice specificato
    void aggiorna(int indice, std::unique_ptr<Attivita> attivita);

    // Carica le attività dal repository sostituendo i dati attuali
    void carica(InterfacciaRepo& repo);
    // Salva le attività attuali nel repository
    void salva(InterfacciaRepo& repo) const;

    // Registra un osservatore per ricevere notifiche di cambiamenti 
    void osservatore(GestioneAttivitaObserver* observer);
    // Rimuove un osservatore dalle notifiche
    void rimuoviOsservatore(GestioneAttivitaObserver* observer);

private:
    // Notifica tutti gli osservatori registrati con il metodo specificato
    void notificaOsservatori(void (GestioneAttivitaObserver::*)());
    // Ordina le attività per data e ora per garantire l'ordine cronologico
    void ordinaCronologicamente();

private:
    std::vector<std::unique_ptr<Attivita>> m_attivita;
    std::list<GestioneAttivitaObserver*> m_osservatori;
};

#endif