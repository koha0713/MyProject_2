#include"conioex_New.h"
#include"Game.h"
using namespace std;

void Draw(Player* p, Pic* pic, Map* m, Enemy* e) {
	switch (p->nowMap) {
	case -1:
		Menu_Draw(p,pic);
		break;
	case 0:
		Title_Draw(p,pic,m,e);
		break;
	case 1:
		Event1_Draw(p, pic, m, e);
		break;
	case 2:
		Event2_Draw(p, pic, m, e);
		break;
	case 3:
		Event3_Draw(p, pic, m);
		break;
	case 4:
		Map4_Draw(p, pic, m);
		break;
	case 5:
		Map1_Draw(p, pic, m,e);
		break;
	case 6:
		Battle1_Draw(p, pic, m,e);
		break;
	case 7:
		Map7_Draw(p,pic,m,e);
		break;
	case 13:
		Map13_Draw(p, pic, m);
		break;
	case 18:
		Boss2_1_Draw(p, pic, m, e);
		break;
	case 19:
		Boss2_2_Draw(p, pic, m, e);
		break;
	case 20:
		Boss2_3_Draw(p, pic, m, e);
		break;
	case 21:
		End_Draw(p, pic);
		break;
	}
}