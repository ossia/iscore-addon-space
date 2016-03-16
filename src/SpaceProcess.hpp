#pragma once
#include <Process/Process.hpp>
#include <iscore/tools/IdentifiedObjectMap.hpp>
#include "Area/AreaModel.hpp"
#include "Computation/ComputationModel.hpp"
#include <iscore/tools/NotifyingMap.hpp>

#include <OSSIA/LocalTree/Scenario/ProcessComponent.hpp>
#include <OSSIA/LocalTree/Scenario/MetadataParameters.hpp>
#include <iscore_plugin_space_export.h>
namespace Space
{
class SpaceModel;
class LayerModel;
class ProcessModel;
namespace Executor { class ProcessExecutor; }

struct ProcessMetadata
{
        static const UuidKey<Process::ProcessFactory>& concreteFactoryKey()
        {
            static const UuidKey<Process::ProcessFactory>name{"ac4d616e-797d-4fdf-aaf0-0cb131aecc3d"};
            return name;
        }

        static QString objectName()
        {
            return "Space";
        }

        static QString factoryPrettyName()
        {
            return QObject::tr("Space");
        }
};


class ProcessModel : public Process::ProcessModel
{
        Q_OBJECT
    public:
        ProcessModel(
                const iscore::DocumentContext& doc,
                const TimeValue &duration,
                const Id<Process::ProcessModel> &id,
                QObject *parent);

        ProcessModel(
                const ProcessModel& other,
                const iscore::DocumentContext& doc,
                const TimeValue &duration,
                const Id<Process::ProcessModel> &id,
                QObject *parent);

        const SpaceModel& space() const
        { return *m_space; }
        const Space::AreaContext& context() const
        { return m_context; }

        NotifyingMap<AreaModel> areas;
        NotifyingMap<ComputationModel> computations;


    private:
        ProcessModel *clone(const Id<Process::ProcessModel> &newId, QObject *newParent) const override;

        UuidKey<Process::ProcessFactory>concreteFactoryKey() const override;
        QString prettyName() const override;

        void setDurationAndScale(const TimeValue &newDuration) override;
        void setDurationAndGrow(const TimeValue &newDuration) override;
        void setDurationAndShrink(const TimeValue &newDuration) override;

        void reset() override;

        ProcessStateDataInterface *startStateData() const override;
        ProcessStateDataInterface* endStateData() const override;

        Selection selectableChildren() const override;
        Selection selectedChildren() const override;
        void setSelection(const Selection &s) const override;

        void serialize_impl(const VisitorVariant &vis) const override;

        Process::LayerModel *makeLayer_impl(
                const Id<Process::LayerModel> &viewModelId,
                const QByteArray &constructionData,
                QObject *parent) override;
        Process::LayerModel *loadLayer_impl(
                const VisitorVariant &,
                QObject *parent) override;
        Process::LayerModel *cloneLayer_impl(
                const Id<Process::LayerModel> &newId,
                const Process::LayerModel &source,
                QObject *parent) override;

        void startExecution() override;
        void stopExecution() override;

        SpaceModel* m_space{};
        Space::AreaContext m_context;
};
}
