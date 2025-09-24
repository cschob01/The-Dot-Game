#include "map.h"

Map::Map(QWidget *parent){

    loading_text = "";

    forced_settings.pov_h = -1;
    forced_settings.pov_v = -1;
    forced_settings.columns = -1;
    forced_settings.rows = -1;
    forced_settings.render = -1;
    forced_settings.height = -1;
    forced_settings.sensitivityH = -1;
    forced_settings.sensitivityV = -1;
    forced_settings.map = true;

    iteration = 0;

    timer = new QTimer(this);
    elapsed = new QElapsedTimer();

    connect(timer, &QTimer::timeout, this, [=]() mutable {
        timer_count++;
        int time_used = (rows + 5) * timer_count/100.0;
        if(time_used < rows){
            for(int i = time_used - 5; i < time_used; i++){
                for(int j = 0; j < collumns; j++){
                    pixels_active[j][i] = true;
                }
            }
        }
        if (elapsed->elapsed() >= duration) {
            timer->stop();
            for(int i = 0; i < collumns; i++){
                for(int j = 0; j < rows; j++){
                    pixels_active[i][j] = true;
                }
            }
        }
    });

}

Map::~Map(){

}

QString Map::collides(QPointF coords, bool checkBeams){

    if(!this->rect().contains(coords.toPoint())){
        return QString("obst");
    }
    for(int i = 0; i < collision_list.size(); i++){
        if(collision_list.at(i)->geometry().contains(coords.toPoint())){
            return QString(collision_list.at(i)->property("type").toString());
        }
    }

    if(checkBeams){
        for(int i = 0; i < beam_list.size(); i++){
            if(beam_list.at(i)->collides(coords)){
                return beam_list.at(i)->property("type").toString();
            }
        }
    }

    return QString("nothing");

}

std::tuple<double, QString, std::vector<std::pair<double, QColor>>> Map::dist(QPointF coords, double angle, bool checkBeams){

    QPointF shot = coords;
    double rad = qDegreesToRadians(angle);

    std::vector<std::pair<double, QColor>> portal_list;

    QWidget * port_in = in_portal(coords);
    bool in_port = (port_in != nullptr);
    double shot_length = 0;
    double tel_dist = max_ren + 1;
    QColor tel_color = QColor("red");
    if(in_port){
        portal_list.push_back(std::make_pair(0, qvariant_cast<QColor>(port_in->property("color"))));
    }

    while(collides(shot, checkBeams) == "nothing" && ((shot_length + QLineF(coords, shot).length() < max_ren)||(!checkBeams))){
        QWidget * port = in_portal(shot);
        if((port != nullptr) && (checkBeams)){
            if(!in_port){
                shot = honeIn(shot, rad);
                shot_length += QLineF(coords, shot).length();
                if(tel_dist == max_ren + 1){
                    portal_list.push_back(std::make_pair(shot_length, qvariant_cast<QColor>(port->property("color"))));
                }
                in_port = true;
                shot.setX(shot.x() + port->property("tx").toInt());
                shot.setY(shot.y() + port->property("ty").toInt());
                coords = shot;
            }
        }
        else{
            in_port = false;
        }

        shot.setX(shot.x() + qCos(rad) * 1);
        shot.setY(shot.y() + qSin(rad) * 1);
    }
    shot.setX(shot.x() - qCos(rad) * 1);
    shot.setY(shot.y() - qSin(rad) * 1);

    while(collides(shot, checkBeams) == "nothing" && ((shot_length + QLineF(coords, shot).length() < max_ren)||(!checkBeams))){
        shot.setX(shot.x() + qCos(rad) * .1);
        shot.setY(shot.y() + qSin(rad) * .1);
    }

    double total_length = shot_length + QLineF(coords, shot).length();
    if((total_length > max_ren + 1) && (checkBeams)){
        qDebug() << "Dist leak!: " << total_length;
    }
    std::tuple<double, QString, std::vector<std::pair<double, QColor>>> 
        rt(total_length, collides(shot, checkBeams), portal_list);
    return rt;

}

QPointF Map::honeIn(QPointF shot, double rad){
    shot.setX(shot.x() - qCos(rad) * 1);
    shot.setY(shot.y() - qSin(rad) * 1);
    while(in_portal(shot) == nullptr){
        shot.setX(shot.x() + qCos(rad) * .1);
        shot.setY(shot.y() + qSin(rad) * .1);
    }
    return shot;
}

