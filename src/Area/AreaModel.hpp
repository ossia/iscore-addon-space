#pragma once
#include <iscore/tools/IdentifiedObject.hpp>
#include <Space/area.hpp>
#include <Device/Address/AddressSettings.hpp>
#include <src/Area/AreaFactory.hpp>
#include <src/SpaceContext.hpp>
#include <Process/ModelMetadata.hpp>
#include <iscore/component/Component.hpp>
#include <src/Area/ValMap.hpp>
class SpaceModel;
class QGraphicsItem;


namespace Space
{
// in the end, isn't an area the same thing as a domain???
// Maps addresses / values to the parameter of an area
class AreaPresenter;
class AreaModel : public IdentifiedObject<AreaModel>
{
        Q_OBJECT
    public:
        ModelMetadata metadata;
        iscore::Components components;

        // The value is used as default value if the address is invalid.
        virtual const UuidKey<AreaFactory>& concreteFactoryKey() const = 0;
        virtual QString prettyName() const = 0;
        virtual int type() const = 0;

        AreaModel(
                const QStringList& formula,
                const Space::AreaContext& space,
                const Id<AreaModel>&,
                QObject* parent);

        const SpaceModel& space() const
        { return m_context.space; }

        void setSpaceMapping(const SpaceMap& mapping);
        const SpaceMap& spaceMapping() const
        { return m_spaceMap; }

        void setParameterMapping(const ParameterMap& mapping);
        const ParameterMap& parameterMapping() const
        { return m_parameterMap; }

        void setCurrentMapping(const ValMap& map);
        void updateCurrentMapping(std::string sym, double value);
        const ValMap& currentMapping() const
        { return m_currentParameterMap;}

        QString toString() const;
        const QTransform& transform() const
        { return m_transform; }
        const QStringList& formula() const
        { return m_formula; }

    signals:
        void currentSymbolChanged(std::string, double);
        void areaChanged(ValMap);

    private:
        QTransform m_transform;
        const Space::AreaContext& m_context;
        QStringList m_formula;

        // Maps a variable from m_area to a variable from m_space.
        SpaceMap m_spaceMap;

        ParameterMap m_parameterMap; // General values of the model.
        ValMap m_currentParameterMap; // Current values used for display / execution.
};
}

Q_DECLARE_METATYPE(std::string)
Q_DECLARE_METATYPE(GiNaC::exmap)
Q_DECLARE_METATYPE(GiNaC::symbol)
Q_DECLARE_METATYPE(Id<Space::AreaModel>)
