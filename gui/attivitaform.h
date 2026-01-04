
#ifndef ATTIVITAFORM_H
#define ATTIVITAFORM_H

#include <memory>

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QDateEdit>
#include <QTimeEdit>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include "modello/attivita.h"
#include "compilaformvisitor.h"
#include "lavorouifactory.h"
#include "personaleuifactory.h"
#include "socialeuifactory.h"
#include "visitamedicauifactory.h"

// Form polimorfo per creare/modificare attività
// Cambia dinamicamente i campi specifici in base al tipo di attività selezionato
// Utilizza factory per costruire l'interfaccia specifica e visitor per caricare i dati
class AttivitaForm : public QWidget {
    Q_OBJECT
    friend class CompilaFormVisitor;
public:
    AttivitaForm(QWidget* parent = nullptr);

    void loadForCreate();
    void loadForEdit(int index, Attivita* existing);  // usa Visitor

signals:
    void saved(Attivita* obj, int index);
    void cancelled();

private slots:
    void onTipoChanged(int idx);   // Ricostruisce i campi specifici quando cambia il tipo
    void onSaveClicked();          
    void onCancelClicked();        

private:
    void clearSpecificUI();              // Rimuove i widget specifici dal form
    void buildSpecificUI(QString tipo);  // Costruisce i widget specifici tramite factory

    
    QLineEdit* titoloEdit;
    QTextEdit* descEdit;
    QDateEdit* dataEdit;
    QTimeEdit* oraEdit;
    QComboBox* tipoCombo;
    QWidget* specificContainer;   
    QVBoxLayout* specificLayout;  
    AttivitaUIFactory* activeFactory = nullptr;
    std::unique_ptr<LavoroUIFactory> lavoroFactory;
    std::unique_ptr<PersonaleUIFactory> personaleFactory;
    std::unique_ptr<SocialeUIFactory> socialeFactory;
    std::unique_ptr<VisitaMedicaUIFactory> visitaMedicaFactory;

    int editingIndex = -1;
};

#endif
