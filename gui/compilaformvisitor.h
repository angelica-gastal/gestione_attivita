#ifndef COMPILAFORMVISITOR_H
#define COMPILAFORMVISITOR_H

#include "modello/attivitavisitor.h"
#include "modello/attivita.h"
#include <QWidget>

class AttivitaForm;

// Visitor che popola il form con i dati di un'attività esistente
// Usato in modalità modifica per caricare i valori nei widget appropriati
class CompilaFormVisitor : public AttivitaVisitor {
public:
    CompilaFormVisitor(AttivitaForm* form);
    void visit(Personale* p) override;
    void visit(Sociale* s) override;
    void visit(Lavoro* l) override;
    void visit(VisitaMedica* v) override;
private:
    AttivitaForm* form;
};

#endif
