#ifndef MAP4_5_H
#define MAP4_5_H

#include "../map.h"

class Map4_5 : public Map
{
    Q_OBJECT

public:
    explicit Map4_5(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int w = 500;
        int h = 270;
        setMapSize(w, h);
        makeWall(-10, -10, 10, h + 20);
        makeWall(-10, -10, w / 2 + 60 + 70 + 20, 10);
        makeWall(w, h - 120 - 60, 10, 120 + 60);
        makeWall(-10, h, w + 20, 10);

        //Set starting data
        starting_coords = QPointF(w / 2 + 33, h - 70);
        starting_angle = 90.0;
        loading_text = "4:5\nRat Maze";

        //Add walls/obstacles/finish
        int h1 = 20;
        int w1 = 20;
        makeWall(0, h - 60 - h1, 90 + w1, 10);
        makeWall(80 + w1, h - 60 - h1, w / 2 - 80 - w1 - 60, 25);
        makeWall(70 + w1, h - 60 + 25 - h1, w / 2 - 70 - w1, 10);

        makeWall(w / 2 + 50 + 20, h - 50 - h1, 40, 10);
        makeWall(w / 2 + 70, h - 50 - h1, 10, 50 + h1);
        makeFin(0, h - 10, w / 2 + 70, 10);
        makeFollowingObst(w / 2 - 100, h - 23 - h1, 65 + w1, 10, .05);
        //Ends at x = w / 2 + 80
        makeWall(0, h - 120, w / 2 + 20 - 100 + 10 + 100, 40);
        makeWall(w / 2 + 40, h - 90, 40, 10); // lower
        makeWall(w / 2 + 40, h - 120, 40, 10); // upper
        int zone3_h = 100;
        makeWall(w / 2 + 40 + 30, h - 120 - 40, 10, 10 + 40); // Takes upper up 40
        makeWall(w / 2 + 30, h - 120 - 40, 50, 10); // Takes ^ left for zone 3 barrier
        makeWall(w / 2 + 30, h - 120 - 40 - zone3_h, 10, 10 + zone3_h); // Barrier left wall
        makeWall(w / 2 + 60 + 30, h - 120 - 40, 50, 10); // Hook roof
        makeWall(w / 2 + 60 + 70, h - 120 - 50 - zone3_h, 10, 50 + zone3_h); // Right of hook + Extended for zone 3
        makeWall(w / 2 + 100, h - 120, 10, 40); // Right
        makeWall(w / 2 + 100, h - 120 - 10, 10, 10 + 10); // Takes right up 10
        makeWall(w / 2 + 100, h - 120, 40 + 10, 10); //Bottom of hook
        makeFollowingObst(w / 2 + 80, h - 90, 19, 19, .05);
        makeWall(w / 2 + 60 + 70, h - 120 - 60, w - (w / 2 + 60 + 70), 10); // Roof of thunder dome
        makeWall(w / 2 + 60 + 70, h - 120 - 60, 10, 30);

        //zone 3
        for(int j = 0; j < zone3_h / 20; j++){
            for(int i = 0; i < 4; i++){
                makeWall(w / 2 + 60 + 50 - 20 * i, h - 120 - 40 - zone3_h + j * 20, 10, 10);
            }
            makeFollowingObst(w / 2 + 60 + 50 - 30, h - 120 - 40 - zone3_h + 10 + j * 20, 13, 9, .03);
        }

        makeWall(w / 2 + 102, h - 80, 6, 3);
        makeWall(w / 2 + 102, h - 73, 6, 3);
        makeFollowingObst(w / 2 + 80, h - 10, 6, 6, .05);
        makeFollowingObst(w / 2 + 100 + 50, h - 135, 6, 6, .05);
        for(int i = 0; i < 2; i++){
            makeWall(w / 2 + 60 + 70 + 30 - 20 * i, h - 180 + 30 + 70 * i, 5, 5);
            makeWall(w / 2 + 60 + 70 + 70 - 20 * i, h - 180 + 47 + 70 * i, 5, 5);
            makeWall(w / 2 + 60 + 70 + 35 - 20 * i, h - 180 + 79 + 70 * i, 5, 5);
            makeWall(w / 2 + 60 + 70 + 43 - 20 * i, h - 180 + 56 + 70 * i, 5, 5);
            makeWall(w / 2 + 60 + 70 + 100 - 20 * i, h - 180 + 70 + 70 * i, 5, 5);
        }

        //Zone 4
        makeWall(w / 2 + 30 - 30, h - 180 - 40, 30, 10);
        makeFollowingObst(w / 2 + 30 - 90, h - 160 - 40, 80, 80, .00195);
        
    }
    ~Map4_5(){}
};

#endif
