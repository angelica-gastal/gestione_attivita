#ifndef DETTAGLIOATTIVITAVISITOR_H
#define DETTAGLIOATTIVITAVISITOR_H

#include <QString>
#include "modello/attivitavisitor.h"

// Visitor che costruisce una descrizione testuale dei campi specifici.
class DettaglioAttivitaVisitor : public AttivitaVisitor {
public:
    QString specific; // output formattato dei campi specifici

    void visit(Personale* p) override;
    void visit(Sociale* s) override;
    void visit(Lavoro* l) override;
    void visit(VisitaMedica* v) override;
};

#endif // DETTAGLIOATTIVITAVISITOR_H
