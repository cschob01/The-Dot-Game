#ifndef MAP1_1_H
#define MAP1_1_H

#include "../map.h"

class Map1_1 : public Map
{
    Q_OBJECT

public:
    explicit Map1_1(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(200, 100);

        //Set starting data
        starting_coords = QPointF(25.0, 50.0);
        starting_angle = 0.0;
        loading_text = "1:1\nOrientation";

        //Add walls/obstacles/finish
        makeWall(10, 10, 10, 80);
        makeWall(10, 30, 75, 10);
        makeWall(10, 10, 180, 10);
        makeWall(180, 10, 10, 80);
        makeWall(10, 60, 75, 10);
        makeWall(115, 60, 75, 10);
        makeWall(115, 30, 75, 10);
        makeWall(10, 80, 180, 10);

        makeFin(20, 20, 10, 10);
        makeFin(20, 70, 10, 10);
        makeFin(170, 20, 10, 10);
        makeFin(170, 70, 10, 10);
    }
    ~Map1_1(){}
};

#endif
