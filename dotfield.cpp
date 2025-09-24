#include "dotfield.h"

void DotField::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_Escape: {
            if(status.m) status.m = false;
            else endLevel(false);
            break;
        }
        case Qt::Key_W: status.w = true; break;
        case Qt::Key_A: status.a = true; break;
        case Qt::Key_S: status.s = true; break;
        case Qt::Key_D: status.d = true; break;
        case Qt::Key_Up: status.up = true; break;
        case Qt::Key_Down: status.down = true; break;
        case Qt::Key_Left: status.l = true; break;
        case Qt::Key_Right: status.r = true; break;
        // case Qt::Key_M: if(settings.map) status.m = true; break;
        case Qt::Key_M: if(settings.map) status.m = !status.m; break;
        case Qt::Key_Shift: status.shift = true; break;
        case Qt::Key_T: status.t = true; break; // Testing
        default: break;
    }
    QWidget::keyPressEvent(event);
}

void DotField::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W: status.w = false; break;
        case Qt::Key_A: status.a = false; break;
        case Qt::Key_S: status.s = false; break;
        case Qt::Key_D: status.d = false; break;
        case Qt::Key_Up: status.up = false; break;
        case Qt::Key_Down: status.down = false; break;
        case Qt::Key_Left: status.l = false; break;
        case Qt::Key_Right: status.r = false; break;
        // case Qt::Key_M: status.m = false; break;
        case Qt::Key_Shift: status.shift = false; break;
        case Qt::Key_T: status.t = false; break; // Testing
        default: break;
    }
    QWidget::keyReleaseEvent(event);
}

void DotField::setTimer(bool active){
    if (active) {
        if (!timer->isActive()) {
            // qDebug() << "Timer starting.";
            timer->start(MPF);
        }
    } else {
        if (timer->isActive()) {
            // qDebug() << "Timer stopping.";
            timer->stop();
        }
    }
}

void DotField::update(){

    //------------------LAG CHECKING
    static QElapsedTimer timer;
    static qint64 lastTickTime = -1;

    // Start the timer on first call
    if (!timer.isValid()) {
        timer.start();
        lastTickTime = timer.elapsed();
    }

    // Time since last update call
    qint64 now = timer.elapsed();
    qint64 delta = now - lastTickTime;

    // Detect lag (tick was delayed more than expected)
    if (delta > 55) {  // Expected 50ms, allow small slack
        qDebug() << "⚠️ Lag detected! Time since last tick:" << delta << "ms";
    }
    
    lastTickTime = now;
    
    // Measure how long this update takes
    QElapsedTimer tickDurationTimer;
    tickDurationTimer.start();
    //------------------LAG CHECKING

    if(status.t){
        qDebug() << status.count;
        status.count++;
    }

    if(map_in_motion){
        map->update(pos);
    }

    if(status.m){
        if(!held_m){
            QScrollBar* hScrollBar = scrollArea->horizontalScrollBar();
            QScrollBar* vScrollBar = scrollArea->verticalScrollBar();
    
            hScrollBar->setValue(pos.x() - MAP_VISIBILITY_H / 2);
            vScrollBar->setValue(pos.y() - MAP_VISIBILITY_V / 2);
            

            scrollArea->horizontalScrollBar()->setVisible(false);
            scrollArea->verticalScrollBar()->setVisible(false);
            scrollArea->show();
            held_m = true;
        }
    }
    else{
        held_m = false;
        scrollArea->hide();

        //New system for getting rid of exploit
        QPoint direction(0, 0);
        if(status.w) direction += QPoint(1, 0);
        if(status.a) direction += QPoint(0, -1);
        if(status.s) direction += QPoint(-1, 0);
        if(status.d) direction += QPoint(0, 1);
        if(direction != QPoint(0, 0)){
            double angleRad = std::atan2(direction.y(), direction.x());
            double angleDeg = angleRad * 180.0 / M_PI;
            moveThere(SPEED * ( 1 + 1 * (SPRINT_MULTIPLIER - 1)), angleH + angleDeg);
        }

        if(status.up){if(angleV < max_vertical_look) angleV += settings.sensitivityV;}
        if(status.down){if(angleV > -max_vertical_look) angleV -= settings.sensitivityV;}
        if(status.l){angleH -= settings.sensitivityH;}
        if(status.r){angleH += settings.sensitivityH;}
    }

    QString collision_result = map->collides(pos);
    if(collision_result == "fin"){
        if(!end_called){
            endLevel(true);
        }
    }
    else if(collision_result.startsWith("obst") || map->getDead()){
        if(!end_called){
            endLevel(false);
        }
    }

    QWidget::update();

    QWidget * port = map->in_portal(pos);
    if(port != nullptr){
        if(!teleported){
            pos.setX(pos.x() + port->property("tx").toInt());
            pos.setY(pos.y() + port->property("ty").toInt());
            teleported = true;
        }
    }
    else{
        teleported = false;
    }

    //------------------LAG CHECKING
    qint64 tickDuration = tickDurationTimer.elapsed();
    if (tickDuration > 50) {
    qDebug() << "⚠️ Update took too long:" << tickDuration << "ms";
    }
    //------------------LAG CHECKING

}

void DotField::moveThere(double step, double angle){

    double rad = qDegreesToRadians(angle);

    QPointF test_x = QPointF(pos.x() + step * qCos(rad), pos.y());
    QPointF test_y = QPointF(pos.x(), pos.y() + step * qSin(rad));

    pos = QPointF(pos.x() + (map->collides(test_x) != "wall") * step * qCos(rad),
         pos.y() + (map->collides(test_y) != "wall") * step * qSin(rad));

}
