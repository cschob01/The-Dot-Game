#include "map1.h"
#include <QDebug>

Map1::Map1(QWidget *parent)
    : Map(parent)
{

    //Set map size <- Necessary boilerplate
    setMapSize(200, 200);

    //Set starting data
    starting_coords = QPointF(5.0, 30.0);
    starting_angle = 0.0;
    loading_text = "1\nBasic Training";

    //Add walls/obstacles/finish
    // makeWall(10, 10, 40, 40);
    // makeFin(100, 100, 40, 40);
    // makeInvisibleObst(10, 100, 40, 40);
    // makeMovingObst(10, 10, 40, 40, 50, 0, 50);
    makeWall(10, 50, 110, 20);
    makeWall(10, 180, 180, 20);
    makeWall(100, 50, 10, 100);
    makeWall(10, 10, 180, 19);
    makeWall(7, 49, 20, 20);
    // makeFollowingObst(150, 100, 20, 20, .1);
    // makeFollowingObst(150, 140, 20, 20, .1);
    // makeBeamInvisibleObst(150, 100, 0, .8);
    makeMovingBeamObst(130, 100, 180, -1.9, 40, 0, 100);
    makeFin(60, 100, 20, 20);

    //Mess with settings (optional)
    // forced_settings.map = false;

}

Map1::~Map1(){}
