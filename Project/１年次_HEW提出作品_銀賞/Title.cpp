#include"conioex_New.h"
#include"Game.h"
using namespace std;

void Title_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {
	// ”wŒi‰æ‘œ‚Ì•`ŽÊ
	SetPalette(pic->titleback);
	DrawBmp(0, 0, pic->titleback, false);
	// ƒ^ƒCƒgƒ‹‰æ‘œ‚Ì•`ŽÊ

	// ‘I‘ðŽˆ‚Ì•`ŽÊ
	SetPalette(pic->title_start);
	DrawBmp(240, 224, pic->title_start ,false);
	SetPalette(pic->title_exit);
	DrawBmp(240, 288, pic->title_exit, false);

	switch (p->choicenumber%2) {
	case 0:
		SetPalette(pic->choice);
		DrawBmp(208, 224, pic->choice, true);
		break;
	case 1:
		SetPalette(pic->choice);
		DrawBmp(208, 288, pic->choice, true);
		break;
	}
	PrintFrameBuffer();
}

void Title_Update(Player* p, Key* k, Map* m, Enemy* e) {
	if (p->bgm_t == 1) {
		MciPlaySound(p->bgm[0], true);
		p->bgm_t = 0;
	}

	if (k->key_enter_T) {
		switch (p->choicenumber % 2) {
		case 0:
			p->changemap[0] = 1;
			p->changemap[1] = 1;
			p->scene_cnt = 0;
			p->text[0] = 1;
			p->text[1] = 1;
			p->flug_event[0] = 0;
			p->flug_event[1] = 0;
			p->flug_event[2] = 0;
			p->flug_event[3] = 0;
			p->flug_event[4] = 0;
			p->bgm_t = 1;
			break;
		case 1:
			p->gameloop = false;
			break;
		}
	}

	if (k->key_down_T == 1) {
		p->choicenumber++;
	}
	else if (k->key_up_T == 1) {
		p->choicenumber--;
	}
}