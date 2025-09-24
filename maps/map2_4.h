#ifndef MAP2_4_H
#define MAP2_4_H

#include "../map.h"

class Map2_4 : public Map
{
    Q_OBJECT

public:
    explicit Map2_4(QWidget *parent = nullptr)
    : Map(parent)
    {
        int h = 200;
        //Set map size <- Necessary boilerplate
        setMapSize(920, h, true);
        int leway = 140;
        int gapSize = 40;

        //Set starting data
        starting_coords = QPointF(10.0, 100.0);
        starting_angle = 0.0;
        loading_text = "2:4\nNothing Yet";

        int w = 500;
        //Add walls/obstacles/finish
        // makeMovingObst();
        int speed  = 600;

        //First obstacles
        makeMovingObst(30, -1 * 190 + 50, w - 60, 150, 0, 180 - gapSize, speed, 0.25);
        makeMovingObst(30, 10 + gapSize, w - 60, 150, 0, 180 - gapSize, speed, 0.25);
        makeMovingObst(30, 5, 20, 15, w - 60 - 20, h - 50 - 10, speed, 0.25);
        makeMovingObst(30, 40, 20, 15, w - 60 - 20, h - 50 - 10, speed, 0.25);
        for(int i = 0; i < 4; i++){
            makeMovingObst(35, i * 50, 10, 30, w - 60 - 20, 0, speed, 0.25);
        }
        //Ends at x=470

        //Second obstacles
        for(int i = 0; i < 20; i++){
            double cycle_spot = 0.25 - .02 * i;
            if(cycle_spot < 0){
                cycle_spot = 1 + cycle_spot;
            }
            makeMovingObst(470 + 10 * i, -1 * 190 + 50, 10, 150, 0, 180 - gapSize, speed, cycle_spot);
            makeMovingObst(470 + 10 * i, 10 + gapSize, 10, 150, 0, 180 - gapSize, speed, cycle_spot);
        }
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                makeInvisibleObst(470 + 40 * i, j * 40, 5, 8);
                makeInvisibleObst(490 + 40 * i, 20 + j * 40, 5, 8);
            }
        }

        //Third obstacle
        w = 300;
        makeMovingObst(670, -1 * 190 + 50, w - 60, 150, 0, 180 - gapSize, speed, 0.87);
        makeMovingObst(670, 10 + gapSize, w - 60, 150, 0, 180 - gapSize, speed, 0.87);
        makeMovingInvisibleObst(670, 5, 20, 15, w - 60 - 20, h - 50 - 10, speed, 0.87);
        makeMovingInvisibleObst(670, 40, 20, 15, w - 60 - 20, h - 50 - 10, speed, 0.87);
        for(int i = 0; i < 4; i++){
            makeMovingInvisibleObst(675, i * 50, 10, 30, w - 60 - 20, 0, speed, 0.87);
        }

        //Leway
        makeWall(-10, -1 * leway, 920 + 20, leway);
        makeWall(-10, h, 920 + 20, leway);

        makeFin(910, 0, 10, h);
        
    }
    ~Map2_4(){}
};

#endif
