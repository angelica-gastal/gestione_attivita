
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
    void onTipoChanged(int idx);
    void onSaveClicked();
    void onCancelClicked();

private:
    void clearSpecificUI();
    void buildSpecificUI(QString tipo);

    // widget base comuni
    QLineEdit* titoloEdit;
    QTextEdit* descEdit;
    QDateEdit* dataEdit;
    QTimeEdit* oraEdit;
    QComboBox* tipoCombo;

    QWidget* specificContainer;   // layout dinamico
    QVBoxLayout* specificLayout;  // dentro specificContainer

    AttivitaUIFactory* activeFactory = nullptr;

    // Factory per i campi specifici
    std::unique_ptr<LavoroUIFactory> lavoroFactory;
    std::unique_ptr<PersonaleUIFactory> personaleFactory;
    std::unique_ptr<SocialeUIFactory> socialeFactory;
    std::unique_ptr<VisitaMedicaUIFactory> visitaMedicaFactory;

    int editingIndex = -1;
};

#endif // ATTIVITAFORM_H
