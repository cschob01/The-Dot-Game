#ifndef MAP1_5_H
#define MAP1_5_H

#include "../map.h"

class Map1_5 : public Map
{
    Q_OBJECT

public:
    explicit Map1_5(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(400, 450, true);

        //Set starting data
        starting_coords = QPointF(200, 50);
        starting_angle = 90.0;
        loading_text = "1:5\nDanger Zones";

        int cycle_time = 1000;
        for(int j = 0; j < 3; j++){
            for(int i = 0; i < 7; i++){
                makeMovingObst(20, 70 + 80 * j, 5, 40, 340 - 50 * i, 0, cycle_time);
            }
            for(int i = 0; i < 7; i++){
                makeMovingObst(20, 70 + 40 + 80 * j, 5, 40, 340 - 50 * i, 0, cycle_time, .5);
            }
            for(int i = 0; i < 7; i++){
                makeMovingObst(370, 70 + 80 * j, 5, 40, -340 + 50 * i, 0, cycle_time, .5);
            }
            for(int i = 0; i < 7; i++){
                makeMovingObst(370, 70 + 40 + 80 * j, 5, 40, -340 + 50 * i, 0, cycle_time);
            }
        }  //Goes till y = 310
        makeObst(20, 20, 20, 290);
        makeObst(360, 20, 20, 290);

        makeWall(20, 310, 178, 20);
        makeWall(202, 310, 178, 10);
        makeWall(20, 330, 350, 10);
        int time = 950;
        makeMovingFin(385, 360, 5, 50, -370, 0, time, 0, false, true);
        makeMovingObst(380, 340, 5, 90, -370, 0, time, 0, false, true);
        makeMovingFin(385, 360, 5, 50, -370, 0, time, .5, false, true);
        makeMovingObst(380, 340, 5, 90, -370, 0, time, .5, false, true);
        makeWall(00, 00, 20, 450);
        makeWall(380, 0, 20, 450);
        makeWall(0, 430, 400, 20);
        makeWall(360, 330, 10, 90);
        makeWall(340, 350, 10, 80);
        makeWall(320, 330, 10, 90);

        for(int i = 0; i < 3; i++){
            if(i != 0){ // getting rid of the first movingObst
                makeMovingObst(330 - i * 100, 340, 20, 20, 0, 70, 200);
            }
            makeMovingObst(280 - i * 100, 410, 20, 20, 0, -70, 200);
        }

        
    }
    ~Map1_5(){}
};

#endif
