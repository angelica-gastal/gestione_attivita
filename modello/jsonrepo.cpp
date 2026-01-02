#include "jsonrepo.h"
#include "attivitafactory.h"
#include "attivita.h"
#include "lavoro.h"
#include "personale.h"
#include "sociale.h"
#include "visitamedica.h"

#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDate>
#include <QTime>

JsonRepo::JsonRepo(const QString& path)
    : m_path(path) {}

std::vector<std::unique_ptr<Attivita>> JsonRepo::carica() {
    QFile f(m_path);
    if (!f.open(QIODevice::ReadOnly))
        return {};

    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();

    if (!doc.isArray())
        return {};

    std::vector<std::unique_ptr<Attivita>> result;
    QJsonArray arr = doc.array();

    for (auto val : arr) {
        if (!val.isObject())
            continue;

        QJsonObject obj = val.toObject();
        QString tipo = obj["tipo"].toString();

        QString titolo = obj["titolo"].toString();
        QString descrizione = obj["descrizione"].toString();
        QDate data = QDate::fromString(obj["data"].toString(), "yyyy-MM-dd");
        QTime ora = QTime::fromString(obj["ora"].toString(), "HH:mm");

        if (!data.isValid() || !ora.isValid())
            continue;

        if (tipo == "Lavoro") {
            auto p = static_cast<Lavoro::Priorita>(obj["priorita"].toInt());
            result.push_back( AttivitaFactory::creaLavoro(titolo, descrizione, data, ora, p) );
        }
        else if (tipo == "Personale") {
            auto cat = static_cast<Personale::Categoria>(obj["categoria"].toInt());
            int ore = obj["ore"].toInt();
            int min = obj["minuti"].toInt();
            result.push_back( AttivitaFactory::creaPersonale(titolo, descrizione, data, ora, cat, ore, min) );
        }
        else if (tipo == "Sociale") {
            QString luogo = obj["luogo"].toString();
            QString conChi = obj["conChi"].toString();
            result.push_back( AttivitaFactory::creaSociale(titolo, descrizione, data, ora, luogo, conChi) );
        }
        else if (tipo == "Visita Medica") {
            QString medico = obj["medico"].toString();
            QString tipoVisita = obj["tipoVisita"].toString();
            result.push_back( AttivitaFactory::creaVisitaMedica(titolo, descrizione, data, ora, medico, tipoVisita) );
        }
    }

    return result;
}

void JsonRepo::salva(const std::vector<std::unique_ptr<Attivita>>& data) {
    QJsonArray arr;

    for (const auto& a : data) {
        QJsonObject obj;
        obj["tipo"] = a->tipo();
        obj["titolo"] = a->titolo();
        obj["descrizione"] = a->descrizione();
        obj["data"] = a->data().toString("yyyy-MM-dd");
        obj["ora"] = a->ora().toString("HH:mm");

        // Cast in base al tipo concreto
        if (auto l = dynamic_cast<Lavoro*>(a.get())) {
            obj["priorita"] = static_cast<int>(l->priorita());
        }
        else if (auto p = dynamic_cast<Personale*>(a.get())) {
            obj["categoria"] = static_cast<int>(p->categoria());
            obj["ore"] = p->orePreviste();
            obj["minuti"] = p->minutiPrevisti();
        }
        else if (auto s = dynamic_cast<Sociale*>(a.get())) {
            obj["luogo"] = s->luogo();
            obj["conChi"] = s->conChi();
        }
        else if (auto v = dynamic_cast<VisitaMedica*>(a.get())) {
            obj["medico"] = v->medico();
            obj["tipoVisita"] = v->tipoVisita();
        }

        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile f(m_path);
    if (f.open(QIODevice::WriteOnly)) {
        f.write(doc.toJson());
        f.close();
    }
}
