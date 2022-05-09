#ifndef __Personnage__

#define __Personnage__
#include <iostream>

#define PI 3.14159265

class Personnage {
	private:
		float POSX;
		float POSY;
		float taille;
		float direction;

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
		void bras(float angleAvantBras, float angleBras, float size);
		void corps(float size);
		void jambe(float angleCuisse, float angleTibia, float size);
	public:
		Personnage(void);
		Personnage(float posX, float posY, float taille);
		virtual ~Personnage(void);

		void idle();
		void avancer();
		void deplacement(float dist);
		float getPosX();
		float getPosY();
		float getDir();
		void changerDirection(float changementDir);
};
#endif