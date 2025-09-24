#include "beam.h"

Beam::Beam(QWidget *parent)
    : QWidget(parent)
{
}

Beam::~Beam(){

}

void Beam::updateBeam(double distance){
    line = QLineF(pos, QPointF());
    line.setAngle(-angle);
    line.setLength(distance);
    this->repaint();
}

void Beam::paintEvent(QPaintEvent *event){

    QPainter painter(this);
    if(this->property("type").toString() == "obst"){
        painter.setPen(QPen(Qt::red, 2));
    }
    else if(this->property("type").toString() == "obst_inv"){
        painter.setPen(QPen(Qt::NoPen));
    }
    else if(this->property("type").toString() == "fin"){
        painter.setPen(QPen(Qt::green, 2));
    }
    painter.drawLine(line);

}

bool Beam::collides(QPointF point){
    qreal lineLength = line.length();
    if (lineLength == 0) {
        return point == line.p1();
    }

    // Calculate the perpendicular distance from the point to the line
    qreal numerator = std::abs((line.p2().y() - line.p1().y()) * point.x() - 
                               (line.p2().x() - line.p1().x()) * point.y() + 
                               line.p2().x() * line.p1().y() - 
                               line.p2().y() * line.p1().x());
    qreal denominator = lineLength;

    qreal distance = numerator / denominator;
    bool range = QLineF(pos, point).length() <= line.length() + 2;
    int sd = 0;
    bool side = ((point - pos).x() > sd) == ((line.p2() - pos).x() > sd)
        && ((point - pos).y() > sd) == ((line.p2() - pos).y() > sd);
    if(!side){
        if(QLineF(pos, point).length() < 1) side = true;
    }

    return (distance <= 1) && range && side;
}

QPointF Beam::getPos(){
    return pos;
}

void Beam::setPos(double x, double y){
    pos = QPointF(x, y);
}

double Beam::getAngle(){
    return angle;
}

void Beam::setAngle(double angle){
    this->angle = angle;
}
