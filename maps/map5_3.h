#ifndef MAP5_3_H
#define MAP5_3_H

#include "../map.h"

class Map5_3 : public Map
{
    Q_OBJECT

public:
    explicit Map5_3(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int w  = 50;
        int h = 700;
        setMapSize(w, h);


        //Set starting data
        starting_coords = QPointF(10, h - 10);
        starting_angle = 0.0;
        loading_text = "5:3\nPump Fake";

        //Add walls/obstacles/finish
        makeWall(0, 20, 20, h - 40);
        // makeWall(0, 20, 20, 10);
        // makeWall(50, 20, 20, 10);
        // makeWall(0, h - 30, 20, 10);
        // makeWall(50, h - 30, 20, 10);
        int port_count = 10;
        for(int i = 0; i < port_count; i++){
            makePortal(20, 20 + ((h - 40) / port_count) * i, 40, 20 + ((h - 40) / port_count) * i, 10, ((h - 40) / port_count / 2) / 3, QColor("purple").lighter(100 + i * 15));
        }

        int num = 10;
        int gap = 5;
        int cycle = 600;
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distr(1, 10 - gap);
        std::random_device rd1;
        std::mt19937 gen1(rd1());
        std::uniform_int_distribution<> distr1(1, 2);
        for(int i = 0; i < num; i++){
            bool r_side = distr1(gen1) == 2;
            int rn = distr(gen) - 1;
            makeMovingObst(20, -15, rn + r_side * 20, 5, 0, h + 20, cycle, 1.0 / num * i, false, true);
            makeMovingObst(20 + rn + r_side * 20 + gap, -15, 30 - rn - r_side * 20 - gap, 5, 0, h + 20, cycle, 1.0 / num * i, false, true);
        }
        makeWall(-10, -30, w + 20, 10);
        // makeWall(-10, 0, 20, 20);
        makeWall(-10, h, w + 20, 10);
        makeWall(-10, -30, 10, h + 40);
        makeWall(w, -20, 10, h + 30);
        makeWall(-10, -20, 30, 20);
        makeFin(0, 0, 10, 20);
    }
    ~Map5_3(){}
};

#endif
