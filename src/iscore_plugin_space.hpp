#pragma once
#include <QObject>
#include <iscore/plugins/qt_interfaces/PluginRequirements_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/FactoryFamily_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/FactoryInterface_QtInterface.hpp>
#include <iscore/plugins/qt_interfaces/GUIApplicationContextPlugin_QtInterface.hpp>

class iscore_plugin_space final :
        public QObject,
        public iscore::Plugin_QtInterface,
        public iscore::FactoryInterface_QtInterface,
        public iscore::FactoryList_QtInterface,
        public iscore::CommandFactory_QtInterface
{
        Q_OBJECT
        Q_PLUGIN_METADATA(IID FactoryInterface_QtInterface_iid)
        Q_INTERFACES(
                iscore::Plugin_QtInterface
                iscore::FactoryInterface_QtInterface
                iscore::FactoryList_QtInterface
                iscore::CommandFactory_QtInterface
                )

    public:
        iscore_plugin_space();
        virtual ~iscore_plugin_space();

    private:
        // Process & inspector
        std::vector<std::unique_ptr<iscore::FactoryInterfaceBase>> factories(
                const iscore::ApplicationContext& ctx,
                const iscore::AbstractFactoryKey& matchingName) const override;

        std::vector<std::unique_ptr<iscore::FactoryListInterface>> factoryFamilies() override;

        std::pair<const CommandParentFactoryKey, CommandGeneratorMap> make_commands() override;

        int32_t version() const override;
        UuidKey<iscore::Plugin> key() const override;
};
