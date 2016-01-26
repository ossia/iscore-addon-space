#include "GenericAreaModel.hpp"
#include "src/Area/AreaParser.hpp"


namespace Space
{
const AreaFactoryKey&GenericAreaModel::static_concreteFactoryKey()
{
    static const AreaFactoryKey name{"ac867755-9c5c-472b-848f-a9826b239648"};
    return name;

}

const AreaFactoryKey&GenericAreaModel::concreteFactoryKey() const
{
    return static_concreteFactoryKey();
}

QString GenericAreaModel::prettyName() const
{
    return tr("Generic");
}

QStringList GenericAreaModel::formula() const
{
    return m_formula;
}

GenericAreaModel::GenericAreaModel(
        const QStringList& formula,
        const Space::AreaContext& space,
        const Id<AreaModel>& id,
        QObject* parent):
    AreaModel{AreaParser{formula}.result(), space, id, parent},
    m_formula{formula}
{
}
}
