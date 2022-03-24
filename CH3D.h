#ifndef __CH3D__

#define __CH3D__

class CH3D {
public:
	float x;
	float y;
	float z;
protected:
	float w;
protected:
	CH3D();
	CH3D(float x, float y, float z, float w);
	CH3D(CH3D* ch);
	virtual ~CH3D(void); //destructeur
};
#endif