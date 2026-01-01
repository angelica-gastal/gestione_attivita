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
    if(form->personaleFactory && form->personaleFactory->luogoEdit)
        form->personaleFactory->luogoEdit->setText(p->luogo());
}

void CompilaFormVisitor::visit(Lavoro* l) {
    form->titoloEdit->setText(l->titolo());
    form->descEdit->setText(l->descrizione());
    form->dataEdit->setDate(l->data());
    form->oraEdit->setTime(l->ora());
    form->tipoCombo->setCurrentText("Lavoro");
    form->clearSpecificUI();
    form->buildSpecificUI("Lavoro");
    if(form->lavoroFactory && form->lavoroFactory->aziendaEdit)
        form->lavoroFactory->aziendaEdit->setText(l->azienda());
}

void CompilaFormVisitor::visit(Sociale* s) {
    form->titoloEdit->setText(s->titolo());
    form->descEdit->setText(s->descrizione());
    form->dataEdit->setDate(s->data());
    form->oraEdit->setTime(s->ora());
    form->tipoCombo->setCurrentText("Sociale");
    form->clearSpecificUI();
    form->buildSpecificUI("Sociale");
    if(form->socialeFactory && form->socialeFactory->eventoEdit)
        form->socialeFactory->eventoEdit->setText(s->evento());
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
