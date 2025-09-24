#include "overlay.h"
#include <QPainter>

Overlay::Overlay(QWidget* parent)
    : QWidget(parent), dotPos(-10, -10) // start offscreen
{
}

void Overlay::setDotPosition(const QPointF& pos)
{
    dotPos = pos;
    update();  // schedule repaint
}

void Overlay::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::black);
    painter.setBrush(Qt::red);

    const int radius = 3;
    painter.drawEllipse(dotPos, radius, radius);
}
