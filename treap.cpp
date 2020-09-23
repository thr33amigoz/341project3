// CMSC 341 - Fall 2019 - Project 3
// File: treap.cpp

using namespace std ;

#include "treap.h"

Treap::Treap() {
  _nptr = nullptr ;
}

Treap::Treap(const Treap& other) {
  //
  // Implement copy constructor
  //
  
  if (other._nptr == nullptr){
    _nptr = nullptr;
  }

  else{

    // creates a deep copy of the "other" node
    _nptr = new TreapNode((other._nptr)->_data, (other._nptr)->_pri);
    // set the nodes left subtree to other nodes left subtree
    (_nptr->_left) = (other._nptr)->_left;
    // set the nodes right subtree to other nodes right subtree
    (_nptr->_right) = (other._nptr)->_right;

    // update the height of the treap
    updateHeight();
    
  }
}

Treap::~Treap() {
  //
  // Implement destructor
  //

  // if the root isn't already empty
  if ( _nptr != nullptr ){

    // delete its left child as much as it can
    if((_nptr->_left)._nptr != nullptr){

      delete (_nptr->_left)._nptr;
      (_nptr->_left)._nptr = nullptr;
    }

    // then delete right children as much as possible
    if((_nptr->_right)._nptr != nullptr){

      delete (_nptr->_right)._nptr;
      (_nptr->_right)._nptr = nullptr;
    }

    delete _nptr;
    _nptr = nullptr;

  }
  
}

const Treap& Treap::operator=(const Treap& rhs) {
  //
  // Implement assignment operator
  //

  // delete the original root
  delete _nptr;
  _nptr = nullptr;

  // if the rhs isn't just null
  if( rhs._nptr != nullptr){

    // create a deep copy of the rhs
    _nptr = new TreapNode((rhs._nptr)->_data, (rhs._nptr)->_pri);
    // set the left subtree equal to the rhs left subtree
    (_nptr->_left) = (rhs._nptr)->_left;
    // set the right subtree equal to the rhs right subtree
    (_nptr->_right) = (rhs._nptr)->_right;

    // update the height of the treap
    updateHeight();
  }

  return *this;
}

// Return -1 if the treap is empty; otherwise, return value in _height.
int Treap::height() const {
  return _nptr ? _nptr->_height : -1 ;
}

// Return the priority of the root node of a Treap.
// Note: numeric_limits<priority_t>::min() returns the minimum value
// of the priority type.  We will only use int priorities, so this is
// the minimum integer value.
priority_t Treap::priority() const {
  return _nptr ? _nptr->_pri : numeric_limits<priority_t>::min();
}

const data_t* Treap::find(const data_t& x) {
  //
  // Implement find function
  //
  
  // if the node is empty
  if(_nptr == nullptr){
    return nullptr;
  }
  
  // if the data is found, return it
  if(_nptr->_data == x){
    return &_nptr->_data;
  }

  // if x is less than the current nodes data, go left
  if(_nptr->_data > x){
    return (_nptr->_left).find( x );
  }

  // if x is greater than the current nodes data, go right
  if(_nptr->_data < x){
    return (_nptr->_right).find( x );
  }

  // return null if its not found
  return nullptr;
}

// Inorder traversal.  Recommend you NOT change this!!!
void Treap::inorder() {

  if ( empty() ) return ;

  cout << "(" ;
  _nptr->_left.inorder() ;

  cout << _nptr->_data << ":" << priority() << ":" << height() ;

  _nptr->_right.inorder() ;
  cout << ")" ;

  return  ;
}

// Used for debugging and grading.  Interprets the characters in
// position[] as directions in the tree.  E.g., "RLR" means, "starting
// from root, go right, then left, then right."  If position[] is an
// empty string, then it just locats the value a the root.
// See project description for details.
bool Treap::locate (const char position[], data_t& x, priority_t& p, int& h, int offset) {

  if (_nptr == nullptr) return false ;

  if (position[offset] == '\0') {
    x = _nptr->_data ;
    p = _nptr->_pri ;
    h = _nptr->_height ;
    return true ;
  }

  if (position[offset] == 'L') {
    return _nptr->_left.locate(position, x, p, h, offset+1) ;
  }

  if (position[offset] == 'R') {
    return _nptr->_right.locate(position, x, p, h, offset+1) ;
  }

  cerr << "Bad position character!\n" ;
  exit(17) ;

  return false ; 
}


// Basic BST insertion.  Does not allow duplicate values.
//
// Complete this function to do Treap insertion.
//
void Treap::insert(const data_t& x, const priority_t& p) {

  if ( empty() ) {
    _nptr = new TreapNode(x, p) ;
  }

  // if new data is greater than current data, insert right
  if ( _nptr->_data < x ) {
    _nptr->_right.insert(x, p) ;

    // if prio is less than right child, left rotate
    if( (_nptr->_pri < ((_nptr->_right)._nptr)->_pri) ){
      rotateLeft();
    }
                                               
  }
  // if new data is less than current data, insert left
  else if ( x < _nptr->_data ) {
    _nptr->_left.insert(x, p);
    
    // if prio is less than left child, right rotate
    if( (_nptr->_pri < ((_nptr->_left)._nptr)->_pri) ){
      rotateRight();
    }
  }

  // update height
  _nptr->_left.updateHeight();
  _nptr->_right.updateHeight();
  updateHeight();
}

