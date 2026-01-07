#ifndef FILTROPROXYMODELCOMBINATO_H
#define FILTROPROXYMODELCOMBINATO_H

#include <QSortFilterProxyModel>
#include <QString>

// Proxy model combino filtro testuale e filtro per tipo
class FiltroProxyModelCombinato : public QSortFilterProxyModel {
    Q_OBJECT
public:
    explicit FiltroProxyModelCombinato(QObject* parent = nullptr)
        : QSortFilterProxyModel(parent) {}

    void setTextFilter(const QString& text) {
        m_text = text;
        invalidateFilter();
    }

    void setTypeFilter(const QString& type) {
        m_type = type;
        invalidateFilter();
    }

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const override {
        Q_UNUSED(source_parent);
        const QAbstractItemModel* src = sourceModel();
        if (!src) return true;

        // Filtro per tipo (su colonna 0)
        if (!m_type.isEmpty() && m_type != QString("Tutti")) {
            QModelIndex typeIdx = src->index(source_row, 0);
            QString tipo = src->data(typeIdx, Qt::DisplayRole).toString();
            if (tipo != m_type)
                return false;
        }

        // Filtro testuale su tutte le colonne
        if (m_text.isEmpty())
            return true;

        const int cols = src->columnCount();
        const QString needle = m_text;
        for (int c = 0; c < cols; ++c) {
            QModelIndex idx = src->index(source_row, c);
            QString val = src->data(idx, Qt::DisplayRole).toString();
            if (val.contains(needle, Qt::CaseInsensitive))
                return true;
        }
        return false;
    }

private:
    QString m_text;
    QString m_type; // "Tutti" o uno dei tipi concreti
};

#endif 