QWidget * Map::in_portal(QPointF coords){
    for(int i = 0; i < portal_list.size(); i++){
        if(portal_list.at(i)->geometry().contains(coords.toPoint())){
            return static_cast<QWidget*>(portal_list.at(i)->property("link").value<void*>());
        }
    }
    return nullptr;
}

void Map::update(QPointF coords){
    overlay->setDotPosition(coords);
    iteration++;

    //Moving obstacles
    for(int i = 0; i < moving_list.size(); i++){
        int x = moving_list.at(i)->property("x_start").toInt();
        int y = moving_list.at(i)->property("y_start").toInt();
        int mx = moving_list.at(i)->property("mx").toInt();
        int my = moving_list.at(i)->property("my").toInt();
        int cycle = moving_list.at(i)->property("cycle").toInt();
        int iter = moving_list.at(i)->property("iter").toInt();
        if(moving_list.at(i)->property("complete").toBool()){
            double noName = 2 * (.5 - fabs((((iteration + iter) % cycle + 0.0) / cycle) - .5));
            moving_list.at(i)->move(x + noName * mx, y + noName * my);
        }
        else{
            int x_go = x + (((iteration + iter) % cycle + 0.0) / cycle) * mx;
            int y_go = y + (((iteration + iter) % cycle + 0.0) / cycle) * my;
            moving_list.at(i)->move(x_go, y_go);
        }
    }

    //Following obstacles
    for(int i = 0; i < following_list.size(); i++){

        //Retreiving info
        QWidget * f = following_list.at(i);
        QRectF pos_f = f->property("pos_f").toRectF();
        QVector2D vel = f->property("velocity").value<QVector2D>();

        QVector2D acc = QVector2D(coords) - QVector2D(f->x() + f->width()/2, f->y() + f->height() / 2);
        acc = acc.normalized() * f->property("speed").toDouble();
        vel = vel + acc;

        if(!check_rect(pos_f, true, vel, f)){
            vel.setX(0.0);
        }
        if(!check_rect(pos_f, false, vel, f)){
            vel.setY(0.0);
        }
        if(collides_rect(pos_f.translated(vel.toPointF()), f)){
            vel = QVector2D(0.0, 0.0);
        }

        pos_f.translate(vel.toPointF());

        //Adding friction
        double friction = f->property("speed").toDouble() / 10;
        double new_mag = vel.length() - friction;
        if (new_mag < 0) new_mag = 0;
        if (vel.length() != 0) {
            vel = vel.normalized() * new_mag;
        }

        f->setProperty("velocity", vel);
        f->setProperty("pos_f", pos_f);
        f->move(pos_f.x(), pos_f.y());
        
    }

    //Moving beams
    for(int i = 0; i < movingBeam_list.size(); i++){
        int x = movingBeam_list.at(i)->property("x_start").toInt();
        int y = movingBeam_list.at(i)->property("y_start").toInt();
        int mx = movingBeam_list.at(i)->property("mx").toInt();
        int my = movingBeam_list.at(i)->property("my").toInt();
        int cycle = movingBeam_list.at(i)->property("cycle").toInt();
        if(movingBeam_list.at(i)->property("complete").toBool()){
            double noName = 2 * (.5 - fabs(((iteration % cycle + 0.0) / cycle) - .5));
            // movingBeam_list.at(i)->move(x + noName * mx, y + noName * my);
            movingBeam_list.at(i)->setPos(x + noName * mx, y + noName * my);
        }
        else{
            int x_go = x + ((iteration % cycle + 0.0) / cycle) * mx;
            int y_go = y + ((iteration % cycle + 0.0) / cycle) * my;
            // movingBeam_list.at(i)->move(x_go, y_go);
            movingBeam_list.at(i)->setPos(x_go, y_go);
        }
    }

    //Beams
    for(int i = 0; i < beam_list.size(); i++){
        double newAngle = beam_list.at(i)->getAngle() 
            + beam_list.at(i)->property("angle_speed").toDouble();
        beam_list.at(i)->setAngle(newAngle);
        beam_list.at(i)->updateBeam(std::get<0>(dist(beam_list.at(i)->getPos(), newAngle, false)));
    }

    if(fadeTimerActive && (iteration % (fadeDuration / 100) == 0)){
        int count = iteration / (fadeDuration / 100) - 1;

        if(count % 2 == 0) fadeIndex(count / 10, count % 10);
        if(count % 2 == 1) fadeIndex((count / 10 + count * 2) % 10, (count * 3) % 10);

        // qDebug() << count;
        if(count == 99){
            dead = true;
            fadeTimerActive = false;
        }
    }
}

