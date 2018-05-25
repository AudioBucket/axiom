#pragma once

#include <map>

#include "../dock/DockWidget.h"

class QTabBar;

namespace AxiomModel {
    class Library;
}

namespace AxiomGui {

    class MainWindow;

    class ModuleBrowserPanel : public ads::CDockWidget {
    Q_OBJECT

    public:
        explicit ModuleBrowserPanel(MainWindow *window, AxiomModel::Library *library, QWidget *parent = nullptr);

    private slots:

        void addTag(const QString &tag);

        void removeTag(const QString &tag);

        void changeTag(int tag);

    private:

        AxiomModel::Library *library;
        QTabBar *filterTabs;
        std::map<QString, int> tabIndexes;
        std::map<int, QString> indexTabs;
    };

}
