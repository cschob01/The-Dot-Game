#ifndef MAP1_4_H
#define MAP1_4_H

#include "../map.h"

class Map1_4 : public Map
{
    Q_OBJECT

public:
    explicit Map1_4(QWidget *parent = nullptr)
    : Map(parent)
    {
        //Set map size <- Necessary boilerplate
        setMapSize(150, 350, true);

        //Set starting data
        starting_coords = QPointF(75, 320);
        starting_angle = -90.0;
        loading_text = "1:4\nStep Up";

        //Add walls/obstacles/finish
        makeMovingObst(20, 40, 10, 135, 100, 0, 330);
        makeMovingObst(20, 175, 10, 135, 100, 0, 330, .5);
        makeMovingObst(20, 40, 40, 10, 0, 255, 330, .5);
        makeMovingObst(90, 40, 40, 10, 0, 255, 330, .5);

        makeObst(0, 0, 20, 350);
        makeObst(130, 0, 20, 350);

        makeFin(20, 20, 110, 10);
    }
    ~Map1_4(){}
};

#endif
