/**
 * @file filler.cpp
 * Implementation of functions in the filler namespace.
 *
 */
#include "filler.h"

/**
 * Performs a multi-point flood fill using breadth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillBFS(FillerConfig &config)
{
  return fill<Queue>(config);
}

/**
 * Performs a multi-point flood fill using depth first search.
 *
 * @param config      FillerConfig struct to setup the fill
 * @return animation  object illustrating progression of flood fill algorithm
 */
animation filler::fillDFS(FillerConfig &config)
{
  return fill<Stack>(config);
}

/**
 * Run a multi-point flood fill on an image
 *
 * @param  config     FillerConfig struct with data for flood fill of image
 * @return animation  object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::fill(FillerConfig &config)
{
    /**
     * @todo You need to implement this function!
     *
     * This is the basic description of a flood-fill algorithm: Every fill
     * algorithm requires an ordering structure, which is passed to this
     * function via its template parameter. For a breadth-first-search
     * fill, that structure is a Queue, for a depth-first-search, that
     * structure is a Stack. To begin the algorithm, you simply place the
     * given point in the ordering structure, marking it processed
     * (the way you mark it is a design decision you'll make yourself).
     * We have a choice to either change the color, if appropriate, when we
     * add the point to the OS, or when we take it off. In our test cases,
     * we have assumed that you will change the color when a point is added
     * to the structure.
     * Until the structure is empty, you do the following:
     *
     * 1.     Remove a point from the ordering structure, and then...
     *
     *        1.    add its unprocessed neighbors whose color values are
     *              within (or equal to) tolerance distance from the center,
     *              to the ordering structure, and
     *              mark them as processed.
     *        2.    if it is an appropriate frame, send the current PNG to the
     *              animation (as described below).
     *
     * 2.     When implementing your breadth-first-search and
     *        depth-first-search fills, you will need to explore neighboring
     *        pixels in some order.
     *
     *        While the order in which you examine neighbors does not matter
     *        for a proper fill, you must use the same order as we do for
     *        your animations to come out like ours! The order you should put
     *        neighboring pixels **ONTO** the queue or stack is as follows:
     *        ** LEFT(-x), DOWN(+y), RIGHT(+x), UP(-y). IMPORTANT NOTE: *UP*
     *        here means towards the top of the image, so since an image has
     *        smaller y coordinates at the top, this is in the *negative y*
     *        direction. Similarly, *DOWN* means in the *positive y*
     *        direction.** To reiterate, when you are exploring (filling out)
     *        from a given pixel, you must first try to fill the pixel to
     *        it's LEFT, then the one DOWN from it, then to the RIGHT and
     *        finally UP. If you do them in a different order, your fill may
     *        still work correctly, but your animations will be different
     *        from the grading scripts!
     *
     *        Because we are doing a multi-point flood fill you will repeat the flood
     *        fill from several locations stored in the `centers` variable of FillerConfig
     *        struct. Initial fill points should be visited in the order they stored in the
     *        `centers` vector. If a pixel lies in the fill region of multiple start points,
     *        it should only be updated by the first fill. To repeat, pixels should only
     *        be modified the first time they are visited by the filler algorithm.
     *
     * 3.     For every k pixels filled, **starting at the kth pixel**, you
     *        must add a frame to the animation, where k = frameFreq.
     *
     *        For example, if frameFreq is 4, then after the 4th pixel has
     *        been filled you should add a frame to the animation, then again
     *        after the 8th pixel, etc.  You must only add frames for the
     *        number of pixels that have been filled, not the number that
     *        have been checked. So if frameFreq is set to 1, a pixel should
     *        be filled every frame.
     *
     * 4.     Finally, as you leave the function, send one last frame to the
     *        animation. This frame will be the final result of the fill, and
     *        it will be the one we test against.
     *
     */
  int k = 0;
  animation anim;
  anim.addFrame(config.img);
  
  OrderingStructure<point> os;
  //set<point> pointsvisited;
  vector<vector<bool>> pointsvisited;
  for (int x = 0; x <= (int)config.img.width(); x++) {
      vector<bool> intial;
    for (int y = 0; y <= (int)config.img.height(); y++){
      intial.push_back(false);
    }
    pointsvisited.push_back(intial);
  }
  // cout <<pointsvisited.size()<<endl;
  // cout <<pointsvisited[1].size()<<endl;
  //we assume centers and pickers are same size
  for (int j = 0; j < (int)config.centers.size(); j++) {
    center ctr = config.centers[j];
    colorPicker* picker = config.pickers[j];
    point center_point(ctr);
    os.add(center_point);
    HSLAPixel cenPixold = *(config.img.getPixel(center_point.x,center_point.y));

    while (!os.isEmpty()) {
    // cout <<"hey9999"<<endl;
    point p = os.remove();
    vector<point> neighbour;
    point LEFT(p.x-1, p.y, p.c);
    point DOWN(p.x, p.y+1, p.c);
    point RIGHT(p.x+1, p.y, p.c);
    point UP(p.x, p.y-1, p.c);
    neighbour.push_back(LEFT);
    neighbour.push_back(DOWN);
    neighbour.push_back(RIGHT);
    neighbour.push_back(UP);
    // cout <<config.img.width()<<endl;
    // cout <<config.img.height()<<endl;
    // cout <<config.tolerance<<endl;


    // cout <<"hey"<<endl;
    // cout <<neighbour.size()<<endl;

    for (int i = 0; i< (int)neighbour.size(); i++){
      //cout <<"hey300"<<endl;
      point neighbouring = neighbour[i];
        if ((neighbouring.x >= 0 && neighbouring.x < config.img.width()) && (neighbouring.y >= 0 && neighbouring.y < config.img.height())){
          // cout <<neighbouring.x<<endl;
          // cout <<neighbouring.y<<endl;
          // cout <<"hey1"<<endl;
        if ((pointsvisited[neighbouring.x][neighbouring.y]) == false){
          // cout <<"hey2"<<endl;
          //  cout <<"hey5"<<endl;
          //  cout <<(config.img.getPixel(neighbouring.x,neighbouring.y)->dist(cenPix))<<endl;
          if ((config.img.getPixel(neighbouring.x,neighbouring.y)->dist(cenPixold)) <= config.tolerance){
            //cout <<"hey3"<<endl;
              *config.img.getPixel(neighbouring.x, neighbouring.y) = picker->operator()(neighbouring);
              os.add(neighbouring);
              // pointsvisited.insert(neighbouring);
              pointsvisited[neighbouring.x][neighbouring.y] = true;
              k++;
            if (k % config.frameFreq == 0){
                  //cout <<"hey10"<<endl;
              anim.addFrame(config.img);
            }
          }
        }
       }
        //cout <<"hey9"<<endl;
      }
      if ((pointsvisited[center_point.x][center_point.y]) == false) {
    
      //cout <<(config.img.getPixel(neighbouring.x,neighbouring.y)->dist(cenPix))<<endl;
    
        *config.img.getPixel(center_point.x, center_point.y) = picker->operator()(center_point);
        //cout <<"hey111"<<endl;
        pointsvisited[center_point.x][center_point.y] = true;
        //cout <<"hey000"<<endl;
        k++;
  
    }
    // delete(LEFT);
    // delete(DOWN);
    // delete(RIGHT);
    // delete(UP);
    // delete(neighbour);
    }
    // //then to use the picker in your loop you can do something like this
    // //here we just check the colour the point x,y should be in the PNG object image based on the picker and update it accordingly
    // point some_point(center.x, center.y, center);
    // *image.getPixel(x, y) = picker->operator()(some_point);
    //}
  
  }
  //delete(pointsvisited);
  anim.addFrame(config.img);
  return anim;
  
}
