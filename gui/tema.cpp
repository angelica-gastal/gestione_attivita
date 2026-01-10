#include "tema.h"

#include <QApplication>
#include <QPalette>
#include <QSettings>
#include <QStyleFactory>
#include <QStyle>

namespace TemaUtil {

static constexpr const char* kChiaveImpostazioni = "ui/tema";

Tema caricaTema() {
    QSettings s;
    const QString v = s.value(kChiaveImpostazioni, QStringLiteral("chiaro")).toString().toLower();
    return (v == QStringLiteral("scuro")) ? Tema::Scuro : Tema::Chiaro;
}

void salvaTema(Tema tema) {
    QSettings s;
    s.setValue(kChiaveImpostazioni, tema == Tema::Scuro ? QStringLiteral("scuro") : QStringLiteral("chiaro"));
}

static void applicaPaletteScura() {
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
    darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Highlight, QColor(142, 45, 197).lighter());
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);
    QApplication::setPalette(darkPalette);
}

void applicaTema(Tema tema) {
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    if (tema == Tema::Scuro) {
        applicaPaletteScura();
    } else {
        QApplication::setPalette(QApplication::style()->standardPalette());
    }
}

} // namespace TemaUtil
