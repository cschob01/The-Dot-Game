#ifndef MAP4_4_H
#define MAP4_4_H

#include "../map.h"

class Map4_4 : public Map
{
    Q_OBJECT

public:
    explicit Map4_4(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int w  = 300;
        int h = 300;
        setMapSize(w + 10, h + 10, true);

        //Set starting data
        starting_coords = QPointF(2, h - 2);
        starting_angle = 315.0;
        loading_text = "4:4\nThey're Coming";

        //Add walls/obstacles/finish
        for(int i = 0; i < h / 20; i++){
            for(int j = 0; j < w / 20; j++){
                makeWall(10 + 20 * i, 10 + 20 * j, 10, 10);
            }
        }
        makeFin(w, 0, 10, 10);
        // makeFollowingInvisibleObst(w - 10, 0, 5, 5, .02);
        // makeFollowingInvisibleObst(w, 11, 5, 5, .02);
        // makeFollowingInvisibleObst(w - 20, 0, 5, 5, .02);
        // makeFollowingInvisibleObst(w, 21, 5, 5, .02);
        double speed = 1.4;
        makeFollowingInvisibleObst(w - 10, 0, 5, 5, .01 * speed);
        makeFollowingInvisibleObst(w, 11, 5, 5, .03 * speed);
        makeFollowingInvisibleObst(w - 10 * 10, 0, 5, 5, .025 * speed);
        makeFollowingInvisibleObst(w, 11 + 10 * 10, 5, 5, .02 * speed);
        makeFollowingInvisibleObst(w - 10 * 20, 0, 5, 5, .027 * speed);
        makeFollowingInvisibleObst(w, 11 + 20 * 10, 5, 5, .013 * speed);

        forced_settings.render = 75;
        
    }
    ~Map4_4(){}
};

#endif
