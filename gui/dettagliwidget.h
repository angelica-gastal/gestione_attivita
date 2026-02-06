#ifndef DETTAGLIWIDGET_H
#define DETTAGLIWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QFormLayout>

// Widget base per i dettagli di un'attività
class DettagliWidget : public QWidget {
    Q_OBJECT
public:
    explicit DettagliWidget(QWidget* parent = nullptr);
    virtual ~DettagliWidget() = default;
};

// Widget per visualizzare i dettagli di un'attività di tipo Lavoro
class LavoroDettagliWidget : public DettagliWidget {
    Q_OBJECT
public:
    explicit LavoroDettagliWidget(const QString& priorita, QWidget* parent = nullptr);
private:
    QLabel* prioritaLabel;
};

// Widget per visualizzare i dettagli di un'attività di tipo Personale
class PersonaleDettagliWidget : public DettagliWidget {
    Q_OBJECT
public:
    explicit PersonaleDettagliWidget(const QString& categoria, 
                                      int ore, 
                                      int minuti, 
                                      QWidget* parent = nullptr);
private:
    QLabel* categoriaLabel;
    QLabel* durataLabel;
};

// Widget per visualizzare i dettagli di un'attività di tipo Sociale
class SocialeDettagliWidget : public DettagliWidget {
    Q_OBJECT
public:
    explicit SocialeDettagliWidget(const QString& luogo, 
                                    const QString& conChi, 
                                    QWidget* parent = nullptr);
private:
    QLabel* luogoLabel;
    QLabel* conChiLabel;
};

// Widget per visualizzare i dettagli di un'attività di tipo VisitaMedica
class VisitaMedicaDettagliWidget : public DettagliWidget {
    Q_OBJECT
public:
    explicit VisitaMedicaDettagliWidget(const QString& medico, 
                                         const QString& tipoVisita, 
                                         QWidget* parent = nullptr);
private:
    QLabel* medicoLabel;
    QLabel* tipoVisitaLabel;
};

#endif
