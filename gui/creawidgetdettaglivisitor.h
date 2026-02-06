#ifndef CREAWIDGETDETTAGLIVISITOR_H
#define CREAWIDGETDETTAGLIVISITOR_H

#include "modello/attivitavisitor.h"
#include <memory>

class DettagliWidget;

// Visitor che costruisce il widget giusto
class CreaWidgetDettagliVisitor : public AttivitaVisitor {
public:
    CreaWidgetDettagliVisitor() = default;
    
    void visit(Lavoro* l) override;
    void visit(Personale* p) override;
    void visit(Sociale* s) override;
    void visit(VisitaMedica* v) override;
    
    // Restituisce widget
    DettagliWidget* prendiWidget();

private:
    DettagliWidget* widget = nullptr;
};

#endif
