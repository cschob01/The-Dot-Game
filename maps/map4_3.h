#ifndef MAP4_3_H
#define MAP4_3_H

#include "../map.h"

class Map4_3 : public Map
{
    Q_OBJECT

public:
    explicit Map4_3(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int h = 100;
        int w = 800;
        setMapSize(w, h, true);

        //Set starting data
        // starting_coords = QPointF(w - 100, 90);
        starting_coords = QPointF(100, 50);
        starting_angle = 0.0;
        loading_text = "4:3\nThe Needle";

        //Add walls/obstacles/finish
        int gap = 70;
        makeWall(w - 20, h - 30, 20, 10);
        makeWall(w - 40 - gap, h - 30, 20, 10);
        makeWall(w - 50 - gap, h - 50, 10, 30);

        makeObst(w - 40 - gap, 0, 110, 10);
        int lasers  = 5;
        for(int i = 0; i < lasers; i++){
            makeBeamObst(w - 60 - gap / 2 + 20 * i, h - 90, 90, 0);
        }
        makeBeamObst(w - 38 - gap, 55, 0, 0);
        int gap_v = 5;
        makeWall(w - 50 - gap, 0, 10, 50 - gap_v);
        makeWall(w - 55 - gap, 50 - gap_v - 4, 10, 4);
        makeWall(w - 55 - gap, 50, 10, 4);

        //Container
        int loops = 5;
        int loop_h = 100;
        int loop_w = 95;
        int start_x = 0;
        bool cycle = false;
        for(int i = 0; i < loops; i++){

            if(cycle){
                makeWall(start_x - 10, 90 - ((80 - loop_h) / 2), loop_w * 2 + 10, 10);
            }
            else{
                makeWall(start_x - 10, (80 - loop_h) / 2, loop_w * 2 + 10, 10);
            }
            start_x += loop_w;
            loop_h -= 10;
            cycle = !cycle;
            makeWall(start_x - 10, (80 - loop_h) / 2 + 10, 10, loop_h);

        }
        //Ends at x = 425
        int shift_x = 50;
        makeWall(415 + shift_x, 75, 10, 10);
        makeWall(415 + shift_x, 50, 30 + loop_w, 10);
        makeWall(425 + loop_w + shift_x, 40 - gap_v, 30, 10);
        makeWall(425 + loop_w + shift_x, 10, 10, 30);

        makeFollowingObst(0, h - 50 - gap_v, 80, gap_v - 1, .023);

        makeFin(w - 10, h - 20, 10, 10);
        makeWall(w - 10, h - 10, 10, 10);
    }
    ~Map4_3(){}
};

#endif
