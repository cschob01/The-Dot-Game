#ifndef MAP3_4_H
#define MAP3_4_H

#include "../map.h"

class Map3_4 : public Map
{
    Q_OBJECT

public:
    explicit Map3_4(QWidget *parent = nullptr)
    : Map(parent)
    {
        int w = 930;
        int h = 210;
        //Set map size <- Necessary boilerplate
        setMapSize(w, h);
        makeWall(-10, -10, w + 20, 10);
        makeWall(-10, -10, 10, 30);

        //Set starting data
        starting_coords = QPointF(5.0, 5.0);
        // starting_coords = QPointF(500.0, 5.0);
        starting_angle = 0.0;
        loading_text = "3:4\nGeneral";

        //Add walls/obstacles/finish
        makeWall(0, 10, 40, 10);

        int start_x = 40;
        int diam = 60;

        for(int i = 0; i < 6; i++){
            makeWall(start_x - 10, 10, 10, diam);
            makeWall(start_x - 10, diam, diam + 20, 10);
            makeWall(start_x + diam, 10, 10, diam);
            makeWall(start_x + diam, 10, 30, 10);
            makeBeamObst(start_x + diam / 2, diam/2, 0, -1.1);
            makeBeamObst(start_x + diam / 2, diam/2, 180, -1.1);
            start_x = start_x + diam + 10;
            diam = diam + 30;
        }
        makeWall(930, 0, 10, 20);
        makeFin(920, 0, 10, 10);
    }
    ~Map3_4(){}
};

#endif