//Helper for following widgets
bool Map::check_rect(QRectF rect, bool x_axis, QVector2D vel, QWidget * f){

    if(x_axis){
        vel.setY(0);
        rect.translate(vel.toPointF());
        if(collides_rect(rect, f)){
            return false;
        }
    }
    else{ //Checking y_axis
        vel.setX(0);
        rect.translate(vel.toPointF());
        if(collides_rect(rect, f)){
            return false;
        }
    }
    return true;
}

bool Map::collides_rect(QRectF rect_f, QWidget * f){
    if (!QRectF(this->rect()).contains(rect_f)){
        return true;
    }
    for(int i = 0; i < collision_list.size(); i++){
        if(collision_list.at(i) == f) continue;
        //Custom intersect check, allowing leeway for common edges
        QRect intersection = rect_f.toRect().intersected(collision_list.at(i)->geometry());
        if(intersection.isValid() && intersection.width() > 0 && intersection.height()){
            return true;
        }
    }
    return false;
}

double Map::startingAngle(){
    return starting_angle;
}

QPointF Map::startingCoords(){
    return QPointF(starting_coords + QPointF(PA, PA));
}

QString Map::loadingText(){
    return loading_text;
}

Settings Map::forcedSettings(Settings settings){

    if(forced_settings.pov_h != -1) settings.pov_h = forced_settings.pov_h;
    if(forced_settings.pov_v != -1) settings.pov_v = forced_settings.pov_v;
    if(forced_settings.columns != -1) settings.columns = forced_settings.columns;
    if(forced_settings.rows != -1) settings.rows = forced_settings.rows;
    if(forced_settings.render != -1) settings.render = forced_settings.render;
    if(forced_settings.height != -1) settings.height = forced_settings.height;
    if(forced_settings.sensitivityH != -1) settings.sensitivityH = forced_settings.sensitivityH;
    if(forced_settings.sensitivityV != -1) settings.sensitivityV = forced_settings.sensitivityV;
    settings.map = forced_settings.map;

    return settings;

}

QString Map::forcedSettingsText(){

    QString text = "Modifiers:";
    QString og_text = text;
    
    if(forced_settings.pov_h != -1) text += "\nHorizontal POV";
    if(forced_settings.pov_v != -1) text += "\nVertical POV";
    if(forced_settings.columns != -1) text += "\nDot Collumns";
    if(forced_settings.rows != -1) text += "\nDot Rows";
    if(forced_settings.render != -1) text += "\nRender Distance";
    if(forced_settings.height != -1) text += "\n[ERROR]";
    if(forced_settings.sensitivityH != -1) text += "\nHorizontal Sensitivity";
    if(forced_settings.sensitivityV != -1) text += "\nVertical Sensitivity";
    if(forced_settings.map == false) text += "\nMap Disabled";

    if(text == og_text) text += "\nNone";

    return text;
}

void Map::startAnimation(int collumns, int rows, int milliseconds){

    pixels_active = QVector<QVector<bool>>(collumns, QVector<bool>(rows, false));

    this->rows = rows;
    this->collumns = collumns;

    duration = milliseconds;
    timer_count = 0;
    elapsed->start();
    timer->start(milliseconds / 100); //Fire a hundred times within the timespan

}

bool Map::pixelActive(int collumn, int row){
    return pixels_active[collumn][row];
}

void Map::fadeIndex(int collumn, int row){
    for(int i = 0; i < collumns / 10; i++){
        for(int j = 0; j < rows / 10; j++){
            pixels_active[i * 10 + collumn][j * 10 + row] = false;
        }
    }
}

bool Map::getDead(){
    return dead;
}

void Map::optimize(int ren){
    max_ren = ren;
}
