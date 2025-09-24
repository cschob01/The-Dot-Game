#ifndef MAP2_5_H
#define MAP2_5_H

#include "../map.h"

class Map2_5 : public Map
{
    Q_OBJECT

public:
    explicit Map2_5(QWidget *parent = nullptr)
    : Map(parent)
    {
        int h = 1000;
        int w = 100;
        //Set map size <- Necessary boilerplate
        setMapSize(w, h, true);

        //Set starting data
        starting_coords = QPointF(90.0, 53.0);
        starting_angle = 180.0;
        loading_text = "2:5\nAsteroid Belt";

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 10);

        //Add walls/obstacles/finish
        makeWall(80, 0, 20, 40);
        for(int i = 0; 130 * i < h; i++){
            if(i * 130 + 110 <= h){
                makeWall(0, i * 130, 20, 110);
                makeWall(80, (i + .5) * 130, 20, 110);
            }
        }
        for(int i = 0; i < 30; i++){
            int obst_height = 8;
            int j = 29 - i;
            makeMovingObst(20 + 2 * i, 0, 2, obst_height, 0, 1000 - obst_height, 400, .01 * dist(gen));
            makeMovingObst(20 + 2 * j, 0, 2, obst_height, 0, 1000 - obst_height, 400, .5 + .01 * dist(gen));
        }
        makeFin(0, 890, 10, 110);
    }
    ~Map2_5(){}
};

#endif
