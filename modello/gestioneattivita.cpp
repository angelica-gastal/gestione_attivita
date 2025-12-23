#include "gestioneattivita.h"
#include "attivita.h"

void GestioneAttivita::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (attivita)
        m_attivita.push_back(std::move(attivita));
}

void GestioneAttivita::rimuovi(int indice) {
    if (indice >= 0 && indice < static_cast<int>(m_attivita.size())) {
        m_attivita.erase(m_attivita.begin() + indice);
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
