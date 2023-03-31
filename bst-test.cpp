#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"
#include "print_bst.h"

using namespace std;


int main(int argc, char *argv[])
{
    /*// Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
*/
    // AVL Tree Tests

  AVLTree<uint16_t, uint16_t> at;
  at.insert(std::make_pair(0, 9));
	at.insert(std::make_pair(1, 8));
	at.insert(std::make_pair(2, 159));

  at.print();


    return 0;
}
