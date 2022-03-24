#ifndef __TG3D__

#define __TG3D__
#include "CH3D.h"

class TG3D : public CH3D {
public:
	float m[4][4];
public:
	TG3D(void);
	TG3D(float *v);
	TG3D(TG3D* tg);
	virtual ~TG3D(void);
};
#endif