#ifndef __Dir3D__

#define __Dir3D__
#include "CH3D.h"
#include "Pos3D.h"

class Dir3D : public CH3D {
public:
	Dir3D(void);
	Dir3D(float x, float y, float z);
	Dir3D(Dir3D* p);
	Dir3D(Pos3D* p1, Pos3D* p2);
	virtual ~Dir3D(void);

	float produitScalaire(Dir3D* d);
	Dir3D produitVectoriel(Dir3D* d);
	bool isPlane(Pos3D* s0, Pos3D* s1, Pos3D* s2, Pos3D* s3);
};
#endif