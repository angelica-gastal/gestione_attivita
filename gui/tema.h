#ifndef TEMA_H
#define TEMA_H

#include <QObject>

namespace TemaUtil {

enum class Tema { Chiaro, Scuro };

// Carica il tema dalle impostazioni (default: Chiaro)
Tema caricaTema();

// Salva il tema nelle impostazioni
void salvaTema(Tema tema);

// Applica stile e palette a livello applicativo
void applicaTema(Tema tema);

}

#endif // TEMA_H
