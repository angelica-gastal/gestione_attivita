#ifndef COMPILAFORMVISITOR_H
#define COMPILAFORMVISITOR_H

#include "modello/attivitavisitor.h"
#include "modello/attivita.h"
#include <QWidget>

class AttivitaForm;

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
