#ifndef __Pos3D__

#define __Pos3D__
#include "CH3D.h"

class Pos3D : public CH3D {
public:
	Pos3D(void);
	Pos3D(float x, float y, float z);
	Pos3D(Pos3D* p);
	virtual ~Pos3D(void);
};
#endif