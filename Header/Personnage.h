#ifndef __Personnage__

#define __Personnage__
#include <iostream>

class Personnage {
public:
	int POSX;
	int POSY;
	float taille;
private:
	float angleJambe1;
	float angleJambe1T;
	float angleJambe2;
	float angleJambe2T;
	float angleAvantBras1;
	float angleBras1;
	float angleAvantBras2;
	float angleBras2;
	float angleCorps;

	bool animationUp;
	int nbFrameAnimation;
public:
	Personnage(void);
	Personnage(int posX, int posY);
	virtual ~Personnage(void);

	void idle();
	void avancer();
private:
	void bras(float angleAvantBras, float angleBras, float size);
	void corps(float size);
	void jambe(float angleCuisse, float angleTibia, float size);
};
#endif