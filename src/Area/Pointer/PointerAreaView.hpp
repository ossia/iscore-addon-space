#pragma once
#include <src/Area/AreaView.hpp>
#include <QPainterPath>

namespace Space
{
class PointerAreaView : public AreaView
{
    public:
        PointerAreaView(QGraphicsItem* parent);


        QRectF boundingRect() const override;

        void paint(QPainter* painter,
                   const QStyleOptionGraphicsItem* ,
                   QWidget*) override;

        void update(double x0, double y0);

    private:
        QPainterPath m_path;
};
}
