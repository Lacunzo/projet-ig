#include "Dir3D.h"
#include "CH3D.h"

Dir3D::Dir3D(void) :CH3D(0.0F, 0.0F, 0.0F, 1.0F) {};
Dir3D::Dir3D(float x, float y, float z) :CH3D(x, y, z, 1.0F) {}
Dir3D::Dir3D(Dir3D* p) : CH3D(p) {};
Dir3D::Dir3D(Pos3D* p1, Pos3D* p2) :CH3D(p1->x - p2->x, p1->y - p2->y, p1->z - p2->z, 1.0F) {}
Dir3D::~Dir3D(void) {};
float Dir3D::produitScalaire(Dir3D* d) {
	return x * d->x + y * d->y + z * d->z;
};
Dir3D Dir3D::produitVectoriel(Dir3D* d) {
	return Dir3D(y * d->z - z * d->y, z * d->x - x * d->z, x * d->y - y * d->x);
};
bool Dir3D::isPlane(Pos3D* s0, Pos3D* s1, Pos3D* s2, Pos3D* s3) {
	Dir3D v1(s0, s1);
	Dir3D v2(s0, s2);
	Dir3D v3(s0, s3);
	Dir3D w = v1.produitVectoriel(&v3);
	return w.produitScalaire(&v2) <= 0.000001;
};