#ifndef __Personnage__

#define __Personnage__
#include <iostream>

class Personnage {
public:
	int POSX;
	int POSY;
public:
	Personnage(void);
	Personnage(int posX, int posY);
	virtual ~Personnage(void);

	void generate(int x, int y);
	void bras(float angleAvantBras, float angleBras, float size);
	void corp(float size);
	void jambe(float angleCuisse, float angleTibia, float size);
};
#endif