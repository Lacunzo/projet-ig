#pragma once
#include <iostream>
using namespace std;

enum class Cell { Empty, Floor, Wall, Pillar, Key };

ostream& operator<<(ostream& os, const Cell& cell);