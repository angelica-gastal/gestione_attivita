#ifndef TEMA_H
#define TEMA_H

#include <QObject>

namespace TemaUtil {

enum class Tema { Chiaro, Scuro };

// Carica il tema dalle impostazioni
Tema caricaTema();

// Salva il tema
void salvaTema(Tema tema);

// Applica stile e palette
void applicaTema(Tema tema);

}

#endif 