bool Treap::remove(const data_t& x) {
  //
  // Implement treap element removal
  //

  // flag to find if the data was found
  static bool found = false;
  static data_t xPrev = x;

  // if its a new node, reset found
  if (x != xPrev){
    found = false;
    xPrev = x;
  }

  // if the node is null, or not found in the tree return false
  if ((find( x ) == nullptr || _nptr == nullptr) && found == false){
    return false;
  }

  // if the node has been found, return true
  if (found == true){
    return true;
  }
  
  TreapNode *rightChild = (_nptr->_right)._nptr;
  TreapNode *leftChild = (_nptr->_left)._nptr;
  
  // if the data is found, delete it                        
  if(_nptr->_data == x){
    
    // if the node is a leaf (has no children), just delete it
    if( (rightChild == nullptr && leftChild == nullptr)
	&& (_nptr->_data == x) ){
      
      // flag that the data was found
      found = true;

      // delete the node
      delete _nptr;
      _nptr = nullptr;

      return true;
    }
    
    // if the node has no right child
    if( rightChild == nullptr && _nptr->_data == x ){
      
      // rotate until root is a leaf
      rotateRight();
      // call remove recursively
      remove(x);
    }
    
    // if the node has no left child
    if( leftChild == nullptr && _nptr->_data == x ){
      
      // rotate until the root is a leaf
      rotateLeft();
      // call remove recursively
      remove(x);
    }
    
  }
  
  // if x is less than the current nodes data, go left
  if(_nptr->_data > x){

    // continually update height depending on direction
    if( leftChild != nullptr ){
      leftChild->_height--;
    }
    
    // update the height
    updateHeight();
    // call remove recursively to the left
    return (_nptr->_left).remove( x );
  }
  
  // if x is greater than the current nodes data, go right
  if(_nptr->_data < x){

    // continually update height depending on direction
    if ( rightChild != nullptr){
      rightChild->_height--;
    }
    
    // update the height
    updateHeight();
    // call remove recursively to the right
    return (_nptr->_right).remove( x );
  }
  
  
  // rotate the node to be deleted to the bottom if we found it
  // by continually using right and left rotations
  
  // if the prio of the right child is greater than the prio of left child
  // rotate that one
  if(_nptr->_data == x && (rightChild)->_pri > (leftChild)->_pri){
    
    // rotate left, so the greater node is the new root
    rotateLeft();
    // keep calling remove, until there are no left or right children
    (_nptr->_left).remove(x);
  }
  
  // if the prio of right child is less than prio of left child
  if( _nptr->_data == x && ( rightChild->_pri < leftChild->_pri ) ){
    
    // rotate right, so the greater node is the new root
    rotateRight();
    // keep calling remove, until there are no left or right children
    (_nptr->_right).remove(x);
  }
  
  // update height
  _nptr->_left.updateHeight();
  _nptr->_right.updateHeight();
  updateHeight();

  return true;
}

// Treap::dump() just calls TreapNode::dump()
void Treap::dump() {
  if ( !empty() ) _nptr->dump() ;
}

ostream& operator<< (ostream& os, const Treap& T) {
  os << T._nptr ; 
  return os ;
}

TreapNode::TreapNode() : _height(0) {  
  // Empty constructor body

}

TreapNode::TreapNode(const data_t& x, const priority_t& p) 
  : _data(x), _pri(p), _height(0) { 
  // Empty constructor body

}

TreapNode::~TreapNode() {
  // Empty destructor
  // Retained for debugging
}

// Dump the contents of a node
void TreapNode::dump() {
  cout << "===== TreapNode::dump()\n" ;
  cout << "      this = " << this << endl ; 
  cout << "      left = " << _left << endl ; 
  cout << "      right= " << _right << endl ; 
  cout << "      data = " << _data << endl ;
  cout << "      height = " << _height << endl ;
  _left.dump() ;
  _right.dump() ;
}

int Treap::greatestHeight(int lhs, int rhs){
  // if lhs is greatest, return lhs
  if (lhs > rhs){
    return lhs;
  }
  // if rhs is greatest, return rhs
  if (lhs < rhs){
    return rhs;
  }

  // if they are equal, just return either one
  return rhs;
}

void Treap::rotateRight(){
  // for both rotate right and left, I refer to the provided picture
  // of a tree in the document that includes "Y","X","a","b", and "c".
  
  // get "b"
  TreapNode *temp = (( (_nptr->_left)._nptr)->_right)._nptr;

  // get "Y" and its subtrees
  TreapNode *tempLeft = (_nptr->_left)._nptr;
  
  // set "Y" and its subtrees to  null
  (_nptr->_left)._nptr = nullptr;

  // "Y"'s right is now "X"
  ((tempLeft)->_right)._nptr = _nptr;

  // "Y"'s right left is now "b"
  ((_nptr->_left)._nptr) = temp;

  // new root is now "Y"
  _nptr = tempLeft;
}

void Treap::rotateLeft(){
  // for both rotate right and left, I refer to the provided picture
  // of a tree in the document that includes "Y","X","a","b", and "c".
  
  // get "b"
  TreapNode *temp = (( (_nptr->_right)._nptr)->_left)._nptr;

  // get "X" and its subtrees
  TreapNode *tempRight = (_nptr->_right)._nptr;

  // set "X" and its subtrees to null
  (_nptr->_right)._nptr = nullptr;
  
  // "X"'s left = "Y"  and its subtrees
  ((tempRight)->_left)._nptr = _nptr;

  // "X"'s left right is now "b"
  ((_nptr->_right)._nptr) = temp;

  // new root is now "X"
  _nptr = tempRight;
}

void Treap::updateHeight(){

  // if the node is null, just return
  if(_nptr == nullptr){
    return;
  }
  // if the node isn't null, update the height of the node
  else{
    int leftHeight = _nptr->_left.height();
    int rightHeight = _nptr->_right.height();
    _nptr->_height = 1 + ( greatestHeight( leftHeight, rightHeight )); 
  }
}
  
