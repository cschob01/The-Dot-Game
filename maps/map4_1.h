#ifndef MAP4_1_H
#define MAP4_1_H

#include "../map.h"

class Map4_1 : public Map
{
    Q_OBJECT

public:
    explicit Map4_1(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int h = 300;
        int w = 100;
        setMapSize(100, 300, true);

        //Set starting data
        starting_coords = QPointF(50.0, 10.0);
        starting_angle = 90.0;
        loading_text = "4:1\nWhat's New";

        //Add walls/obstacles/finish
        for(int i = 0; i < 10; i++){
            makeWall(20, 30 * i, 5, 20);
            makeWall(30, 30 * i, 5, 20);
            makeWall(65, 30 * i, 5, 20);
            makeWall(75, 30 * i, 5, 20);
        }
        makeFollowingObst(25, 65, 5, 50, .1);
        makeFollowingObst(70, 65, 5, 50, .1);
        
        makeFin(0, 0, 10, h);
        makeFin(w - 10, 0, 10, h);
    }
    ~Map4_1(){}
};

#endif
