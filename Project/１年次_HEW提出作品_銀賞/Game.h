#pragma once

#include<iostream>
using namespace std;

// 構造体定義
struct Player {
	bool gameloop;
	int Name[10];// 名前
	int Gender;// 性別 
	int Job;//　職業
	int Level;//　レベル
	int Exp;//　累計経験値
	int Hp;
	int HpMax;
	int Atk;
	int AtkPlus;
	int Int;
	int IntPlus;
	int Trust;// 信頼値
	int Lank;
	int NowQuest;// 依頼を受けているか
	int Money;
	int Hand;
	int Bogu;
	// 座標
	int F_x;
	int F_y;
	int Left;
	int Right;
	int Top;
	int Bottom;
	int N_x;
	int N_y;
	// バトルマップ用座標
	int B_Left;
	int B_Right;
	int B_Top;
	int B_Bottom;
	int Center[2];
	int B_x;
	int B_y;
	int zan_x = 0;
	int zan_y = 0;

	int flug_Ground;// 設置フラグ
	int flug_BoxGround;// 障害物の接地フラグ
	int flug_Jump;
	int flug_Fall;
	int JumpCount;
	int FallCount;
	int ani_cnt;
	int ani_cnt2;
	int ani_data_1[16];
	int ani_data_2[13];// バトル走り
	int ani_data_3[8];// 斬撃エフェクト
	int flug_Move;
	int flug_Move_finish;
	int flug_Zan;
	int flug_changeBattle;
	int flug_damage;
	int muteki_cnt;
	int change_cnt;
	int changemap[2];// マップ変更フラグ、次に移動するマップ
	int nowMap;
	int beforeMap;
	int menumap;
	/*イベントフラグ一覧
	０：中ボス戦闘済ませたか
	１：隠しエンディング
	２：ラスボス一戦目の会話フラグ
	３：ラスボス二戦目の会話フラグ
	４：ラスボス三戦目の会話フラグ
	*/
	int flug_event[5];
	int end_number;

	int choicenumber;
	int scene_cnt;

	// テキスト＆イベント関係
	int text[3];// テキストフラグ、現在のテキストナンバー、キャラアイコン

	/* 0:title,1:城,2:モブ戦闘,3:王都,4:草原,5:森,6:ボス１,7:ボス２,
	*/
	int* bgm[8];
	int* se_jump1;
	int* se_jump2;
	int* se_fire;
	int* se_damage;
	int* se_attack;

	int bgm_t;
};

struct Enemy {
	//0：HP,1:ATK,2:Left,3:Right,4:Top,5:Bottom,6:向き,7:最大HP
	int enemy[6][8];
	int flug_enemy;// 敵生存か
	int e_cnt;// プレイヤーの位置を探るクールタイム
	int now_enemy;// 今戦ている敵の番号
	int flug_damage;// 無敵状態判定
	int blood_x;
	int e_anime_cnt;
	int flug_e_walk;
	int anime[19];
	int mahodan[5][5];
	int next_maho;
	int now_maho;
	int time;
};

struct Pic {
	// 常にメモリに置いておくもの
	Bmp* textbox;
	Bmp* choice;
	// プレイヤー　バトルマップ
	Bmp* b_r;// 右待機
	Bmp* b_l;// 左待機
	Bmp* b_r_run[6];
	Bmp* b_l_run[6];
	Bmp* b_r_run1;
	Bmp* b_r_run2;
	Bmp* b_r_run3;
	Bmp* b_r_run4;
	Bmp* b_r_run5;
	Bmp* b_r_run6;
	Bmp* b_l_run1;
	Bmp* b_l_run2;
	Bmp* b_l_run3;
	Bmp* b_l_run4;
	Bmp* b_l_run5;
	Bmp* b_l_run6;
	// エフェクト
	Bmp* b_blood1;// 血しぶき
	Bmp* b_zan1;
	Bmp* b_zan2;
	Bmp* b_zan3;
	Bmp* hp;
	Bmp* b_clear;

	// プレイヤー（フィールドマップ）
	Bmp* p1_f_r1;// 右
	Bmp* p1_f_r2;
	Bmp* p1_f_r3;
	Bmp* p1_f_l1;// 左
	Bmp* p1_f_l2;
	Bmp* p1_f_l3;
	Bmp* p1_f_u1;// 上
	Bmp* p1_f_u2;
	Bmp* p1_f_u3;
	Bmp* p1_f_d1;// 下
	Bmp* p1_f_d2;
	Bmp* p1_f_d3;
	// 暗転用素材
	Bmp* f_black;

	// 敵キャラ
	Bmp* e_1;
	Bmp* e_0;

	// バトルマップ用画像
	Bmp* c_1;
	Bmp* c_2;
	Bmp* c_3;
	Bmp* c_4;
	Bmp* f_1;// フィールドマップ用
	Bmp* f_2;
	Bmp* f_3;
	Bmp* k_1;
	Bmp* k_2;
	Bmp* k_3;
	Bmp* k_4;
	Bmp* k_kisi;
	Bmp* house;

