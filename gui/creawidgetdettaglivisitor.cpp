#include "creawidgetdettaglivisitor.h"
#include "dettagliwidget.h"
#include "modello/lavoro.h"
#include "modello/personale.h"
#include "modello/sociale.h"
#include "modello/visitamedica.h"

namespace {
QString categoriaToString(Personale::Categoria c) {
    switch (c) {
    case Personale::Categoria::Casa: return "Casa";
    case Personale::Categoria::Hobby: return "Hobby";
    case Personale::Categoria::Sport: return "Sport";
    case Personale::Categoria::Commissioni: return "Commissioni";
    }
    return "";
}

QString prioritaToString(Lavoro::Priorita p) {
    switch (p) {
    case Lavoro::Priorita::Alta: return "Alta";
    case Lavoro::Priorita::Media: return "Media";
    case Lavoro::Priorita::Bassa: return "Bassa";
    }
    return "";
}
}

void CreaWidgetDettagliVisitor::visit(Lavoro* l) {
    widget = new LavoroDettagliWidget(prioritaToString(l->priorita()));
}

void CreaWidgetDettagliVisitor::visit(Personale* p) {
    widget = new PersonaleDettagliWidget(
        categoriaToString(p->categoria()),
        p->orePreviste(),
        p->minutiPrevisti()
    );
}

void CreaWidgetDettagliVisitor::visit(Sociale* s) {
    widget = new SocialeDettagliWidget(
        s->luogo(),
        s->conChi()
    );
}

void CreaWidgetDettagliVisitor::visit(VisitaMedica* v) {
    widget = new VisitaMedicaDettagliWidget(
        v->medico(),
        v->tipoVisita()
    );
}

DettagliWidget* CreaWidgetDettagliVisitor::prendiWidget() {
    DettagliWidget* result = widget;
    widget = nullptr;
    return result;
}
