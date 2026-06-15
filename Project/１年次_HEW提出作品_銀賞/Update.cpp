#include"conioex_New.h"
#include"Game.h"
using namespace std;

void Update(Player* p, Key* key, Map* m,Enemy* e) {
	switch (p->nowMap) {
	case -1:
		Menu_Update(p, key);
		break;
	case 0:
		Title_Update(p, key, m, e);
		break;
	case 1:
		Event1_Update(p,key,m,e);
		break;
	case 2:
		Event2_Update(p, key, m, e);
		break;
	case 3:
		Event3_Update(p, key, m);
		break;
	case 4:
		Map4_Update(p, key, m);
		break;
	case 5:
		Map1_Update(p, key, m,e);
		break;
	case 6:
		Battle1_Update(p, key, m,e);
		break;
	case 7:
		Map7_Update(p, key, m, e);
		break;
	case 13:
		Map13_Update(p, key, m,e);
		break;
	case 18:
		Boss2_1_Update(p, key, m, e);
		break;
	case 19:
		Boss2_2_Update(p, key, m, e);
		break;
	case 20:
		Boss2_3_Update(p, key, m, e);
		break;
	case 21:
		End_Update(p, key);
		break;
	}
}