	// NPCキャラ
	Bmp* npc1_f;

	// タイトル画面
	
	Bmp* titleback;
	Bmp* title_start;
	Bmp* title_exit;

	// メニュー画面
	Bmp* menu_back;
	Bmp* menu_title;
	
	// 背景画像
	Bmp* b2_1_buck;
	Bmp* b2_2_buck;

	// エネミー画像
	Bmp* boss_nomal_l;
	Bmp* boss_nomal_r;
	Bmp* boss_walk_l[6];
	Bmp* boss_walk_r[6];
	Bmp* boss_maho[2];// 魔法弾

	// イベント１
	// テキスト関係
	Bmp* e1_t1[6];
	Bmp* e1_t2[6];
	Bmp* b2_t1[6];
	Bmp* b2_t2[6];
	Bmp* b2_t3[6];
	Bmp* b2_t4[3];
	Bmp* b2_t5[2];
	Bmp* e2_t1[7];
	Bmp* e3_t[8];

	// 立ち絵
	Bmp* tatie_p;
	Bmp* tatie_king;
	Bmp* tatie_maou;
	Bmp* tatie_mob;
	Bmp* tatie_npc;
	Bmp* tatie_kisi;

	Bmp* end[6];
};

struct Key {
	int key_right_O;
	int key_right_N;
	int key_right_T;
	int key_left_O;
	int key_left_N;
	int key_left_T;
	int key_up_O;
	int key_up_N;
	int key_up_T;
	int key_down_O;
	int key_down_N;
	int key_down_T;
	int key_enter_O;
	int key_enter_N;
	int key_enter_T;
	int key_back_O;
	int key_back_N;
	int key_back_T;
	int key_space_O;
	int key_space_N;
	int key_space_T;
	int key_esc_O;
	int key_esc_N;
	int key_esc_T;
};

struct Map {
	int stage_0[16][20];
	int stage_1[16][20];
	int boss2_stage1[16][20];
	// 王都マップ
	int map_4[16][20];
	// 草原マップ
	int map_1[16][20];
	// 森マップ
	int map_7[16][20];
	// 国境マップ
	int map_12[16][20];
};

struct Sound {
	int* bgm[8];
	int* se_jump1;
	int* se_jump2;
	int* se_fire;
	int* se_damage;
	int* se_attack;
};

// 関数定義
void Input(Key*);

void Draw(Player*, Pic*, Map*,Enemy*);

void Update(Player*, Key*, Map*,Enemy*);

void Menu_Draw(Player*,Pic*);
void Menu_Update(Player*, Key*);


// Bmp画像の定義とメモリ破棄
void BmpScan(Player*,Pic*);

// タイトルシーン
void Title_Draw(Player*, Pic*, Map*, Enemy*);
void Title_Update(Player*, Key*, Map*, Enemy*);

// 最初のチュートリアルイベント
void Event1_Draw(Player*, Pic*, Map*, Enemy*);
void Event1_Update(Player*, Key*, Map*, Enemy*);
// バトル（チュートリアル）
void Event2_Draw(Player*, Pic*, Map*, Enemy*);
void Event2_Update(Player*, Key*, Map*, Enemy*);
// チュートリアル
void Event3_Draw(Player*, Pic*, Map*);
void Event3_Update(Player*, Key*, Map*);

//中ボスイベント
void Event4_Draw(Player*, Pic*, Map*);
void Event4_Update(Player*, Key*, Map*);

// 王都マップ関係関数
void Map4_Draw(Player*, Pic*, Map*);
void Map4_Update(Player*, Key*, Map*);

// 草原マップでの戦闘関数
void Battle1_Draw(Player*,Pic*,Map*, Enemy*);
void Battle1_Update(Player*,Key*,Map*,Enemy*);

// 草原マップ関係関数
void Map1_Draw(Player*, Pic*, Map*, Enemy*);
void Map1_Update(Player*, Key*, Map*,Enemy*);

// 森マップ関係関数
void Map7_Draw(Player*, Pic*, Map*, Enemy*);
void Map7_Update(Player*, Key*, Map*, Enemy*);
void Battle7_Draw(Player*, Pic*, Map*, Enemy*);
void Battle7_Update(Player*, Key*, Map*, Enemy*);

// 国境マップ関係関数
void Map13_Draw(Player*, Pic*, Map*);
void Map13_Update(Player*, Key*, Map*,Enemy*);

// ラスボス戦闘関数
void Boss2_1_Draw(Player*, Pic*, Map*, Enemy*);
void Boss2_1_Update(Player*, Key*, Map*, Enemy*);
void Boss2_2_Draw(Player*, Pic*, Map*, Enemy*);
void Boss2_2_Update(Player*, Key*, Map*, Enemy*);
void Boss2_3_Draw(Player*, Pic*, Map*, Enemy*);
void Boss2_3_Update(Player*, Key*, Map*, Enemy*);

void End_Draw(Player*, Pic*);
void End_Update(Player*, Key*);