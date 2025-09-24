#include "dotfield.h"

void DotField::paintEvent(QPaintEvent *event){
    // Create a QPainter object to paint on this widget
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    maxSize_h = (width() - 2 * BORDER_SPACE) / (settings.columns + 0.0);
    maxSize_v = (height() - 2 * BORDER_SPACE) / (settings.rows + 0.0);

    for(int i = 0; i < settings.columns; i++){
        std::tuple<double, QString, std::vector<std::pair<double, QColor>>> distance = map->dist(pos, (angleH + (((i + 0.0)/(settings.columns + 0.0)) - .5) * (settings.pov_h + 0.0)));
        for(int j = 0; j < settings.rows; j++){
            paintPixel(&painter, i, j, distance);
        }
    }

}

void DotField::paintPixel(QPainter* painter, int i, int j, std::tuple<double, QString, std::vector<std::pair<double, QColor>>> dist){

    double vert_angle = qDegreesToRadians(-(angleV + (-((j + 0.0)/(settings.rows + 0.0)) + .5) * (settings.pov_v + 0.0)));

    bool ground = true;

    double dist_to_ground = settings.height / sin(vert_angle);
    if((dist_to_ground < 0) && (!settings.roofs)){
        ground = false;
    }
    dist_to_ground = abs(dist_to_ground);

    double dist_to_wall = std::get<0>(dist) / cos(vert_angle);

    if(dist_to_ground < dist_to_wall){
        if(ground){
            painter->setBrush(Qt::blue);
        }
        else{
            painter->setBrush(Qt::NoBrush);
        }
    }
    else{
        if(std::get<1>(dist) == "obst_inv"){
            painter->setBrush(Qt::NoBrush);
        }
        else if(std::get<1>(dist) == "wall"){
            painter->setBrush(QColor(0, 116, 230));
        }
        else if(std::get<1>(dist) == "obst"){
            painter->setBrush(Qt::red);
        }
        else if(std::get<1>(dist) == "fin"){
            painter->setBrush(Qt::green);
        }
    }

    double distance = fmin(dist_to_ground, dist_to_wall);
    
    std::vector<std::pair<double, QColor>> port_list = std::get<2>(dist);
    if(distance == dist_to_ground){
        for(int i = 0; i < port_list.size(); i++){
            if((port_list.at(i).first / cos(vert_angle) < distance) && (ground)){
                painter->setBrush(port_list.at(i).second.darker(100 + 20 * i));
            }
        }
    }
    double p_size;
    if(distance > settings.render + 5){
        p_size = 0.0;
    }
    else{
        p_size = (settings.render - distance) / (settings.render + 0.0);
    }

    if(map->pixelActive(i, j)){
        painter->drawRect(QRect(BORDER_SPACE + i * maxSize_h, BORDER_SPACE + j * maxSize_v, p_size * maxSize_h, p_size * maxSize_v));
    }

}
