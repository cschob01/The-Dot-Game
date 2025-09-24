#ifndef MAP3_1_H
#define MAP3_1_H

#include "../map.h"

class Map3_1 : public Map
{
    Q_OBJECT

public:
    explicit Map3_1(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(400, 200, true);

        //Set starting data
        starting_coords = QPointF(20.0, 125.0);
        starting_angle = 0.0;
        loading_text = "3:1\nBeam Me Up";

        //Add walls/obstacles/finish
        makeBeamObst(200, 20, 0, .78);
        makeWall(0, 110, 40, 10);
        makeWall(50, 160, 20, 10);
        makeWall(100, 60, 10, 10);
        makeWall(150, 110, 10, 10);
        makeWall(180, 180, 30, 10);
        makeWall(195, 160, 10, 10);
        makeWall(230, 175, 5, 10);
        makeWall(240, 175, 5, 10);
        makeWall(250, 175, 5, 10);
        makeWall(260, 175, 5, 10);
        makeWall(290 - 55, 100, 10, 10);
        makeWall(320 - 55, 120, 20, 10);
        for(int i = 0; i < 5; i++){
            makeWall(360 - 20 + i * 7, 170, 3, 3);
            makeWall(361 - 20 + i * 6, 150, 3, 3);
        }

        makeFin(390, 0, 10, 200);

    }
    ~Map3_1(){}
};

#endif
