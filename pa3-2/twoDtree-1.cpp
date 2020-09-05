
/**
 *
 * twoDtree (pa3)
 * slight modification of a Kd tree of dimension 2.
 * twoDtree.cpp
 * This file will be used for grading.
 *
 */

#include "twoDtree.h"

// Node constructor, given.
twoDtree::Node::Node(pair<int,int> ul, pair<int,int> lr, RGBAPixel a)
	:upLeft(ul),lowRight(lr),avg(a),left(NULL),right(NULL)
	{}

// twoDtree destructor, given.
twoDtree::~twoDtree(){
	clear();
}

// twoDtree copy constructor, given.
twoDtree::twoDtree(const twoDtree & other) {
	copy(other);
}


// twoDtree assignment operator, given.
twoDtree & twoDtree::operator=(const twoDtree & rhs){
	if (this != &rhs) {
		clear();
		copy(rhs);
	}
	return *this;
}

twoDtree::twoDtree(PNG & imIn){ 
	stats s = stats(imIn);

	width = imIn.width();
	height = imIn.height();

	pair<int, int> ul = make_pair(0,0);
	pair<int, int> lr = make_pair(imIn.width()-1, imIn.height()-1);

	root = buildTree(s,ul,lr,true);

// YOUR CODE HERE

}

twoDtree::Node * twoDtree::buildTree(stats & s, pair<int,int> ul, pair<int,int> lr, bool vert) {
	RGBAPixel avg = s.getAvg(ul, lr);
	Node* node = new Node(ul, lr, avg);

	pair<int,int> LRtemp;
	pair<int,int> ULtemp;
	pair<int,int> LRnew;
	pair<int,int> ULnew;

	// single pixel 
	if (ul == lr) {
		return node;
	}

	// single column -> horizontal splitting
	if (ul.first == lr.first && lr.second > ul.second) {
		long minscore = 0;

		for (int i = ul.second; i < lr.second; i++) {
			LRtemp = make_pair(lr.first, i);
			ULtemp = make_pair(ul.first, 1+i);
			long tempscore = s.getScore(ul, LRtemp) + s.getScore(ULtemp, lr);

			if (tempscore <= minscore || minscore == 0) {
				minscore = tempscore;
				LRnew = LRtemp;
				ULnew = ULtemp;
			} 
		}

		node->left = buildTree(s, ul, LRnew, vert);
		node->right = buildTree(s, ULnew, lr, vert);
		return node;	


	}

	// single row -> vertical splitting
	if (ul.second == lr.second && lr.first > ul.first) {
		long minscore = 0;

		for (int i = ul.first; i < lr.first; i++) {
			LRtemp = make_pair(i,lr.second);
			ULtemp= make_pair(1+i,ul.second);
			long tempscore = s.getScore(ul,LRtemp) + s.getScore(ULtemp,lr);

			if (tempscore <= minscore || minscore == 0) {
				minscore = tempscore;
				LRnew = LRtemp;
				ULnew = ULtemp;
			} 
		}

		node->left = buildTree(s, ul, LRnew, vert);
		node->right = buildTree(s, ULnew, lr, vert);
		return node;
	}



	// Vetical Splitting
	if (vert == true) {
		vert = false;
		long minscore = 0;

		for (int i = ul.first; i < lr.first; i++) {
			LRtemp = make_pair(i,lr.second);
			ULtemp= make_pair(1+i,ul.second);
			long tempscore = s.getScore(ul,LRtemp) + s.getScore(ULtemp,lr);

			if (tempscore <= minscore || minscore == 0) {
				minscore = tempscore;
				LRnew = LRtemp;
				ULnew = ULtemp;
			} 
		}

		node->left = buildTree(s, ul, LRnew, vert);
		node->right = buildTree(s, ULnew, lr, vert);
		return node;
	}

	// Horizontal Splitting
	if (vert == false) {
		vert = true;
		long minscore = 0;

		for (int i = ul.second; i < lr.second; i++) {
			LRtemp = make_pair(lr.first, i);
			ULtemp = make_pair(ul.first, 1+i);
			long tempscore = s.getScore(ul, LRtemp) + s.getScore(ULtemp, lr);

			if (tempscore <= minscore || minscore == 0) {
				minscore = tempscore;
				LRnew = LRtemp;
				ULnew = ULtemp;
			} 
		}

		node->left = buildTree(s, ul, LRnew, vert);
		node->right = buildTree(s, ULnew, lr, vert);
		return node;	

	}

// YOUR CODE HERE!!

}

