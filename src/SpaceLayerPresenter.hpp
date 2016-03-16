#pragma once
#include <Process/LayerPresenter.hpp>
#include <Process/Focus/FocusDispatcher.hpp>
#include <iscore/tools/IdentifiedObjectMap.hpp>

#include "nano_observer.hpp"
#include "Area/AreaModel.hpp"
#include "Area/AreaPresenter.hpp"
class QMainWindow;
class QGraphicsItemGroup;
namespace Process {
class LayerModel;
class LayerView;
}

struct EmptySpaceItem : public QGraphicsItem
{
        QRectF m_rect;
    public:
        using QGraphicsItem::QGraphicsItem;
        void setRect(const QRectF& rect)
        {

        }

        QRectF boundingRect() const override
        { return m_rect; }

        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override
        { }
};
namespace Space
{
class LayerView;
class LayerPresenter :
        public Process::LayerPresenter,
        public Nano::Observer
{
    public:
        LayerPresenter(const Process::LayerModel& model,
                            Process::LayerView* view,
                            QObject* parent);
        ~LayerPresenter();

        void setWidth(qreal width) override;
        void setHeight(qreal height) override;

        void on_focusChanged() override;

        void putToFront() override;
        void putBehind() override;

        void on_zoomRatioChanged(ZoomRatio) override;
        void parentGeometryChanged() override;

        const Process::LayerModel &layerModel() const override;
        const Id<Process::ProcessModel> &modelId() const override;

        void update();

    private:
        void reset();
        void on_areaAdded(const AreaModel&);
        void on_areaRemoved(const AreaModel& a);

        const Process::LayerModel& m_model;
        LayerView* m_view;

        const iscore::DocumentContext& m_ctx;
        QMainWindow* m_spaceWindowView{};
        IdContainer<AreaPresenter, AreaModel> m_areas;
        FocusDispatcher m_focusDispatcher;

        EmptySpaceItem* m_spaceItem{};

    public:
        void fillContextMenu(QMenu*, const QPoint& pos, const QPointF& scenepos) const override;
};
}
