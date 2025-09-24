#ifndef MAP2_3_H
#define MAP2_3_H

#include "../map.h"

class Map2_3 : public Map
{
    Q_OBJECT

public:
    explicit Map2_3(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        int width = 400;
        int height = 400;
        setMapSize(width, height, false);

        //Set starting data
        starting_coords = QPointF(10.0, 200.0);
        starting_angle = 45.0;
        loading_text = "2:3\nBlind Spots";

        //border
        makeObst(-10, -10, width + 20, 10);
        makeObst(-10, -10, 10, height + 20);
        makeObst(width, -10, 10, height + 20);
        makeObst(-10, height, width + 20, 10);

        //Gap
        makeObst(0, 170 + 10, 190, 10);
        makeObst(200, 170 + 10, 200, 10);
        makeObst(0, 170, 400, 10);

        for(int i = 0; i < 10; i++){
            makeMovingObst(190, 400, 10, 10, 0, -500, 1000, i * .1, false, true);
        }

        //1
        makeObst(20, 210, 60, 20);
        makeObst(0, 240, 40, 20);
        makeObst(50, 230, 10, 50); //
        makeObst(90, 200, 20, 70); //
        makeObst(90, 200, 40, 20);
        makeObst(70, 240, 10, 50);
        makeObst(30, 290, 100, 10);
        makeObst(10, 240, 10, 50);

        makeObst(0, 310, 120, 10);
        makeObst(130, 310, 30 + 30, 10);
        makeObst(150, 180, 10, 140);

        makeObst(120, 230, 30, 50);

        //2 <- Enterance at 120, 320 to 130, 320
        makeObst(100, 330, 20, 10);
        makeObst(80, 350, 100, 10);
        makeObst(80, 330, 10, 60);
        makeObst(180, 310, 10, 80);
        makeObst(130, 330, 40, 10);
        makeObst(130, 320, 10, 10);

        makeObst(10, 330, 20, 10);
        makeObst(40, 330, 40, 10);
        makeObst(10, 330, 10, 60);
        makeObst(10, 380, 40, 10);
        makeObst(40, 380, 10, 20);

        makeObst(30, 350, 40, 20);
        makeObst(100, 370, 90, 20);

        //3 <- Enterance at 190, 390 to 190, 400
        makeObst(200, 200, 10, 200);
        makeObst(220, 180, 10, 220);
        makeFin(210, 350, 10, 50);

        for(int i = 0; i < 4; i++){
            makeObst(170, 200 + 30 * i, 20, 20);
        }

        setFadeTimer(101);

        forced_settings.map = false;
        
    }
    ~Map2_3(){}
};

#endif
