#include "fadeColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    /* your code here */
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    /* your code here */
    HSLAPixel ret;
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;

    int x = p.x - p.c.x;
    int y = p.y - p.c.y;
    int dist = pow(x,2) + pow(y,2);
    dist = sqrt(dist);
    ret.l = p.c.color.l * pow ( fadeFactor, dist);
    
    return ret;
}
