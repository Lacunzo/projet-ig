#include "Pos3D.h"
#include "CH3D.h"

Pos3D::Pos3D(void) :CH3D(0.0F, 0.0F, 0.0F, 1.0F) {};
Pos3D::Pos3D(float x, float y, float z):CH3D(x,y,z,1.0F){}
Pos3D::Pos3D(Pos3D* p) : CH3D(p) {};
Pos3D::~Pos3D(void) {};