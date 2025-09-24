#ifndef MAP3_2_H
#define MAP3_2_H

#include "../map.h"

class Map3_2 : public Map
{
    Q_OBJECT

public:
    explicit Map3_2(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(300, 100, true);

        //Set starting data
        starting_coords = QPointF(10.0, 50.0);
        starting_angle = 0.0;
        loading_text = "3:2\nThe Door";

        //Add walls/obstacles/finish
        for(int i = 0; i < 5; i++){
            makeBeamObst(50 + i * 5, 0, 90, 0);
            makeBeamObst(100 + i * 5, 99, 270, 0);
        }
        makeMovingObst(15, 47, 10, 5, 100, 0, 700, 0);

        double arctan = 16.6992442;
        makeMovingBeamObst(155, 99, 270 - arctan, 0, 130, 0, 200);
        makeMovingBeamObst(125, 0, 90 - arctan, 0, 130, 0, 200);
        makeMovingBeamObst(125 + 130, 99, 270 + arctan, 0, -130, 0, 200);
        makeMovingBeamObst(155 + 130, 0, 90 + arctan, 0, -130, 0, 200);

        int num = 3;
        for(int i = 0; i < num; i++){
            makeMovingObst(130, 40, 14, 5, 150, 0, 1200, (1.0/num) * i, false, true);
            makeMovingObst(130, 55, 14, 5, 150, 0, 1200, (1.0/num) * i, false, true);
        }

        makeBeamObst(289, 10, 180, 0);
        makeBeamObst(289, 90, 180, 0);

        makeFin(295, 0, 5, 100);

    }
    ~Map3_2(){}
};

#endif
