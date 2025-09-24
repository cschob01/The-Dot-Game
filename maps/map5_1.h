#ifndef MAP5_1_H
#define MAP5_1_H

#include "../map.h"

class Map5_1 : public Map
{
    Q_OBJECT

public:
    explicit Map5_1(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(280, 200);

        //Set starting data
        starting_coords = QPointF(45.0, 45.0);
        starting_angle = 0.0;
        loading_text = "5:1\nWraps";

        //Add walls/obstacles/finish

        int w;
        int h;
        int start_w;
        int start_h;

        //Enclosure 1
        w = 120;
        h = 90;
        start_w = 0;
        start_h = 0;
        makeWall(-10 + start_w, -10 + start_h, w + 20, 10);
        makeWall(-10 + start_w, -10 + start_h, 10, h + 20);
        makeWall(-10 + start_w, h  + start_h, w + 20, 10);
        makeWall(w + start_w, -10  + start_h, 10, h + 20);
        makeObst(start_w + 20, start_h + 10, w - 40, 10);
        makeObst(start_w + 20, start_h + h - 20, w - 40, 10);
        
        //Enclosure 2
        w = 200;
        h = 100;
        start_w = 0;
        start_h = 100;
        makeWall(-10 + start_w, -10 + start_h, w + 20, 10);
        makeWall(-10 + start_w, -10 + start_h, 10, h + 20);
        makeWall(-10 + start_w, h  + start_h, w + 20, 10);
        makeWall(w + start_w, -10  + start_h, 10, h + 20);
        makeMovingObst(start_w + 60, start_h + 10, 20, 20, 0, h - 20 - 20, 200);
        makePortal(start_w + 127, start_h + 30, start_w + 140, start_h + 30, 3, h - 60, QColor("teal"));
        makeWall(start_w + 130, start_h + 20, 10, h - 40);

        //Connect E1 to E2
        makePortal(90, 40, 20, 100 + 45, 10, 10, QColor("purple"));

        //Enclosure 3
        w = 150;
        h = 90;
        start_w = 130;
        start_h = 0;
        makeWall(start_w + 120, 0, 30, 40);
        makeWall(start_w + 120, 50, 30, 40);
        makeWall(-10 + start_w, -10 + start_h, w + 20, 10);
        makeWall(-10 + start_w, -10 + start_h, 10, h + 20);
        makeWall(-10 + start_w, h  + start_h, w + 20, 10);
        makeWall(w + start_w, -10  + start_h, 10, h + 20);
        makeWall(start_w, start_h + 0, 30, 40);
        makeWall(start_w, start_h + 50, 30, 40);
        makeObst(start_w + 30 + 40, start_h + 30 + 2, 6, 10);
        makeObst(start_w + 30 + 40, start_h + 48, 6, 10);
        makePortal(start_w + 30 + 20, start_h + 20, start_w + 30 + 20, start_h + 60, 50, 10, QColor("magenta"));

        //Connect E2 to E3
        makePortal(0 + 170, 100 + 45, 130, 40, 10, 10, QColor("white"));

        //Enclosure 4
        w = 70;
        h = 100;
        start_w = 210;
        start_h = 100;
        makeWall(-10 + start_w, -10 + start_h, w + 20, 10);
        makeWall(-10 + start_w, -10 + start_h, 10, h + 20);
        makeWall(-10 + start_w, h  + start_h, w + 20, 10);
        makeWall(w + start_w, -10  + start_h, 10, h + 20);
        makeBeamObst(start_w + w / 2, start_h + h / 2, 0, 1.5);
        makeFin(start_w + w - 20, start_h + 45, 10, 10);

        //Connect E3 to E4
        makePortal(130 + 120 + 20, 40, 210 + 10, 100 + 45, 10, 10, QColor("brown"));
        
    }
    ~Map5_1(){}
};

#endif
