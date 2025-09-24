#include "map.h"

void Map::setMapSize(int width, int height, bool border){

    this->setFixedSize(width + 2 * PA, height + 2 * PA);
    QWidget* bor = new QWidget(this);
    bor->setGeometry(0, 0, width + 2 * PA, height + 2 * PA);
    bor->setStyleSheet("background-color: grey; border: 2px solid white;");
    overlay = new Overlay(this);
    overlay->setGeometry(0, 0, width + 2 * PA, height + 2 * PA);

    if(border){
        makeWall(-10, -10, width + 20, 10);
        makeWall(-10, -10, 10, height + 20);
        makeWall(width, -10, 10, height + 20);
        makeWall(-10, height, width + 20, 10);
    }

}

QWidget * Map::makeWall(int x, int y, int w, int h, bool coll){
    QWidget* wall = new QWidget(this);
    wall->setGeometry(x + PA, y + PA, w, h);
    wall->setProperty("type", QString("wall"));
    wall->setStyleSheet("background-color: blue;");
    wall->show();
    collision_list.push_back(wall);
    return wall;
}

QWidget * Map::makeObst(int x, int y, int w, int h, bool coll){
    QWidget* obst = new QWidget(this);
    obst->setGeometry(x + PA, y + PA, w, h);
    obst->setProperty("type", QString("obst"));
    obst->setStyleSheet("background-color: red;");
    collision_list.push_back(obst);
    return obst;
}

QWidget * Map::makeFin(int x, int y, int w, int h, bool coll){
    QWidget* fin = new QWidget(this);
    fin->setGeometry(x + PA, y + PA, w, h);
    fin->setProperty("type", QString("fin"));
    fin->setStyleSheet("background-color: green;");
    collision_list.push_back(fin);
    return fin;
}

QWidget * Map::makeInvisibleObst(int x, int y, int w, int h, bool coll){
    QWidget* iobst = new QWidget(this);
    iobst->setGeometry(x + PA, y + PA, w, h);
    iobst->setProperty("type", QString("obst_inv"));
    iobst->setStyleSheet("background-color: red;");
    iobst->hide();
    collision_list.push_back(iobst);
    return iobst;
}

QWidget * Map::makePortal(int x1, int y1, int x2, int y2, int w, int h, QColor color){
    QWidget* port1 = new QWidget(this);
    QWidget* port2 = new QWidget(this);
    port1->setGeometry(x1 + PA, y1 + PA, w, h);
    port2->setGeometry(x2 + PA, y2 + PA, w, h);

    port1->setProperty("link", QVariant::fromValue(static_cast<void*>(port2)));
    port1->setProperty("tx", x1 - x2);
    port1->setProperty("ty", y1 - y2);
    port1->setProperty("color", color);
    port1->setStyleSheet(QString("background-color: %1").arg(color.name()));

    port2->setProperty("link", QVariant::fromValue(static_cast<void*>(port1)));
    port2->setProperty("tx", x2 - x1);
    port2->setProperty("ty", y2 - y1);
    port2->setProperty("color", color);
    port2->setStyleSheet(QString("background-color: %1").arg(color.name()));
    portal_list.push_back(port1);
    portal_list.push_back(port2);

    QGraphicsOpacityEffect* effect1 = new QGraphicsOpacityEffect(port1);
    effect1->setOpacity(0.5); 
    port1->setGraphicsEffect(effect1);
    QGraphicsOpacityEffect* effect2 = new QGraphicsOpacityEffect(port2);
    effect2->setOpacity(0.5); 
    port2->setGraphicsEffect(effect2);

    return port1;
}

QWidget * Map::makeMovingObst(int x, int y, int w, int h, int mx, int my, int cycle, double it, bool complete, bool coll){
    QWidget * obst = makeObst(x + PA, y + PA, w, h, coll);
    obst->setProperty("x_start", x + PA);
    obst->setProperty("y_start", y + PA);
    obst->setProperty("mx", mx);
    obst->setProperty("my", my);
    obst->setProperty("cycle", cycle);
    obst->setProperty("iteration", 0);
    obst->setProperty("complete", complete);
    int iter = it * cycle;
    obst->setProperty("iter", iter);
    if(complete){
        double noName = 2 * (.5 - fabs(((iter % cycle + 0.0) / cycle) - .5));
        obst->move(x + PA + noName * mx, y + PA + noName * my);
    }
    else{
        obst->move(x + PA + (iter / (cycle + 0.0)) * mx, y + PA + (iter / (cycle + 0.0)) * my);
    }
    moving_list.push_back(obst);
    return obst;
}

QWidget * Map::makeMovingInvisibleObst(int x, int y, int w, int h, int mx, int my, int cycle, double it, bool complete, bool coll){
    QWidget * iobst = makeInvisibleObst(x + PA, y + PA, w, h, coll);
    iobst->setProperty("x_start", x + PA);
    iobst->setProperty("y_start", y + PA);
    iobst->setProperty("mx", mx);
    iobst->setProperty("my", my);
    iobst->setProperty("cycle", cycle);
    iobst->setProperty("complete", complete);
    int iter = it * cycle;
    iobst->setProperty("iter", iter);
    if(complete){
        double noName = 2 * (.5 - fabs(((iter % cycle + 0.0) / cycle) - .5));
        iobst->move(x + PA + noName * mx, y + PA + noName * my);
    }
    else{
        iobst->move(x + PA + (iter / (cycle + 0.0)) * mx, y + PA + (iter / (cycle + 0.0)) * my);
    }
    moving_list.push_back(iobst);
    return iobst;
}

