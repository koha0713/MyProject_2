#include"conioex_New.h"
#include"Game.h"
using namespace std;

void End_Draw(Player* p, Pic* pic) {
    switch (p->end_number) {
    case 1:
        SetPalette(pic->end[0]);
        DrawBmp(0, 0, pic->end[0], false);
        break;
    case 2:
        SetPalette(pic->end[1]);
        DrawBmp(0, 0, pic->end[1], false);
        break;
    case 3:
        SetPalette(pic->end[2]);
        DrawBmp(0, 0, pic->end[2], false);
        break;
    case 4:
        SetPalette(pic->end[3]);
        DrawBmp(0, 0, pic->end[3], false);
        break;
    case 5:
        SetPalette(pic->end[4]);
        DrawBmp(0, 0, pic->end[4], false);
        break;
    case 6:
        SetPalette(pic->end[5]);
        DrawBmp(0, 0, pic->end[5], false);
        break;
    }
    PrintFrameBuffer();
}

void End_Update(Player* p, Key* k ) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[5], true);
        p->bgm_t = 0;
    }
	if (k->key_enter_T == 1) {
        p->changemap[0] = 1;
        p->changemap[1] = 0;
	}
}