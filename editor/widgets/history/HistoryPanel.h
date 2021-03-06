#pragma once

#include <QtWidgets/QListWidget>

#include "../dock/DockPanel.h"
#include "common/TrackedObject.h"

namespace AxiomModel {
    class Action;

    class HistoryList;
}

namespace AxiomGui {

    class HistoryPanel : public DockPanel, public AxiomCommon::TrackedObject {
        Q_OBJECT

    public:
        explicit HistoryPanel(AxiomModel::HistoryList *list, QWidget *parent = nullptr);

    private slots:

        void updateStack();

    private:
        AxiomModel::HistoryList *list;
        QListWidget *listWidget;

        void appendItem(size_t i, AxiomModel::Action *action, QString prepend);
    };
}
