#pragma once
#include <iscore/tools/SettableIdentifier.hpp>
#include <iscore/plugins/customfactory/FactoryInterface.hpp>
#include <src/SpaceContext.hpp>
#include <QObject>
class QGraphicsItem;
class SpaceModel;

namespace Space
{
class AreaModel;
class AreaPresenter;

class AreaFactory : public iscore::AbstractFactory<AreaFactory>
{
        ISCORE_ABSTRACT_FACTORY_DECL(
                AreaFactory,
                "4620006c-4562-42f4-a3eb-4cd525330d50")
    public:
        virtual ~AreaFactory();

        // Pretty name, id
        virtual int type() const = 0;

        virtual QString prettyName() const = 0;

        // Model
        virtual AreaModel* makeModel(
                const QStringList& generic_formula,
                const Space::AreaContext& space,
                const Id<AreaModel>&,
                QObject* parent) const = 0;

        // Presenter
        virtual AreaPresenter* makePresenter(
                QGraphicsItem* view,
                const AreaModel& model,
                QObject* parent) const = 0;

        // View
        virtual QGraphicsItem* makeView(QGraphicsItem* parent) const = 0;

        // Formula
        virtual QStringList generic_formula() const = 0;

        // Widget ?
};
}

Q_DECLARE_METATYPE(UuidKey<Space::AreaFactory>)
