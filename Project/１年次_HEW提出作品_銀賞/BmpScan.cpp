#include"conioex_New.h"
#include"Game.h"
using namespace std;

void BmpScan(Player* p, Pic* pic) {
	// 前のデータの消去
	switch (p->nowMap) {
	case 0:// タイトル画面
		DeleteBmp(&pic->titleback);
		DeleteBmp(&pic->title_exit);
		DeleteBmp(&pic->title_start);
		MciCloseSound(p->bgm[0]);
		break;
	case 3:// チュートリアル
		// テキスト画像破棄
		for (int i = 0; i < 6; i++ ) {
			DeleteBmp(&pic->e1_t1[i]);
			DeleteBmp(&pic->e1_t2[i]);
		}
		MciCloseSound(p->bgm[1]);
		break;
	case 4:
		for (int i = 0; i < 8; i++) {
			DeleteBmp(&pic->e3_t[i]);
			
		}
		MciCloseSound(p->bgm[3]);
		break;
	case 5:
		MciCloseSound(p->bgm[4]);
		break;
	case 7:
		MciCloseSound(p->bgm[5]);
		break;
	case 13:
		MciCloseSound(p->bgm[4]);
		break;
	case 18:
		for (int i = 0; i < 6; i++) {
			DeleteBmp(&pic->b2_t1[i]);
			DeleteBmp(&pic->b2_t2[i]);
		}
		MciCloseSound(p->bgm[6]);
		break;
	case 19:
		for (int i = 0; i < 6; i++) {
			DeleteBmp(&pic->b2_t3[i]);
		}
		for (int i = 0; i < 3; i++) {
			DeleteBmp(&pic->b2_t4[i]);
		}
		MciCloseSound(p->bgm[6]);
		break;
	case 20:
		for (int i = 0; i < 2; i++) {
			DeleteBmp(&pic->b2_t5[i]);
		}
		MciCloseSound(p->bgm[7]);
		break;
	case 21:
		MciCloseSound(p->bgm[5]);
		DeleteBmp(&pic->end[p->end_number-1]);
		break;
	}
	// 次に読み込むマップのデータ起動
	switch (p->changemap[1]) {
	case 0:// タイトル
		pic->titleback = LoadBmp("pic/title/タイトル画面.bmp");
		pic->title_start = LoadBmp("pic/title/START.bmp");
		pic->title_exit = LoadBmp("pic/title/EXIT.bmp");
		p->bgm[0] = MciOpenSound("sound/bgm/title.mp3");
		break;
	case 1:
		// テキスト読み込み
		pic->e1_t1[0] = LoadBmp("pic/text/e1_t1.bmp");
		pic->e1_t1[1] = LoadBmp("pic/text/e1_t2.bmp");
		pic->e1_t1[2] = LoadBmp("pic/text/e1_t3.bmp");
		pic->e1_t1[3] = LoadBmp("pic/text/e1_t4.bmp");
		pic->e1_t1[4] = LoadBmp("pic/text/e1_t5.bmp");
		pic->e1_t1[5] = LoadBmp("pic/text/e1_t6.bmp");
		pic->e1_t2[0] = LoadBmp("pic/text/e1_t7.bmp");
		pic->e1_t2[1] = LoadBmp("pic/text/e1_t8.bmp");
		pic->e1_t2[2] = LoadBmp("pic/text/e1_t9.bmp");
		pic->e1_t2[3] = LoadBmp("pic/text/e1_t10.bmp");
		pic->e1_t2[4] = LoadBmp("pic/text/e1_t11.bmp");
		pic->e1_t2[5] = LoadBmp("pic/text/e1_t12.bmp");
		// キャラ読み込み

		// bgm読み込み
		p->bgm[1] = MciOpenSound("sound/bgm/siro.mp3");
		p->bgm[2] = MciOpenSound("sound/bgm/sento.mp3");
		// 背景画像読み込み
		pic->b2_1_buck = LoadBmp("pic/背景/boss2_1.bmp");
		break;
	case 4:
		p->bgm[3] = MciOpenSound("sound/bgm/outo.mp3");
		pic->e3_t[0] = LoadBmp("pic/text/outo/0.bmp");
		pic->e3_t[1] = LoadBmp("pic/text/outo/1.bmp");
		pic->e3_t[2] = LoadBmp("pic/text/outo/2.bmp");
		pic->e3_t[3] = LoadBmp("pic/text/outo/3.bmp");
		pic->e3_t[4] = LoadBmp("pic/text/outo/4.bmp");
		pic->e3_t[5] = LoadBmp("pic/text/outo/5.bmp");
		pic->e3_t[6] = LoadBmp("pic/text/outo/6.bmp");
		pic->e3_t[7] = LoadBmp("pic/text/outo/7.bmp");
		break;
	case 5:
		p->bgm[4] = MciOpenSound("sound/bgm/sougen.mp3");
		break;
	case 7:
		p->bgm[5] = MciOpenSound("sound/bgm/mori.mp3");
		break;
	case 13:
		p->bgm[4] = MciOpenSound("sound/bgm/sougen.mp3");
		break;
	case 18:
		// 背景画像読み込み
		pic->b2_1_buck = LoadBmp("pic/背景/boss2_1.bmp");
		// テキスト画像読み込み
		pic->b2_t1[0] = LoadBmp("pic/text/Boss2_1/b2_1_1.bmp");
		pic->b2_t1[1] = LoadBmp("pic/text/Boss2_1/b2_1_2.bmp");
		pic->b2_t1[2] = LoadBmp("pic/text/Boss2_1/b2_1_3.bmp");
		pic->b2_t1[3] = LoadBmp("pic/text/Boss2_1/b2_1_4.bmp");
		pic->b2_t1[4] = LoadBmp("pic/text/Boss2_1/b2_1_5.bmp");
		pic->b2_t1[5] = LoadBmp("pic/text/Boss2_1/b2_1_6.bmp");
		pic->b2_t2[0] = LoadBmp("pic/text/Boss2_1/boss2_12_1.bmp");
		pic->b2_t2[1] = LoadBmp("pic/text/Boss2_1/boss2_12_2.bmp");
		pic->b2_t2[2] = LoadBmp("pic/text/Boss2_1/boss2_12_3.bmp");
		pic->b2_t2[3] = LoadBmp("pic/text/Boss2_1/boss2_12_4.bmp");
		pic->b2_t2[4] = LoadBmp("pic/text/Boss2_1/boss2_12_5.bmp");
		pic->b2_t2[5] = LoadBmp("pic/text/Boss2_1/boss2_12_6.bmp");
		// ボス画像読み込み
		pic->boss_nomal_l = LoadBmp("pic/ボス関係/ボス左待機.bmp");
		pic->boss_walk_l[0] = LoadBmp("pic/ボス関係/ボス左歩き１.bmp");
		pic->boss_walk_l[1] = LoadBmp("pic/ボス関係/ボス左歩き２.bmp");
		pic->boss_walk_l[2] = LoadBmp("pic/ボス関係/ボス左歩き３.bmp");
		pic->boss_walk_l[3] = LoadBmp("pic/ボス関係/ボス左歩き４.bmp");
		pic->boss_walk_l[4] = LoadBmp("pic/ボス関係/ボス左歩き５.bmp");
		pic->boss_walk_l[5] = LoadBmp("pic/ボス関係/ボス左歩き６.bmp");
		pic->boss_nomal_r = LoadBmp("pic/ボス関係/ボス右待機.bmp");
		pic->boss_walk_r[0] = LoadBmp("pic/ボス関係/ボス右歩き１.bmp");
		pic->boss_walk_r[1] = LoadBmp("pic/ボス関係/ボス右歩き２.bmp");
		pic->boss_walk_r[2] = LoadBmp("pic/ボス関係/ボス右歩き３.bmp");
		pic->boss_walk_r[3] = LoadBmp("pic/ボス関係/ボス右歩き４.bmp");
		pic->boss_walk_r[4] = LoadBmp("pic/ボス関係/ボス右歩き５.bmp");
		pic->boss_walk_r[5] = LoadBmp("pic/ボス関係/ボス右歩き６.bmp");
		
		p->bgm[6] = MciOpenSound("sound/bgm/boss1.mp3");
		
		break;
	case 19:
		// 背景画像読み込み
		pic->b2_2_buck = LoadBmp("pic/背景/boss2_2.bmp");
		pic->b2_t3[0] = LoadBmp("pic/text/Boss2_2/b2_2_1.bmp");
		pic->b2_t3[1] = LoadBmp("pic/text/Boss2_2/b2_2_2.bmp");
		pic->b2_t3[2] = LoadBmp("pic/text/Boss2_2/b2_2_3.bmp");
		pic->b2_t3[3] = LoadBmp("pic/text/Boss2_2/b2_2_4.bmp");
		pic->b2_t3[4] = LoadBmp("pic/text/Boss2_2/b2_2_5.bmp");
		pic->b2_t3[5] = LoadBmp("pic/text/Boss2_2/b2_2_6.bmp");
		pic->b2_t4[0] = LoadBmp("pic/text/Boss2_2/b2_23_1.bmp");
		pic->b2_t4[1] = LoadBmp("pic/text/Boss2_2/b2_23_2.bmp");
		pic->b2_t4[2] = LoadBmp("pic/text/Boss2_2/b2_23_3.bmp");
		// 魔法弾
		pic->boss_maho[0] = LoadBmp("pic/ボス関係/魔法弾１.bmp");
		pic->boss_maho[1] = LoadBmp("pic/ボス関係/魔法弾２.bmp");
		p->bgm[6] = MciOpenSound("sound/bgm/boss1.mp3");
		break;
	case 20:
		pic->b2_t5[0] = LoadBmp("pic/text/Boss2_3/b2_3_1.bmp");
		pic->b2_t5[1] = LoadBmp("pic/text/Boss2_3/b2_3_2.bmp");
		p->bgm[7] = MciOpenSound("sound/bgm/boss2.mp3");
		break;
	case 21:
		switch (p->end_number) {
		case 1:
			pic->end[0] = LoadBmp("pic/End/１.bmp");
			break;
		case 2:
			pic->end[1] = LoadBmp("pic/End/２.bmp");
			break;
		case 3:
			pic->end[2] = LoadBmp("pic/End/３.bmp");
			break;
		case 4:
			pic->end[3] = LoadBmp("pic/End/４.bmp");
			break;
		case 5:
			pic->end[4] = LoadBmp("pic/End/５.bmp");
			break;
		case 6:
			pic->end[5] = LoadBmp("pic/End/６.bmp");
			break;
		}
		p->bgm[5] = MciOpenSound("sound/bgm/mori.mp3");
	}

	p->changemap[0] = 0;
	p->beforeMap = p->nowMap;
	p->nowMap = p->changemap[1];
}