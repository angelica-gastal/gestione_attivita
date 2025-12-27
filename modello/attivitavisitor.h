#ifndef ATTIVITAVISITOR_H
#define ATTIVITAVISITOR_H

class Lavoro;
class Sociale;
class Personale;
class VisitaMedica;

class AttivitaVisitor {
public:
    virtual ~AttivitaVisitor() = default;

    virtual void visit(Lavoro*) = 0;
    virtual void visit(Sociale*) = 0;
    virtual void visit(Personale*) = 0;
    virtual void visit(VisitaMedica*) = 0;
};

#endif
