#include "borderColorPicker.h"

borderColorPicker::borderColorPicker(unsigned int borderSize, HSLAPixel fillColor, PNG &img, double tolerance)
{
    /* your code here */
    this->borderSize = borderSize;
    this->fillColor = fillColor;
    this->img = img;
    this->tolerance = tolerance;

}

HSLAPixel borderColorPicker::operator()(point p)
{
    
    // cout <<"hey10"<<endl;
    //|| ((int)p.y - (int)borderSize<=0 || (int)p.y + (int)borderSize >= (int)img.height()
    if ((int)p.x - (int)borderSize < 0 || (int)p.x + (int)borderSize >= (int)img.width()) {
        return fillColor;
    }
    // cout <<"hey11111"<<endl;
    if ((int)p.y - (int)borderSize<0 || (int)p.y + (int)borderSize >= (int)img.height()){
        return fillColor;
    }

    for (int x= (int)p.x - (int)borderSize; x <= (int)p.x + (int)borderSize; x++){
        for (int y = (int)p.y - (int)borderSize; y <= (int)p.y + (int)borderSize; y++){

                if ((x-(int)p.x)*(x-(int)p.x)+ (y-(int)p.y)*(y-(int)p.y) <= (int)borderSize*(int)borderSize) {
                    if ((img.getPixel(x,y)->dist(p.c.color) > tolerance)){
                    return fillColor;
                    }
                }
            }

        }
    // return *img.getPixel(p.x,p.y);
    return *img.getPixel(p.x,p.y);
}