#ifndef BEAM_H
#define BEAM_H

#include <QVector>
#include <QWidget>
#include <QPointF>
#include <utility>
#include <QtMath>
#include <QString>
#include <QDebug>
#include <QVector>
#include <QTimer>
#include <QVector2D>

#include <QPainter>
#include <QPaintEvent>

class Beam : public QWidget
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    explicit Beam(QWidget *parent = nullptr);
    ~Beam();

    QPointF getPos();
    void setPos(double x, double y);
    double getAngle();
    void setAngle(double angle);

    void updateBeam(double distance);
    bool collides(QPointF coords);

private:
    QLineF line;
    QPointF pos;
    double angle;
};

#endif
