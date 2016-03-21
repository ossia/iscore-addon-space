#include "DistanceComputationFactory.hpp"
#include "DistanceComputation.hpp"

namespace Space
{
ComputationModel*DistanceComputationFactory::makeModel(
        const AreaModel& a1,
        const AreaModel& a2,
        const Context& ctx,
        const Id<ComputationModel>& comp,
        QObject* parent)
{
    return make_computation<DistanceComputation>(a1, a2, ctx, comp, parent);
}

ComputationModel*DistanceComputationFactory::load(
        const VisitorVariant& data,
        const Context& space,
        QObject* parent)
{
    ISCORE_TODO;
    return nullptr;
}

const UuidKey<ComputationFactory>&DistanceComputationFactory::concreteFactoryKey() const
{
    static const UuidKey<ComputationFactory> k{"2437bda3-6c38-46b5-bfac-9661bfcd5bec"};
    return k;
}

}
