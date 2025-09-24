#ifndef MAP2_2_H
#define MAP2_2_H

#include "../map.h"

class Map2_2 : public Map
{
    Q_OBJECT

public:
    explicit Map2_2(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(400, 100, true);

        makeWall(10, 10, 380, 10);
        makeWall(10, 10, 10, 80);
        makeWall(380, 10, 10, 80);
        makeWall(10, 80, 380, 10);

        //Set starting data
        starting_coords = QPointF(25.0 + 10, 50.0);
        starting_angle = 0.0;
        loading_text = "2:2\nWatch Your Step";

        // makeInvisibleObst(10 + 10, 35, 5, 5 + 20 + 5);
        // makeInvisibleObst(10 + 10, 35, 5 + 20 + 5 + 350, 5);
        // makeInvisibleObst(10 + 10, 60, 5 + 20 + 5 + 350, 5);
        makeFin(10 + 10 + 350, 35, 5, 5 + 20 + 5);

        forced_settings.render = 35;
        double speed_setter = 2;

        makeMovingInvisibleObst(60 + 0  , 0   , 20, 5, 0,    100, 200 * speed_setter, .2 , false, true);
        makeMovingInvisibleObst(60 + 20 , 0   , 20, 5, 0,    100, 150 * speed_setter, .8 , false, true);
        makeMovingInvisibleObst(60 + 40 , 100 , 20, 5, 0,   -100, 200 * speed_setter, .5 , false, true);
        makeMovingInvisibleObst(60 + 60 , 100 , 20, 5, 0,   -130, 100 * speed_setter, .9 , false, true);
        makeMovingInvisibleObst(60 + 80 , 0   , 20, 5, 0,    100, 150 * speed_setter, .2 , false, true);
        makeMovingInvisibleObst(60 + 100, 100 , 20, 5, 0,   -150, 160 * speed_setter, .38, false, true);
        makeMovingInvisibleObst(60 + 120, 100 , 20, 5, 0,   -150, 100 * speed_setter, .79, false, true);
        makeMovingInvisibleObst(60 + 140, 0   , 20, 5, 0,    132, 200 * speed_setter, .2 , false, true);
        makeMovingInvisibleObst(60 + 160, 100 , 20, 5, 0,   -150, 100 * speed_setter, .1 , false, true);
        makeMovingInvisibleObst(60 + 180, 0   , 20, 5, 0,    120, 210 * speed_setter, .76, false, true);
        makeMovingInvisibleObst(60 + 200, 0   , 20, 5, 0,    110, 140 * speed_setter, .09, false, true);
        makeMovingInvisibleObst(60 + 220, 100 , 20, 5, 0,   -120, 110 * speed_setter, .39, false, true);
        makeMovingInvisibleObst(60 + 240, 0   , 20, 5, 0,    100, 100 * speed_setter, .3 , false, true);
        makeMovingInvisibleObst(60 + 260, 0   , 20, 5, 0,    160, 90 * speed_setter, .9 , false, true);
        makeMovingInvisibleObst(60 + 280, 100 , 20, 5, 0,   -100, 120 * speed_setter, .54, false, true);

        makeMovingInvisibleObst(60 + 270  , 0   , 20, 5, 0,    100, 200 * speed_setter, .4 , false, true);
        makeMovingInvisibleObst(60 + 250 , 0   , 20, 5, 0,    100, 150 * speed_setter, .15 , false, true);
        makeMovingInvisibleObst(60 + 230 , 100 , 20, 5, 0,   -100, 200 * speed_setter, .53 , false, true);
        makeMovingInvisibleObst(60 + 210 , 100 , 20, 5, 0,   -130, 100 * speed_setter, .0 , false, true);
        makeMovingInvisibleObst(60 + 190 , 0   , 20, 5, 0,    100, 150 * speed_setter, .65 , false, true);
        makeMovingInvisibleObst(60 + 170, 100 , 20, 5, 0,   -150, 160 * speed_setter, .38, false, true);
        makeMovingInvisibleObst(60 + 150, 100 , 20, 5, 0,   -150, 100 * speed_setter, .34, false, true);
        makeMovingInvisibleObst(60 + 130, 0   , 20, 5, 0,    132, 200 * speed_setter, .61 , false, true);
        makeMovingInvisibleObst(60 + 110, 100 , 20, 5, 0,   -150, 100 * speed_setter, .23 , false, true);
        makeMovingInvisibleObst(60 + 90, 0   , 20, 5, 0,    120, 210 * speed_setter, .53, false, true);
        makeMovingInvisibleObst(60 + 70, 0   , 20, 5, 0,    110, 140 * speed_setter, .09, false, true);
        makeMovingInvisibleObst(60 + 50, 100 , 20, 5, 0,   -120, 110 * speed_setter, .52, false, true);
        makeMovingInvisibleObst(60 + 30, 0   , 20, 5, 0,    100, 100 * speed_setter, .32 , false, true);
        makeMovingInvisibleObst(60 + 10, 100   , 20, 5, 0,    -160, 90 * speed_setter, .67 , false, true);
        makeMovingInvisibleObst(60 + (-10), 100 , 20, 5, 0,   -100, 120 * speed_setter, .40, false, true);

        
    }
    ~Map2_2(){}
};

#endif
