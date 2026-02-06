#include "compilaformvisitor.h"
#include "attivitaform.h"
#include "personaleuifactory.h"
#include "lavorouifactory.h"
#include "socialeuifactory.h"
#include "visitamedicauifactory.h"

CompilaFormVisitor::CompilaFormVisitor(AttivitaForm* f) : form(f) {}

void CompilaFormVisitor::visit(Personale* p) {
    form->titoloEdit->setText(p->titolo());
    form->descEdit->setText(p->descrizione());
    form->dataEdit->setDate(p->data());
    form->oraEdit->setTime(p->ora());
    form->tipoCombo->setCurrentText("Personale");
    form->clearSpecificUI();
    form->buildSpecificUI("Personale");
    if(form->personaleFactory) {
        if (form->personaleFactory->categoriaCombo)
            form->personaleFactory->categoriaCombo->setCurrentIndex(static_cast<int>(p->categoria()));
        if (form->personaleFactory->oreSpin)
            form->personaleFactory->oreSpin->setValue(p->orePreviste());
        if (form->personaleFactory->minutiSpin)
            form->personaleFactory->minutiSpin->setValue(p->minutiPrevisti());
    }
}

void CompilaFormVisitor::visit(Lavoro* l) {
    form->titoloEdit->setText(l->titolo());
    form->descEdit->setText(l->descrizione());
    form->dataEdit->setDate(l->data());
    form->oraEdit->setTime(l->ora());
    form->tipoCombo->setCurrentText("Lavoro");
    form->clearSpecificUI();
    form->buildSpecificUI("Lavoro");
    if(form->lavoroFactory && form->lavoroFactory->prioritaCombo)
        form->lavoroFactory->prioritaCombo->setCurrentIndex(static_cast<int>(l->priorita()));
}

void CompilaFormVisitor::visit(Sociale* s) {
    form->titoloEdit->setText(s->titolo());
    form->descEdit->setText(s->descrizione());
    form->dataEdit->setDate(s->data());
    form->oraEdit->setTime(s->ora());
    form->tipoCombo->setCurrentText("Sociale");
    form->clearSpecificUI();
    form->buildSpecificUI("Sociale");
    if(form->socialeFactory) {
        if (form->socialeFactory->luogoEdit)
            form->socialeFactory->luogoEdit->setText(s->luogo());
        if (form->socialeFactory->conChiEdit)
            form->socialeFactory->conChiEdit->setText(s->conChi());
    }
}

void CompilaFormVisitor::visit(VisitaMedica* v) {
    form->titoloEdit->setText(v->titolo());
    form->descEdit->setText(v->descrizione());
    form->dataEdit->setDate(v->data());
    form->oraEdit->setTime(v->ora());
    form->tipoCombo->setCurrentText("VisitaMedica");
    form->clearSpecificUI();
    form->buildSpecificUI("VisitaMedica");
    if(form->visitaMedicaFactory) {
        if(form->visitaMedicaFactory->medicoEdit)
            form->visitaMedicaFactory->medicoEdit->setText(v->medico());
        if(form->visitaMedicaFactory->tipoVisitaEdit)
            form->visitaMedicaFactory->tipoVisitaEdit->setText(v->tipoVisita());
    }
}
