#include"conioex_New.h"
#include"Game.h"
using namespace std;


void Menu_Draw(Player* p, Pic* pic) {
	// 背景画像、ボタンの呼び出し
	SetPalette(pic->menu_title);
	DrawBmp(240, 224, pic->menu_title, false);
	SetPalette(pic->menu_back);
	DrawBmp(240, 288, pic->menu_back, false);
	// 選択肢の書き込み
	switch (p->choicenumber % 2) {
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
	return;
}
void Menu_Update(Player* p, Key* k) {
	if (k->key_enter_T) {
		switch (p->choicenumber % 2) {
		case 0:
			p->changemap[0] = 1;
			p->changemap[1] = 0;
			p->scene_cnt = 0;
			break;
		case 1:
			p->nowMap = p->menumap;
			break;
		}
	}

	if (k->key_down_T == 1) {
		p->choicenumber++;
	}
	else if (k->key_up_T == 1) {
		p->choicenumber--;
	}
	return;
}