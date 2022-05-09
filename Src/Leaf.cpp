#include "Leaf.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

Leaf::Leaf(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    this->leftChild = nullptr;
    this->rightChild = nullptr;
    this->room = nullptr;
}

bool Leaf::split() {
    if (this->leftChild != nullptr || rightChild != nullptr) return false;

    bool splitH = rand() > 0.5;
	
    if (this->width > height && width / height >= 1.25) {
        splitH = false;
    } else if (height > width && height / width >= 1.25) {
        splitH = true;
    }

    int max = (splitH ? height : width) - MIN_LEAF_SIZE;
    if (max <= MIN_LEAF_SIZE) return false;

    int split = rand() % max + MIN_LEAF_SIZE;

    if (splitH) {
        leftChild = new Leaf(x, y, width, split);
        rightChild = new Leaf(x, y + split, width, height - split);
    } else {
        leftChild = new Leaf(x, y, split, height);
        rightChild = new Leaf(x + split, y, width - split, height);
    }
	
    return true;
}

void Leaf::print() const {
    cout << "Leaf: " << x << " " << y << " " << width << " " << height << endl;
}

void Leaf::prettyPrint() const {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i >= y && i < y + height && j >= x && j < x + width) {
                cout << "*";
            }
            else {
                cout << " ";
            }
        }
    }
}
