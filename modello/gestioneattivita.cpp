#include "gestioneattivita.h"
#include "attivita.h"
#include "interfaccia_repo.h"
#include "gestioneattivita_observer.h"
#include <algorithm>

void GestioneAttivita::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (attivita) {
        m_attivita.push_back(std::move(attivita));
        ordinaCronologicamente();
        notificaOsservatori(&GestioneAttivitaObserver::onAttivitaAggiunta);
    }
}

void GestioneAttivita::rimuovi(int indice) {
    if (indice >= 0 && indice < static_cast<int>(m_attivita.size())) {
        m_attivita.erase(m_attivita.begin() + indice);
        notificaOsservatori(&GestioneAttivitaObserver::onAttivitaRimossa);
    }
}

void GestioneAttivita::aggiorna(int indice, std::unique_ptr<Attivita> attivita) {
    if (indice >= 0 && indice < static_cast<int>(m_attivita.size()) && attivita) {
        m_attivita[indice] = std::move(attivita);
        ordinaCronologicamente();
        notificaOsservatori(&GestioneAttivitaObserver::onAttivitaModificata);
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
    ordinaCronologicamente();
    notificaOsservatori(&GestioneAttivitaObserver::onDatiCaricati);
}

void GestioneAttivita::salva(InterfacciaRepo& repo) const {
    repo.salva(m_attivita);
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

void GestioneAttivita::ordinaCronologicamente() {
    std::sort(m_attivita.begin(), m_attivita.end(), [](const std::unique_ptr<Attivita>& a, const std::unique_ptr<Attivita>& b) {
        if (!a || !b)
            return false;

        if (a->data() == b->data())
            return a->ora() < b->ora();

        return a->data() < b->data();
    });
}
