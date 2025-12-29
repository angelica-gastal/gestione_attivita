#include "gestioneattivita.h"
#include "attivita.h"
#include "interfaccia_repo.h"
#include "gestioneattivita_observer.h"

void GestioneAttivita::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (attivita) {
        m_attivita.push_back(std::move(attivita));
        notificaOsservatori(&GestioneAttivitaObserver::onAttivitaAggiunta);
    }
}

void GestioneAttivita::rimuovi(int indice) {
    if (indice >= 0 && indice < static_cast<int>(m_attivita.size())) {
        m_attivita.erase(m_attivita.begin() + indice);
        notificaOsservatori(&GestioneAttivitaObserver::onAttivitaRimossa);
    }
}

Attivita* GestioneAttivita::attivita(int indice) const {
    if (indice >= 0 && indice < static_cast<int>(m_attivita.size()))
        return m_attivita[indice].get();
    return nullptr;
}

int GestioneAttivita::numeroAttivita() const {
    return static_cast<int>(m_attivita.size());
}

void GestioneAttivita::carica(InterfacciaRepo& repo) {
    m_attivita = repo.carica();
    notificaOsservatori(&GestioneAttivitaObserver::onDatiCaricati);
}

void GestioneAttivita::salva(InterfacciaRepo& repo) const {
    repo.salva(m_attivita);
}

void GestioneAttivita::segnalaModifica() {
    notificaOsservatori(&GestioneAttivitaObserver::onAttivitaModificata);
}

void GestioneAttivita::osservatore(GestioneAttivitaObserver* observer) {
    if (observer)
        m_osservatori.push_back(observer);
}

void GestioneAttivita::rimuoviOsservatore(GestioneAttivitaObserver* observer) {
    m_osservatori.remove(observer);
}

void GestioneAttivita::notificaOsservatori(void (GestioneAttivitaObserver::*metodo)()) {
    for (auto observer : m_osservatori) {
        (observer->*metodo)();
    }
}
