#ifndef GESTIONEATTIVITA_OBSERVER_H
#define GESTIONEATTIVITA_OBSERVER_H

class GestioneAttivitaObserver {
public:
    virtual ~GestioneAttivitaObserver() = default;

    /// Notificato quando viene aggiunta un'attività
    virtual void onAttivitaAggiunta() = 0;

    /// Notificato quando viene rimossa un'attività
    virtual void onAttivitaRimossa() = 0;

    /// Notificato quando vengono modificate le attività
    virtual void onAttivitaModificata() = 0;

    /// Notificato quando i dati vengono caricati
    virtual void onDatiCaricati() = 0;
};

#endif
