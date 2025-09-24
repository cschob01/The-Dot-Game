#ifndef MAP3_5_H
#define MAP3_5_H

#include "../map.h"

class Map3_5 : public Map
{
    Q_OBJECT

public:
    explicit Map3_5(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(400, 400, true);

        //Set starting data
        starting_coords = QPointF(200.0, 10.0);
        // starting_coords = QPointF(30.0, 375.0);
        starting_angle = 90.0;
        loading_text = "3:5\nThe Windmill";

        //Add walls/obstacles/finish
        int disco = 4;
        for(int i = 0; i < disco; i++){
            makeBeamObst(200, 200, (360.0 / disco) * i, -.8);
        }

        for(int i = 0; i < 3; i++){
            makeWall(190, 20 + 40 * i, 20, 20);
            makeWall(360 - 40 * i, 190, 20, 20);
        }

        makeMovingObst(400 - 30, 220 + 0, 10, 20, 0, 20, 75, 0);
        makeMovingObst(400 - 30, 220 + 50, 10, 20, 0, 20, 50, 0);
        makeMovingObst(400 - 30, 220 + 100, 10, 20, 0, 20, 100, 0);

        for(int i = 0; i < 12; i++){
            makeWall(360 - 30 * i, 375, 20, 5);
        }
        makeMovingInvisibleObst(20, 380, 380, 20, 0, 20, 300, 0);
        makeWall(40, 360, 10, 20);
        makeWall(20, 360, 20, 10);

        for(int i = 0; i < 5; i++){
            makeMovingObst(0, 400, 20, 60, 0, -460, 1000, (1.0 / 5) * i, false, true);
        }
        makeWall(-10, -60, 40, 60);
        makeWall(-10, 400, 40, 60);
        for(int i = 0; i < 7; i++){
            makeWall(20, 340 - 50 * i, 10, 32);
        }
        makeObst(0, 0, 10, 400);
        makeFin(20, 0, 10, 40);
    }
    ~Map3_5(){}
};

#endif
