#ifndef MAP1_3_H
#define MAP1_3_H

#include "../map.h"

class Map1_3 : public Map
{
    Q_OBJECT

public:
    explicit Map1_3(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(300, 100, true);

        //Set starting data
        starting_coords = QPointF(25, 50);
        starting_angle = 0;
        loading_text = "1:3\nMap Time";

        //Add walls/obstacles/finish
        makeWall(0, 20, 65 + 20, 25);
        makeWall(20 + 65 + 130, 20, 65 + 20, 25);
        makeWall(0, 55, 65 + 20, 25);
        makeWall(20 + 65 + 130, 55, 65 + 20, 25);

        makeWall(20 + 65 + 10, 40, 110, 5);
        makeWall(20 + 65 + 10, 55, 110, 5);

        makeMovingObst(85, 20, 130, 5, 0, 20 - 5, 215);
        makeMovingObst(85, 80 - 5, 130, 5, 0, - 20 + 5, 215);
        makeMovingObst(46, 45, 130, 10, 260 - 130 - 46, 0, 215); // Middle

        makeFin(270, 45, 10, 10);
    }
    ~Map1_3(){}
};

#endif
