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
#include <stdexcept>

JsonRepo::JsonRepo(const QString& path)
    : m_path(path) {}

std::vector<std::unique_ptr<Attivita>> JsonRepo::carica() {
    QFile f(m_path);
    if (!f.open(QIODevice::ReadOnly))
        throw std::runtime_error("Impossibile aprire il file");

    QByteArray data = f.readAll();
    f.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    
    if (doc.isNull() || parseError.error != QJsonParseError::NoError)
        throw std::runtime_error("File JSON corrotto o non valido");

    if (!doc.isArray())
        throw std::runtime_error("Il file JSON non contiene un array");

    std::vector<std::unique_ptr<Attivita>> result;
    QJsonArray arr = doc.array();

    // Itera su ogni elemento JSON
    for (auto val : arr) {
        if (!val.isObject())
            continue;

        QJsonObject obj = val.toObject();
        QString tipo = obj["tipo"].toString();

        // Carica campi comuni a tutti i tipi
        QString titolo = obj["titolo"].toString();
        QString descrizione = obj["descrizione"].toString();
        QDate data = QDate::fromString(obj["data"].toString(), "yyyy-MM-dd");
        QTime ora = QTime::fromString(obj["ora"].toString(), "HH:mm");

        // Salta gli elementi con dati non validi
        if (!data.isValid() || !ora.isValid())
            continue;

        // Crea l'oggetto giusto in base al tipo, caricando i campi specifici
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
        else if (tipo == "VisitaMedica") {
            QString medico = obj["medico"].toString();
            QString tipoVisita = obj["tipoVisita"].toString();
            result.push_back( AttivitaFactory::creaVisitaMedica(titolo, descrizione, data, ora, medico, tipoVisita) );
        }
    }

    return result;
}

void JsonRepo::salva(const std::vector<std::unique_ptr<Attivita>>& data) {
    QJsonArray arr;

    // Itera su tutti gli oggetti per serializzarli in JSON
    for (const auto& a : data) {
        QJsonObject obj;
        obj["tipo"] = a->tipo();
        obj["titolo"] = a->titolo();
        obj["descrizione"] = a->descrizione();
        obj["data"] = a->data().toString("yyyy-MM-dd");
        obj["ora"] = a->ora().toString("HH:mm");

        // Salva i campi specifici in base al tipo tramite cast dinamico
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

    // Scrive l'array JSON nel file
    QJsonDocument doc(arr);
    QFile f(m_path);
    if (f.open(QIODevice::WriteOnly)) {
        f.write(doc.toJson());
        f.close();
    }
}
