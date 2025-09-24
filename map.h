#ifndef MAP_H
#define MAP_H

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
#include <random>
#include <QGraphicsOpacityEffect>

#include "overlay.h"
#include "settings.h"
#include "beam.h"

#include <tuple> //For effects list

class Map : public QWidget
{
    Q_OBJECT

protected:

    std::vector<QWidget*> collision_list;
    std::vector<QWidget*> moving_list;
    std::vector<QWidget*> following_list;
    std::vector<Beam*> movingBeam_list;
    std::vector<Beam*> beam_list;
    std::vector<QWidget*> portal_list;
    Overlay * overlay;
    QPointF starting_coords;
    double starting_angle;
    QString loading_text;

    Settings forced_settings;

    //map_maker.cpp
    QWidget * makeWall(int x, int y, int w, int h, bool coll = true);
    QWidget * makeObst(int x, int y, int w, int h, bool coll = true);
    QWidget * makeFin(int x, int y, int w, int h, bool coll = true);
    QWidget * makeInvisibleObst(int x, int y, int w, int h, bool coll = true);
    QWidget * makeMovingObst(int x, int y, int w, int h, int mx, int my, int cycle, double iter = 0, bool complete = true, bool coll = true);
    QWidget * makeMovingInvisibleObst(int x, int y, int w, int h, int mx, int my, int cycle, double iter = 0, bool complete = true, bool coll = true);
    QWidget * makeMovingFin(int x, int y, int w, int h, int mx, int my, int cycle, double iter = 0, bool complete = true, bool coll = true);
    QWidget * makeFollowingObst(int x, int y, int w, int h, double speed, bool coll = true);
    QWidget * makeFollowingInvisibleObst(int x, int y, int w, int h, double speed, bool coll = true);
    QWidget * makeFollowingFin(int x, int y, int w, int h, double speed, bool coll = true);
    Beam * makeBeamObst(int x, int y, double angle, double angle_speed);
    Beam * makeBeamInvisibleObst(int x, int y, double angle, double angle_speed);
    Beam * makeBeamFin(int x, int y, double angle, double angle_speed);
    Beam * makeMovingBeamObst(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete = true);
    Beam * makeMovingBeamInvisibleObst(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete = true);
    Beam * makeMovingBeamFin(int x, int y, double angle, double angle_speed, int mx, int my, int cycle, bool complete = true);
    void setMapSize(int width, int height, bool border = false);
    void setFadeTimer(int duration);

    //Effects:
    QWidget * makePortal(int x1, int y1, int x2, int y2, int width, int height, QColor color);

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

    QString collides(QPointF coords, bool checkBeams = true);
    void update(QPointF coords);

    std::tuple<double, QString, std::vector<std::pair<double, QColor>>> dist(QPointF coords, double angle, bool checkBeams = true);
    double startingAngle();
    QPointF startingCoords();
    QString loadingText();
    Settings forcedSettings(Settings settings);
    QString forcedSettingsText();
    bool pixelActive(int i, int j);

    //Intro cutscene
    void startAnimation(int collumns, int rows, int milliseconds);

    //Changing player status
    bool getDead();

    QWidget * in_portal(QPointF coords);

    void optimize(int ren);

private:

    static const int PA = 150;

    //Animation
    int duration;
    int timer_count;
    int rows;
    int collumns;
    QTimer* timer;
    QElapsedTimer* elapsed;
    QVector<QVector<bool>> pixels_active;

    //Turning off lights
    bool fadeTimerActive = false;
    int fadeDuration = -1;
    void fadeIndex(int collumn, int row);
    bool dead = false;

    //Moving widgets
    int iteration;
    bool check_rect(QRectF rect, bool x_axis, QVector2D vel, QWidget * f);
    bool collides_rect(QRectF rect_f, QWidget * f);

    //Portals
    QPointF honeIn(QPointF shot, double rad);

    //Optimization
    int max_ren = 500;
    
};

#endif
