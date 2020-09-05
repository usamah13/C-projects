// File:        gridlist.cpp
// Date:        2020-01-18 00:11
// Description: Contains partial implementation of GridList class
//              CPSC 221 2019W2 PA1
//              Function bodies to be completed by yourselves
//
// ADD YOUR FUNCTION IMPLEMENTATIONS IN THIS FILE
//

#include "gridlist.h"
#include "gridlist_given.cpp"

// Creates a PNG of appropriate pixel dimensions according to the GridList's structure
//   and colours each pixel according the each GridNode's Block data.
// The fully coloured PNG is returned.
PNG GridList::Render() const
{
  // PNG image;
  // // enter your code here


  // image = PNG(this->dimx,this->dimy);
  // GridNode* curr_node = this->northwest;

  // Block b = curr_node->data;
  
  // for (int i = 0; i < this->dimy; i++) {
  //   for (int k = 0; k < this->dimx; k++) {
  //       b.Render(image, i, k);
  //       curr_node = curr_node->next;
  //       }
  //   }
  // return image;

  GridNode *temp = northwest;
  int size = temp->data.Dimension();
  PNG image(dimx*size, dimy*size);
  int i = 0;
  while(i < (dimx * dimy)) {
    for(int j = 0; j < dimy; j++) {
      for(int k = 0; k < dimx; k++) {
        temp->data.Render(image, j*size, k*size);
        temp = temp->next;
        i++;
      }
    }
  }
  return image;
}

// Allocates a new GridNode containing bdata and
//   attaches it to end of this list.
// Be careful of the special case of inserting into an empty list.
void GridList::InsertBack(const Block& bdata)
{
  // enter your code here
  if (this->IsEmpty()){
    GridNode* new_node = new GridNode(bdata);
    new_node->next = NULL;
    new_node->prev = NULL;
    this->northwest = new_node;
    this->southeast = new_node;
    // new_node = NULL;
    // delete new_node;

  }else{
  GridNode* temp_node = this->southeast;
  GridNode* new_node = new GridNode(bdata);
  temp_node->next = new_node;
  new_node->next = NULL;
  new_node->prev = temp_node;
  this->southeast = new_node;
  // temp_node = NULL;
  // new_node = NULL;
  // delete temp_node;
  // delete new_node;
  
  }
  
}

// if this list has an odd number of column blocks, then the right side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two column blocks
//       inner list must have at least one column block
//       inner list must have the same vertical resolution, vertical block dimension, and block size
// POST: this list has nodes of the entire inner list in between the left and right halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_H(GridList& inner)
{
 if (this->dimy == inner.dimy) {
   // enter your code here
   int starting_column = (this->dimx/2)-1;
   //int end_column = (this->dimx/2)+1; 
   int counter = 0;
   this->dimx = this->dimx + inner.dimx;
   GridNode* curr = this->northwest;
   GridNode* temp = inner.northwest;
   GridNode* temp2;
   GridNode* curr2;

   for(int row = 0; row < this->dimy; row++) {
     for(int column = 0; column < this->dimx; column++) {
        if (column >= starting_column && counter<inner.dimx ){
          temp2 = temp->next;
          curr2 = curr->next;
          temp->next = curr->next;
          curr->next = temp;
          temp->prev = curr;
          curr2->prev = temp;
          temp2->prev = NULL;
          counter++; 
        }
       temp = temp2;
       curr = curr->next;
      }
      counter = 0;

    }
     dimx = dimx + inner.dimx;
    inner.northwest = NULL;
    inner.southeast = NULL;
    inner.dimx = 0;
    inner.dimy = 0;
    //this->dimx += inner.dimx;
   // inner.~GridList;
  }
}
// if (inner.dimy != this->dimy) {
//     return;
//   }

//   if (inner.northwest->data.Dimension() != this->northwest->data.Dimension()) {
//     return;
//   }

// int t;
//   if (dimx % 2 == 0) {
//     t = dimx/2 - 1;
//   } else {
//     t = (dimx -1)/2 - 1;
//   }

//   GridNode *main = northwest;
//   GridNode *other = inner.northwest;
//   GridNode *temp;

//   for (int i = 0; i < t; i++) {
//     main = main->next;
//   }

//   temp = main->next;
//   GridNode *temp2;

//  while(main != NULL) {

//   main->next = other;
//   other->prev = main;
//   main = temp;

//   for (int k = 0; k < inner.dimx - 1; k++) {
//     other = other->next;
//   }

//   temp2 = other->next;
//   other->next = main;
//   main->prev = other;
//   other = temp2;

//   for (int j = 0; j < dimx -1; j ++) {
//     main = main->next;
//     if (main == NULL) {
//       break;
//     }
//     temp = main->next;
//   }
// }
// dimx = dimx + inner.dimx;
// inner.northwest = NULL;
// inner.southeast = NULL;
// inner.dimx = 0;
// inner.dimy = 0;

// }

// inner list must have the same horizontal resolution, horizontal block dimension, and block size
// if this list has an odd number of row blocks, then the bottom side will have more blocks
// PRE:  this list and inner are not the same physical list
//       this list must have at least two row blocks
//       inner list must have at least one row block
//       inner list must have same horizontal resolution, horizontal block dimension, and block size
// POST: this list has nodes of the entire inner list in between the upper and lower halves of this list
//         and inner list becomes empty
//       otherwise both lists are not modified
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::Sandwich_V(GridList& inner)
{
  // enter your code here
}


// PRE:  this list and otherlist have the same pixel dimensions, block dimensions, and block size
// POST: this list and otherlist are checkered with each other's nodes
//       each list's dimensions remain the same
// THIS MUST BE ACHIEVED USING POINTER REASSIGNMENTS.
// DO NOT ALLOCATE OR DELETE ANY NODES IN THIS FUNCTION.
void GridList::CheckerSwap(GridList& otherlist)
{
  // enter your code here
}

// POST: this list has the negative effect applied selectively to GridNodes to form
//         a checkerboard pattern.
//       The northwest block is normal (does not have the negative effect applied).
// Ensure that the checkering looks correct for both odd and even horizontal block dimensions
void GridList::CheckerN()
{
  // enter your code here
   if (dimx % 2 != 0) {
    GridNode *temp = northwest;
    int i = 0;
    while (temp != NULL) {
      if (i % 2 != 0) {
        temp->data.Negative();
      }
      temp = temp->next;
      i++;
    }
    return;
  }

  if (dimx % 2 == 0) {
    GridNode *temp = northwest;
    int k = 0;
    int i = 0;
    while (temp != NULL) {
      i = 0;
      while (i < dimx) {
        if (k % 2 == 0) {
          if(i % 2 != 0) {
            temp->data.Negative();
          }
          temp = temp->next;
          i++;
        } 
        if (k % 2 != 0) {
          if (i % 2 == 0 ) {
            temp->data.Negative();
          }
          temp = temp->next;
          i++;
        }
      }
      k++;
    }
    return;
  }
  
}

// Deallocates any dynamic memory associated with this list
//   and re-initializes this list to an empty state
void GridList::Clear()
{
  // enter your code here

}

// Allocates new nodes into this list as copies of all nodes from otherlist
void GridList::Copy(const GridList& otherlist)
{
  // enter your code here
}

// IMPLEMENT ANY PRIVATE FUNCTIONS YOU HAVE ADDED BELOW
//
//