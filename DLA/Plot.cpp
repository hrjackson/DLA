//
//  Plot.cpp
//  DLA
//
//  Created by Henry Jackson on 29/04/2015.
//  Copyright (c) 2015 n/a. All rights reserved.
//

#include "plot.h"

////////////////////////////////////////////////////////////////////////////////
//// Plot private member function definitions //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////
//// Plot member function definitions //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Plot::Plot(int width, int height, int scale)
:width(width), height(height), scale(scale) {
    origin = Point(width/2, (double)height/2);
    
    // Initialise the plot
    image =  Mat::Mat(height, width, CV_8UC3, Scalar(255,255,255));
}

Plot::~Plot(){

}

void Plot::drawLine(cpx point, Scalar colour=Scalar(0,0,0)) {
    Point endPoint = cpxToCV(point);
    line(image,
         currentPosition,
         endPoint,
         colour,
         1,
         CV_AA);
    currentPosition = endPoint;
}

void Plot::drawLine(vector<cpx> points, Scalar colour=Scalar(0,0,0)){
    if (points.size() != 0){
        currentPosition = cpxToCV(points.front());
        for (auto it = ++points.begin(); it != points.end(); ++it) {
            drawLine((*it), colour);
        }
    }
}

void Plot::drawLoop(vector<cpx> points, Scalar colour) {
    drawLine(points, colour);
    // Close the loop:
    drawLine(points.front(), colour);
}

void Plot::drawCircle(cpx centre, double radius, Scalar colour) {
    Point cvCentre = cpxToCV(centre);
    double cvRad = radius*scale;
    circle(image,
           cvCentre,
           cvRad,
           colour,
           1,
           CV_AA);
}

void Plot::output(const char* filename) {
    cv::imwrite(filename, image);
}

void Plot::show(){
    cv::imshow("window", image);
    cv::waitKey();
}

void Plot::clear(){
    image = Scalar(255,255,255);
}

Point Plot::cpxToCV(cpx z) {
    Point result = Point(origin.x + z.real()*scale, origin.y - z.imag()*scale);
    return result;
}

cpx Plot::CVTocpx(Point pt) {
    cpx result = cpx( ( (double)pt.x - (double)origin.x )/scale,
                      ( (double)origin.y - (double)pt.y )/scale );
    return result;
}

Point Plot::getOrigin() {
    return origin;
}

double Plot::minX(){
    return (double)(origin.x - width)/(double)scale;
}

double Plot::maxX(){
    return -minX();
}

double Plot::maxY(){
    return (double)(origin.y)/(double)scale;
}

int Plot::rows(){
    return height;
}

int Plot::cols(){
    return width;
}
