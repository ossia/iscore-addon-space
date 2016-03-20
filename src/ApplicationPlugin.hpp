#pragma once
#include <iscore/plugins/application/GUIApplicationContextPlugin.hpp>
#include <src/SpaceContext.hpp>
#include <src/EditionSettings.hpp>
#include <QActionGroup>
namespace Space
{
class ApplicationPlugin : public QObject, public iscore::GUIApplicationContextPlugin
{
    public:
        ApplicationPlugin(const iscore::ApplicationContext& app);
        const EditionSettings& settings() const
        { return m_settings; }

    private:
        std::vector<iscore::OrderedToolbar> makeToolbars() override;

        QAction* m_move{};
        QAction* m_scale{};
        QAction* m_rotate{};
        QActionGroup* m_actions{};

        EditionSettings m_settings;

};
}