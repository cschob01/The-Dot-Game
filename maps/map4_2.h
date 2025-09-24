#ifndef MAP4_2_H
#define MAP4_2_H

#include "../map.h"

class Map4_2 : public Map
{
    Q_OBJECT

public:
    explicit Map4_2(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int h = 250;
        int w = 500;
        setMapSize(w, h, true);

        //Set starting data
        starting_coords = QPointF(10.0, h / 2);
        starting_angle = 0.0;
        loading_text = "4:2\nHammer Throw";

        //Add walls/obstacles/finish
        for(int i = 0; i < 1; i++){
            makeWall(0, 10 + i * 20, 30, 10);
            makeFollowingObst(0, 20 * i, 10, 10, .12);

            // makeWall(0, h - 20 - i * 20, 30, 10);
            // makeFollowingObst(0, h - 10 - 20 * i, 10, 10, .09);
        }
        makeFin(w - 10, 0, 10, h);
        forced_settings.render = 150;
    }
    ~Map4_2(){}
};

#endif
