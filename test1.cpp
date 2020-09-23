
// CMSC 341 - Fall 2019 - Project 3
// Basic test driver for the Treap class
// Creates the treap example from the project write-up and deletes two
// values

#include <iostream>
#include "treap.h"

using namespace std;

int main() {
  
  Treap T;

        
  T.insert("B", 24);
  T.insert("C", 35);  
  T.insert("H", 29);
  T.insert("E", 33);
  T.insert("I", 25);
  T.insert("K", 9);
  T.insert("A", 21);
  T.insert("L", 16);
  T.insert("D", 8);
  T.insert("J", 13);
  T.insert("G", 50);
  
  // Delete "K" and "C"
  T.remove("K");
  T.remove("C");
  //T.remove("L");

  /*    
  T.insert("A", 19);
  T.insert("B", 56);
  T.insert("C", 28);
  T.insert("D", 5);
  T.insert("E", 42);
  T.insert("F", 12);
  T.insert("G", 31);
  T.insert("H", 2);
  T.insert("I", 73);
  T.insert("J", 62);
  T.insert("K", 37);
  T.insert("L", 53);
  T.insert("M", 76);
  T.insert("N", 55);
  T.insert("O", 23);
  T.insert("P", 30);
  T.insert("Q", 36);
  T.insert("R", 72);
  T.insert("S", 46);
  T.insert("T", 1);
  T.insert("U", 77);
  T.insert("V", 47);
  T.insert("W", 48);
  T.insert("X", 27);
  T.insert("Y", 32);
  T.insert("Z", 6);

  T.remove("A");
  T.remove("A");
  T.remove("A");
  T.remove("B");
  T.remove("B");
  T.remove("C");
  T.remove("D");
  T.remove("E");
  T.remove("F");
  T.remove("G");
  T.remove("H");
  T.remove("I");
  T.remove("J");
  T.remove("K");
  T.remove("L");
  T.remove("M");
  T.remove("N");
  T.remove("O");
  T.remove("K");
  T.remove("I");
  T.remove("P");
  T.remove("Q");
  T.remove("R");
  T.remove("S");
  T.remove("T");
  T.remove("U");
  //T.remove("V");
  //T.remove("W");
  //T.remove("X");
  //T.remove("Y");
  T.remove("I");
  //T.remove("Z");
  */
  
  cout << endl;
  T.inorder();
  cout << endl;
  
  T.dump();
  
  return 0;
}
