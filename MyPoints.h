//
// Created by wanle on 5/1/2021.
//

#ifndef FINALPROJECT_MYPOINTS_H
#define FINALPROJECT_MYPOINTS_H


class MyPoints {
public:
    MyPoints();
    MyPoints(double x, double y);
    double getX();
    double getY();
    void setPoint(double x, double y);
private:
    double _x;
    double _y;
};


#endif //FINALPROJECT_MYPOINTS_H
