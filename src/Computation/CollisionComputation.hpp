#pragma once
#include <src/Computation/ComputationModel.hpp>
#include <src/Area/Circle/CircleAreaModel.hpp>
#include <src/Area/Pointer/PointerAreaModel.hpp>
#include <src/Area/Rectangle/Area.hpp>
#include <src/Area/Generic/GenericAreaModel.hpp>
#include <src/Computation/ComputationFactory.hpp>
#include <atomic>
namespace Space
{
class CollisionComputation;
}

COMPUTATION_METADATA(, Space::CollisionComputation, "3b48d241-c11b-479e-b188-82cef922a0d9", "CollisionComputation", "Collision")
namespace Space
{
class MatrixCollisionComputer;
class CollisionComputation :
        public ComputationModel
{
    public:
        void setup(
                const CircleAreaModel& a1,
                const CircleAreaModel& a2);
        void setup(
                const CircleAreaModel& a1,
                const PointerAreaModel& a2);
        void setup(
                const CircleAreaModel& a1,
                const RectangleAreaModel& a2);
        void setup(
                const PointerAreaModel& a1,
                const PointerAreaModel& a2);
        void setup(
                const RectangleAreaModel& a1,
                const PointerAreaModel& a2);
        void setup(
                const RectangleAreaModel& a1,
                const RectangleAreaModel& a2);
        void setup(
                const AreaModel& a1,
                const AreaModel& a2);

        template<typename Area1, typename Area2>
        CollisionComputation(
                const Area1& a1,
                const Area2& a2,
                const SpaceModel& space,
                const Id<ComputationModel>& id,
                QObject* parent):
            ComputationModel{a1.id(), a2.id(), space, id, parent}
        {
            setup(a1, a2);
        }

        template<typename Deser>
        CollisionComputation(
                Deser& d,
                const Context& space,
                QObject* parent):
            ComputationModel{d, space.space, parent}
        {
            loadAreas(space.process);
        }

        CollisionComputation(
                const CollisionComputation& source,
                const Context& space,
                const Id<ComputationModel>& newId,
                QObject* parent):
            ComputationModel{source, space.space, newId, parent}
        {
            loadAreas(space.process);
        }

        CollisionComputation* clone(
                        const Context& space,
                        const Id<ComputationModel>& newId,
                        QObject* parent) const override
        {
            return new CollisionComputation{*this, space, newId, parent};
        }

        State::Value result() const override;
        UuidKey<ComputationFactory> concreteKey() const override;

    private:
        void loadAreas(const Space::ProcessModel&);
        MatrixCollisionComputer* m_cptr{};
        std::function<bool()> m_fun;

        std::atomic_bool m_currentResult{false};
};

COMPUTATION_FACTORY(CollisionComputationFactory, "3b48d241-c11b-479e-b188-82cef922a0d9", CollisionComputation)

}