PNG twoDtree::render(){

// YOUR CODE HERE!!
	PNG img = PNG(width, height);
	setLeafNodes(root, img);
	return img;



}

void twoDtree::setLeafNodes(Node * node, PNG& img) {
	
	if(node->left == NULL && node->right == NULL) {
		for (int i = node->upLeft.first; i < node->lowRight.first + 1; i++) {
			for (int j = node->upLeft.second; j < node->lowRight.second + 1; j++) {
				*(img.getPixel(i,j)) = node->avg;
	
			}
		}
		// *(img.getPixel(node->upLeft.first, node->upLeft.second)) = node->avg;
	}

	if (node->left) {
		setLeafNodes(node->left, img);
	}

	if (node->right) {
		setLeafNodes(node->right,img);
	}

}
int twoDtree::idealPrune(int leaves){
	Node* copy = copyHelper(root);
	int tol = 5000;

	int count = pruneSize(tol);
	while (leaves != count) {
		if (leaves > count) {
			tol = (tol + 2*tol)/2;
		}
		if (leaves < count) {
			tol = (0 + tol)/2;
		}

		root = copyHelper(copy);
		count = pruneSize(tol);
	}

	return tol;

// YOUR CODE HERE!!

}

int twoDtree::pruneSize(int tol){
	prune(tol);
	int count = countLeafNodes(root);
	return count;
    
// YOUR CODE HERE!!

}

int twoDtree::countLeafNodes (Node* node) {
	if (node == NULL) {
		return 0;
	}
	if (node->left == NULL && node->right == NULL) {
		return 1;
	} else {
		return countLeafNodes(node->left) + countLeafNodes(node->right);
	}
}

void twoDtree::prune(int tol){

// YOUR CODE HERE!!
	if (root == NULL) {
		return;
	}
	pruneHelper(root, tol);
}

void twoDtree::pruneHelper(Node * node, int tol) {
	CanBePruned = true;
	canBePruned(node, node, tol);

	if(CanBePruned == true) {
		clearRoot (node->left);
		node->left = NULL;
		clearRoot(node->right);
		node->right = NULL;
	}

	if (node->left) {
		pruneHelper(node->left, tol);
	}

	if (node->right) {
		pruneHelper(node->right, tol);
	}

}

void twoDtree::canBePruned(Node* temp, Node* root, int tol) {

	if (temp == NULL) {
		return;
	}

	if (temp->left == NULL && temp->right == NULL) {
		int r = temp->avg.r - root->avg.r;
		int g = temp->avg.g - root->avg.g;
		int b = temp->avg.b - root->avg.b;

		if(((r*r + g*g + b*b) > tol) && temp != root) {
			CanBePruned = false;
		}
	}
	

	if (temp->left) {
		canBePruned (temp->left, root, tol);
	}

	if (temp->right) {
		canBePruned (temp->right, root, tol);
	}



}


void twoDtree::clear() {
	clearRoot(root);

// YOUR CODE HERE!!

}

void twoDtree::clearRoot(Node* node) {
	if (node != NULL) {
		clearRoot(node->left);
		clearRoot(node->right);
		delete node;
		node = NULL;
	}
}

void twoDtree::copy(const twoDtree & orig){

// YOUR CODE HERE!!
	width = orig.width;
	height = orig.height;
	root = copyHelper(orig.root);

}

twoDtree::Node * twoDtree::copyHelper(Node* node){
	Node* t = NULL;
	if(node != NULL) {
		t = new Node(node->upLeft, node->lowRight, node->avg);
		t->left = copyHelper(node->left);
		t->right = copyHelper(node->right);
	}
	return t;
}



