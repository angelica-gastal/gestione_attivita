#include "dettaglioattivitavisitor.h"

#include "modello/personale.h"
#include "modello/sociale.h"
#include "modello/lavoro.h"
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

void DettaglioAttivitaVisitor::visit(Personale* p) {
    specific = QString("Categoria: %1\nDurata prevista: %2 h %3 min")
                   .arg(categoriaToString(p->categoria()))
                   .arg(p->orePreviste())
                   .arg(p->minutiPrevisti());
}

void DettaglioAttivitaVisitor::visit(Sociale* s) {
    specific = QString("Luogo: %1\nCon chi: %2")
                   .arg(s->luogo())
                   .arg(s->conChi());
}

void DettaglioAttivitaVisitor::visit(Lavoro* l) {
    specific = QString("Priorità: %1")
                   .arg(prioritaToString(l->priorita()));
}

void DettaglioAttivitaVisitor::visit(VisitaMedica* v) {
    specific = QString("Medico: %1\nTipo visita: %2")
                   .arg(v->medico())
                   .arg(v->tipoVisita());
}
