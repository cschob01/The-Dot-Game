#ifndef MAP6_1_H
#define MAP6_1_H

#include "../map.h"

class Map6_1 : public Map
{
    Q_OBJECT

public:
    explicit Map6_1(QWidget *parent = nullptr)
    : Map(parent)
    {
        int h = 125;
        int w = 60;
        //Set map size <- Necessary boilerplate
        setMapSize(w, h);
        makeWall(-25, -10, w + 35, 10);
        makeWall(-25, -10, 10, h + 20);
        makeWall(-25, h, w + 35, 10);
        makeWall(w, -10, 10, h + 20);

        //Set starting data
        starting_coords = QPointF(20.0, h / 3);
        starting_angle = 90.0;
        loading_text = "6:1\nEscape Your Mind";

        //Add walls/obstacles/finish
        makeWall(-2, 5, 2, h - 10);
        makeWall(40, 5, 2, h - 10);
        makeFin(w - 10, 0, 10, h);
        makePortal(0, 7, 0, h - 8, 40, 1, QColor("Blue"));
        makeInvisibleObst(15, h / 2, 10, 10);

        // forced_settings.height = 999;
        forced_settings.map = false;
    }
    ~Map6_1(){}
};

#endif