QWidget * Map::makeMovingFin(int x, int y, int w, int h, int mx, int my, int cycle, double it, bool complete, bool coll){
    QWidget * fin = makeFin(x + PA, y + PA, w, h, coll);
    fin->setProperty("x_start", x + PA);
    fin->setProperty("y_start", y + PA);
    fin->setProperty("mx", mx);
    fin->setProperty("my", my);
    fin->setProperty("cycle", cycle);
    fin->setProperty("complete", complete);
    int iter = it * cycle;
    fin->setProperty("iter", iter);
    if(complete){
        double noName = 2 * (.5 - fabs(((iter % cycle + 0.0) / cycle) - .5));
        fin->move(x + PA + noName * mx, y + PA + noName * my);
    }
    else{
        fin->move(x + PA + (iter / (cycle + 0.0)) * mx, y + PA + (iter / (cycle + 0.0)) * my);
    }
    moving_list.push_back(fin);
    return fin;
}

QWidget * Map::makeFollowingObst(int x, int y, int w, int h, double speed, bool coll){
    QWidget * obst = makeObst(x, y, w, h, coll);
    obst->setProperty("velocity", QVector2D(0.0, 0.0));
    obst->setProperty("speed", speed);
    obst->setProperty("pos_f", QRectF(obst->geometry()));
    following_list.push_back(obst);
    return obst;
}

QWidget * Map::makeFollowingInvisibleObst(int x, int y, int w, int h, double speed, bool coll){
    QWidget * iobst = makeInvisibleObst(x, y, w, h, coll);
    iobst->setProperty("velocity", QVector2D(0.0, 0.0));
    iobst->setProperty("speed", speed);
    iobst->setProperty("pos_f", QRectF(iobst->geometry()));
    following_list.push_back(iobst);
    return iobst;
}

QWidget * Map::makeFollowingFin(int x, int y, int w, int h, double speed, bool coll){
    QWidget * fin = makeFin(x, y, w, h, coll);
    fin->setProperty("velocity", QVector2D(0.0, 0.0));
    fin->setProperty("speed", speed);
    fin->setProperty("pos_f", QRectF(fin->geometry()));
    following_list.push_back(fin);
    return fin;
}

Beam * Map::makeBeamObst(int x, int y, double angle, double angle_speed){
    Beam* beam = new Beam(this);
    beam->setPos(x + PA, y + PA);
    beam->setGeometry(0, 0, this->width(), this->height());
    beam->setAngle(angle);
    beam->setProperty("angle_speed", angle_speed);
    beam->setProperty("type", QString("obst"));
    beam_list.push_back(beam);
    return beam;
}

Beam * Map::makeBeamInvisibleObst(int x, int y, double angle, double angle_speed){
    Beam* beam = new Beam(this);
    beam->setPos(x + PA, y + PA);
    beam->setGeometry(0, 0, this->width(), this->height());
    beam->setAngle(angle);
    beam->setProperty("angle_speed", angle_speed);
    beam->setProperty("type", QString("obst_inv"));
    beam_list.push_back(beam);
    return beam;
}

Beam * Map::makeBeamFin(int x, int y, double angle, double angle_speed){
    Beam* beam = new Beam(this);
    beam->setPos(x + PA, y + PA);
    beam->setGeometry(0, 0, this->width(), this->height());
    beam->setAngle(angle);
    beam->setProperty("angle_speed", angle_speed);
    beam->setProperty("type", QString("fin"));
    beam_list.push_back(beam);
    return beam;
}

Beam * Map::makeMovingBeamObst(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete){
    Beam * beam = makeBeamObst(x, y, angle, angle_speed);
    beam->setProperty("x_start", x + PA);
    beam->setProperty("y_start", y + PA);
    beam->setProperty("mx", mx);
    beam->setProperty("my", my);
    beam->setProperty("cycle", cycle);
    beam->setProperty("iteration", 0);
    beam->setProperty("complete", complete);
    movingBeam_list.push_back(beam);
    return beam;
}
Beam * Map::makeMovingBeamInvisibleObst(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete){
    Beam * beam = makeBeamInvisibleObst(x, y, angle, angle_speed);
    beam->setProperty("x_start", x + PA);
    beam->setProperty("y_start", y + PA);
    beam->setProperty("mx", mx);
    beam->setProperty("my", my);
    beam->setProperty("cycle", cycle);
    beam->setProperty("iteration", 0);
    beam->setProperty("complete", complete);
    movingBeam_list.push_back(beam);
    return beam;
}

Beam * Map::makeMovingBeamFin(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete){
    Beam * beam = makeBeamFin(x, y, angle, angle_speed);
    beam->setProperty("x_start", x + PA);
    beam->setProperty("y_start", y + PA);
    beam->setProperty("mx", mx);
    beam->setProperty("my", my);
    beam->setProperty("cycle", cycle);
    beam->setProperty("iteration", 0);
    beam->setProperty("complete", complete);
    movingBeam_list.push_back(beam);
    return beam;
}

void Map::setFadeTimer(int duration){

    fadeTimerActive = true;
    fadeDuration = duration * 20;

}
