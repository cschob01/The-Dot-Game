#ifndef MAP1_2_H
#define MAP1_2_H

#include "../map.h"

class Map1_2 : public Map
{
    Q_OBJECT

public:
    explicit Map1_2(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(200, 200);

        //Set starting data
        starting_coords = QPointF(100.0, 30.0);
        starting_angle = 90.0;
        loading_text = "1:2\nConflict";

        //Add walls/obstacles/finish
        makeWall(10, 10, 180, 10);
        makeWall(10, 10, 10, 180);
        makeWall(180, 10, 10, 180);
        makeWall(10, 180, 180, 10);

        for(int i = 0; i < 5; i++){
            makeObst(27 + 5 * ((5 * i) % 3), 65 + 20 * i, 10, 10);
            makeObst(84 + 5 * ((5 * i) % 3), 62 + 20 * i, 10, 10);
            makeObst(109 + 5 * ((5 * i) % 3), 57 + 20 * i, 10, 10);
            makeObst(44 + 5 * ((5 * i) % 3), 63 + 20 * i, 10, 10);
            makeObst(67 + 5 * ((5 * i) % 3), 68 + 20 * i, 10, 10);
            makeObst(127 + 5 * ((5 * i) % 3), 51 + 20 * i, 10, 10);
            makeObst(152 + 5 * ((5 * i) % 3), 60 + 20 * i, 10, 10);
        }

        makeObst(20, 20, 5, 160);
        makeObst(175, 20, 5, 160);
        makeObst(25, 165, 73, 5);
        makeObst(102, 165, 73, 5);

        makeFin(25, 170, 150, 10);

    }
    ~Map1_2(){}
};

#endif
