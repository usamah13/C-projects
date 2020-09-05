#include "block.h"

using namespace cs221util;
    void Block::Build(PNG& im, int upper, int left, int dimension) {
        for(int i = 0 ; i < dimension; i++) {
            vector<HSLAPixel> temp;
            for (int k = 0; k < dimension; k ++) {
                temp.push_back(*im.getPixel(left + k, upper + i));
            }
            data.push_back(temp);
        } 
    }
     

    void Block::Render(PNG& im, int upper, int left) const {
         HSLAPixel* p;
          for (int i = 0; i < this->Dimension(); i++) {
            for (int k = 0; k < this->Dimension(); k++) {
                p = im.getPixel(left+k,upper+i);
                p->h = data[i][k].h;
                p->s = data[i][k].s;
                p->l = data[i][k].l;
            }
        }
    }

    void Block::Negative() {
        for (int i = 0; i < this->Dimension(); i++) {
            for (int k = 0; k < this->Dimension(); k++) {
                if ((data[i][k].h + 180) >= 360) {
                    data[i][k].h  = (data[i][k].h + 180) - 360;
                } else {
                     data[i][k].h  = (data[i][k].h + 180);
                }
                data[i][k].l = (1 - data[i][k].l);
            }
        }
    }
    
    int Block::Dimension () const {
        return data.size();
    
    }
