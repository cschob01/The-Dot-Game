#ifndef MAP2_1_H
#define MAP2_1_H

#include "../map.h"

class Map2_1 : public Map
{
    Q_OBJECT

public:
    explicit Map2_1(QWidget *parent = nullptr)
    : Map(parent)
    {

        //Set map size <- Necessary boilerplate
        setMapSize(200, 200);

        //Set starting data
        starting_coords = QPointF(100.0, 30.0);
        starting_angle = 90.0;
        loading_text = "2:1\nA Dark Room";

        //Add walls/obstacles/finish
        makeWall(10, 10, 180, 10);
        makeWall(10, 10, 10, 180);
        makeWall(180, 10, 10, 180);
        makeWall(10, 180, 180, 10);

        for(int i = 0; i < 5; i++){
            makeInvisibleObst(27 + 5 * ((5 * i) % 3), 65 + 20 * i, 10, 10);
            makeInvisibleObst(84 + 5 * ((5 * i) % 3), 62 + 20 * i, 10, 10);
            makeInvisibleObst(109 + 5 * ((5 * i) % 3), 57 + 20 * i, 10, 10);
            makeInvisibleObst(44 + 5 * ((5 * i) % 3), 63 + 20 * i, 10, 10);
            makeInvisibleObst(67 + 5 * ((5 * i) % 3), 68 + 20 * i, 10, 10);
            makeInvisibleObst(127 + 5 * ((5 * i) % 3), 51 + 20 * i, 10, 10);
            makeInvisibleObst(152 + 5 * ((5 * i) % 3), 60 + 20 * i, 10, 10);
        }

        makeInvisibleObst(20, 20, 5, 160);
        makeInvisibleObst(175, 20, 5, 160);
        makeInvisibleObst(25, 165, 73, 5);
        makeInvisibleObst(102, 165, 73, 5);

        makeFin(25, 170, 150, 10);

        forced_settings.render = 32;

    }
    ~Map2_1(){}
};

#endif
