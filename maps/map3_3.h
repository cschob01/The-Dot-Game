#ifndef MAP3_3_H
#define MAP3_3_H

#include "../map.h"

class Map3_3 : public Map
{
    Q_OBJECT

public:
    explicit Map3_3(QWidget *parent = nullptr)
    : Map(parent)
    {
        int w = 200;
        int h = 400;
        //Set map size <- Necessary boilerplate
        setMapSize(w, h, true);

        //Set starting data
        starting_coords = QPointF(100.0, 390.0);
        starting_angle = 270.0;
        loading_text = "3:3\nGetting Hotter";

        //Add walls/obstacles/finish
        makeWall(80, h - 40, 10, 40);
        makeWall(110, h - 40, 10, 40);
        makeWall(80, 0, 10, 40);
        makeWall(110, 0, 10, 40);
        makeFin(90, 0, 20, 10);

        int disco = 2;
        for(int i = 0; i < disco; i++){
            makeBeamObst(20, h / 2, (360.0 / disco) * i, 1);
            makeBeamObst(w - 20, h / 2, (360.0 / disco) * i, 1);
        }

        for(int i = 0; i < 9; i++){
            makeWall(80, h - 60 - 40 * i, 10, 20);
            makeWall(110, h - 40 - 40 * i, 10, 20);
        }
    }
    ~Map3_3(){}
};

#endif
