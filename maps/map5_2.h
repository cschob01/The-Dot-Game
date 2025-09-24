#ifndef MAP5_2_H
#define MAP5_2_H

#include "../map.h"

class Map5_2 : public Map
{
    Q_OBJECT

public:
    explicit Map5_2(QWidget *parent = nullptr)
    : Map(parent)
    {
       //Set map size <- Necessary boilerplate
       int w  = 300;
    //    int h = 800;
       int h = 950;
       int size = 40;
       int arc  = 400;
       int drop = 170;
       int shift = 150;
       int ps = 430;
       setMapSize(w, h);

       //Set starting data
       starting_coords = QPointF(5.0, ps - 17);
       starting_angle = 0.0;
       loading_text = "5:2\nHoops";

       //Add walls/obstacles/finish
       makeWall(-10, -10, 10, h + 20);
       makeWall(-10, -10, w + 20, 10);
       makeWall(-10 - size - 20 + shift, drop - 10, size + 20, 10);
       makeWall(-10 - size - 20 + shift, size + 20 + drop, size + 20, 10);
       makeWall(-10 - size - 20 + shift, -10 + drop, 10, size + 40);

       int down = 170;
       makeWall(w, -10, 10, ((h * 2) / 3) + 20 + down);
       makeWall(-10, h, size + 40, 10);
       makeFin(0, h - 10, size + 20, 10);
       makeWall(size + 20, ((h * 2) / 3) + down, 10, (h / 3) + 10 - down);
       makeWall(size + 20, ((h * 2) / 3) + down, w - size - 10, 10);

       int count = 5;
       for(int i = 0; i < count + 2; i++){
           makeWall(w - 20 - size, arc + ((200) / count) * i, 10, (200) / count / 2);
       }
       // makeWall(w - 20 - size, arc, 10, ((h * 2) / 3) - arc - 10 - size);
       makeBeamObst(w - 21 - size, arc, 180, 0);
       makeBeamObst(1, arc, 0, 0);
       makeFollowingObst(w - size - 5, arc + 30, size, size, .04);

       makePortal(20, ps - 21, w - 20 - size - 30, ps - 21, 10, 10, QColor("purple"));
       makePortal(w - 20 - size - 20, ps + 130, w - 20 - size - 20, ps - 10, 10, 10, QColor("teal"));

    }
    ~Map5_2(){}
};

#endif
