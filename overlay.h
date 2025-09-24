#ifndef OVERLAY_H
#define OVERLAY_H

#include <QWidget>
#include <QPointF>

class Overlay : public QWidget
{
    Q_OBJECT
public:
    explicit Overlay(QWidget* parent = nullptr);

    void setDotPosition(const QPointF& pos);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    QPointF dotPos;
};

#endif
