#include"conioex_New.h"
#include"Game.h"
using namespace std;

// 王都マップ
void Map4_Draw(Player* p, Pic* pic, Map* m) {
    // 初期位置：ｘ＝２８８、ｙ＝９６、
    // 王都マップ
        // 1,2:道, 3:地面, 4:城壁, 5,6:マップ移動箇所, 7:家,8~:会話ポイント
        // 8,9:会話（騎士）,10:NPC1 11,NPC2~
     // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->map_4[y][x]) {
            case 1:
            case 5:
                SetPalette(pic->k_2);
                DrawBmp(x * 32, y * 32, pic->k_2, false);
                break;
            case 2:
            case 6:
                SetPalette(pic->k_3);
                DrawBmp(x * 32, y * 32, pic->k_3, false);
                break;
            case 3:
            case 7:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
            case 14:
            case 15:
                SetPalette(pic->f_1);
                DrawBmp(x * 32, y * 32, pic->f_1, false);
                break;
            case 4:
            case 8:
                SetPalette(pic->k_4);
                DrawBmp(x * 32, y * 32, pic->k_4, false);
                break;
            }

        }
    }

    // NPC描写
    if (true) {
        SetPalette(pic->npc1_f);
        DrawBmp(32, 160, pic->npc1_f, true);
        DrawBmp(64, 384, pic->npc1_f, true);
        DrawBmp(128, 160, pic->npc1_f, true);
        DrawBmp(416, 448, pic->npc1_f, true);
        DrawBmp(448, 160, pic->npc1_f, true);
        DrawBmp(544, 384, pic->npc1_f, true);
        DrawBmp(576, 192, pic->npc1_f, true);
        SetPalette(pic->k_kisi);
        DrawBmp(320, 64, pic->k_kisi, true);
        DrawBmp(288, 64, pic->k_kisi, true);
    }
    // 家
    SetPalette(pic->house);
    DrawBmp(0, 0, pic->house, true);
    DrawBmp(128, 0, pic->house, true);
    DrawBmp(384, 0, pic->house, true);
    DrawBmp(512, 0, pic->house, true);
    DrawBmp(0, 224, pic->house, true);

    DrawBmp(128, 224, pic->house, true);
    DrawBmp(384, 224, pic->house, true);
    DrawBmp(512, 224, pic->house, true);
    // キャラ描写
    // 停止時
    if (p->flug_Move == 0) {
        // 右停止
        if (p->N_x == 1) {
            SetPalette(pic->p1_f_r1);
            DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
        }
        // 左停止
        if (p->N_x == -1) {
            SetPalette(pic->p1_f_l1);
            DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
        }
        // 上停止
        if (p->N_y == -1) {
            SetPalette(pic->p1_f_u1);
            DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
        }
        // 下停止
        if (p->N_y == 1) {
            SetPalette(pic->p1_f_d1);
            DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
        }
    }
    // 移動時
    else if (p->flug_Move == 1) {
        // 右移動
        if (p->N_x == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_r2);
                DrawBmp(p->Left, p->Top, pic->p1_f_r2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_r3);
                DrawBmp(p->Left, p->Top, pic->p1_f_r3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 左移動
        if (p->N_x == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_l2);
                DrawBmp(p->Left, p->Top, pic->p1_f_l2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_l3);
                DrawBmp(p->Left, p->Top, pic->p1_f_l3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 上移動
        if (p->N_y == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_u2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_u3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 下移動
        if (p->N_y == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_d2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_d3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }
    }

    // テキスト
    if (p->text[0] == 1) {
        // テキストボックスの描写
        SetPalette(pic->textbox);
        DrawBmp(0, 352, pic->textbox, false);
        if (p->text[1] > 0) {
            // キャラアイコン
            SetPalette(pic->tatie_npc);
            DrawBmp(10, 362, pic->tatie_npc, true);
        }
        else {
            // キャラアイコン
            SetPalette(pic->tatie_kisi);
            DrawBmp(10, 362, pic->tatie_kisi, true);
        }
        // テキストの描写
        SetPalette(pic->e3_t[p->text[1]]);
        DrawBmp(160, 352, pic->e3_t[p->text[1]], true);
    }

    PrintFrameBuffer();

    return;


}
void Map4_Update(Player* p, Key* k, Map* m) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[3], true);
        p->bgm_t = 0;
    }
    //　キャラが今いるマップ座標の更新
    p->F_x = (p->Left + p->Right) / 64;
    p->F_y = (p->Top + p->Bottom) / 64;

    if (m->map_4[p->F_y][p->F_x] == 5 ||
        m->map_4[p->F_y][p->F_x] == 4) {
        p->changemap[0] = 1;
        p->changemap[1] = 5;
        p->N_x = 0;
        p->N_y = 1;
        p->Left = 288;
        p->Right = 319;
        p->Top = 32;
        p->Bottom = 63;

        p->ani_cnt = 0;
        p->flug_Move = 0;
        p->bgm_t = 1;
    }

    // 移動
    if (p->flug_changeBattle != 1) {

        // 右移動
        if (k->key_right_N == 1 && p->flug_Move == 0) {
            // 方向の指定
            p->N_x = 1;
            p->N_y = 0;
            // 進む先に障害物があるか判定
            if (m->map_4[p->Top / 32][(p->Left / 32) + 1] == 1 ||
                m->map_4[p->Top / 32][(p->Left / 32) + 1] == 2 ||
                m->map_4[p->Top / 32][(p->Left / 32) + 1] == 3 ||
                m->map_4[p->Top / 32][(p->Left / 32) + 1] == 5 ||
                m->map_4[p->Top / 32][(p->Left / 32) + 1] == 6) {

                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 1;
                p->N_y = 0;
            }
        }
        // 左移動
        else if (k->key_left_N == 1 && p->flug_Move == 0) {
            //方向の指定
            p->N_x = -1;
            p->N_y = 0;
            // 進む先に障害物があるか判定
            if (m->map_4[p->Top / 32][(p->Left / 32) - 1] == 1 ||
                m->map_4[p->Top / 32][(p->Left / 32) - 1] == 2 ||
                m->map_4[p->Top / 32][(p->Left / 32) - 1] == 3 ||
                m->map_4[p->Top / 32][(p->Left / 32) - 1] == 5 ||
                m->map_4[p->Top / 32][(p->Left / 32) - 1] == 6) {
                // 移動フラグON
                p->flug_Move = 1;
                //方向の指定
                p->N_x = -1;
                p->N_y = 0;
            }
        }
        // 上移動
        else if (k->key_up_N == 1 && p->flug_Move == 0) {
            // 方向の指定
            p->N_x = 0;
            p->N_y = -1;
            // 進む先に障害物があるか判定
            if (m->map_4[(p->Top / 32) - 1][p->Left / 32] == 1 ||
                m->map_4[(p->Top / 32) - 1][p->Left / 32] == 2 ||
                m->map_4[(p->Top / 32) - 1][p->Left / 32] == 3 ||
                m->map_4[(p->Top / 32) - 1][p->Left / 32] == 5 ||
                m->map_4[(p->Top / 32) - 1][p->Left / 32] == 6) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = -1;
            }
        }
        // 下移動
        else if (k->key_down_N == 1 && p->flug_Move == 0) {
            // 方向の指定
            p->N_x = 0;
            p->N_y = 1;
            // 進む先に障害物があるか判定
            if (m->map_4[(p->Top / 32) + 1][p->Left / 32] == 1 ||
                m->map_4[(p->Top / 32) + 1][p->Left / 32] == 2 ||
                m->map_4[(p->Top / 32) + 1][p->Left / 32] == 3 ||
                m->map_4[(p->Top / 32) + 1][p->Left / 32] == 5 ||
                m->map_4[(p->Top / 32) + 1][p->Left / 32] == 6) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = 1;
            }
        }


        // 移動処理
        if (p->flug_Move == 1) {
            // 上移動時
            if (p->N_x == 0 && p->N_y == -1) {
                p->Top -= 2;
                p->Bottom -= 2;
            }
            // 下移動時
            else if (p->N_x == 0 && p->N_y == 1) {
                p->Top += 2;
                p->Bottom += 2;
            }
            // 右移動時
            else if (p->N_x == 1 && p->N_y == 0) {
                p->Right += 2;
                p->Left += 2;
            }
            // 左移動時
            else if (p->N_x == -1 && p->N_y == 0) {
                p->Right -= 2;
                p->Left -= 2;
            }

        }
    }

    // 会話
    // 各方向に
    // 右
    if (p->N_x == 1) {
        if (m->map_4[p->F_y][p->F_x+1] >= 8 ) {
            p->text[0] = 1;
            switch (m->map_4[p->F_y][p->F_x + 1]) {
            case 8:
                p->text[1] = 0;
                break;
            case 9:
                p->text[1] = 1;
                break;
            case 10:
                p->text[1] = 2;
                break;
            case 11:
                p->text[1] = 3;
                break;
            case 12:
                p->text[1] = 4;
                break;
            case 13:
                p->text[1] = 5;
                break;
            case 14:
                p->text[1] = 6;
                break;
            case 15:
                p->text[1] = 7;
                break;
            }
        }
        else {
            p->text[0] = 0;
        }
    }
    // 左
    else if (p->N_x == -1) {
        if (m->map_4[p->F_y][p->F_x - 1] >= 8) {
            p->text[0] = 1;
            switch (m->map_4[p->F_y][p->F_x - 1]) {
            case 8:
                p->text[1] = 0;
                break;
            case 9:
                p->text[1] = 1;
                break;
            case 10:
                p->text[1] = 2;
                break;
            case 11:
                p->text[1] = 3;
                break;
            case 12:
                p->text[1] = 4;
                break;
            case 13:
                p->text[1] = 5;
                break;
            case 14:
                p->text[1] = 6;
                break;
            case 15:
                p->text[1] = 7;
                break;
                break;
            }
        }
        else {
            p->text[0] = 0;
        }
    }
    // 上
    else if (p->N_y == 1) {
        if (m->map_4[p->F_y+1][p->F_x] >= 8) {
            p->text[0] = 1;
            switch (m->map_4[p->F_y+1][p->F_x]) {
            case 8:
                p->text[1] = 0;
                break;
            case 9:
                p->text[1] = 1;
                break;
            case 10:
                p->text[1] = 2;
                break;
            case 11:
                p->text[1] = 3;
                break;
            case 12:
                p->text[1] = 4;
                break;
            case 13:
                p->text[1] = 5;
                break;
            case 14:
                p->text[1] = 6;
                break;
            case 15:
                p->text[1] = 7;
                break;
                break;
            }
        }
        else {
            p->text[0] = 0;
        }
    }
    // 下
    else if (p->N_y == -1) {
        if (m->map_4[p->F_y-1][p->F_x] >= 8) {
            p->text[0] = 1;
            switch (m->map_4[p->F_y-1][p->F_x]) {
            case 8:
                p->text[1] = 0;
                break;
            case 9:
                p->text[1] = 1;
                break;
            case 10:
                p->text[1] = 2;
                break;
            case 11:
                p->text[1] = 3;
                break;
            case 12:
                p->text[1] = 4;
                break;
            case 13:
                p->text[1] = 5;
                break;
            case 14:
                p->text[1] = 6;
                break;
            case 15:
                p->text[1] = 7;
                break;
            }
        }
        else {
            p->text[0] = 0;
        }
    }
    


}

// 草原マップ
void Map1_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->map_1[y][x]) {
            case 1:
            case 5:
                SetPalette(pic->f_1);
                DrawBmp(x * 32, y * 32, pic->f_1, false);
                break;
            case 2:
                SetPalette(pic->f_2);
                DrawBmp(x * 32, y * 32, pic->f_2, false);
                break;
            case 3:
                SetPalette(pic->f_3);
                DrawBmp(x * 32, y * 32, pic->f_3, false);
                break;
            }

        }
    }
    // キャラ描写
    if (p->flug_Move == 0) {
        // 右停止
        if (p->N_x == 1) {
            SetPalette(pic->p1_f_r1);
            DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
        }
        // 左停止
        if (p->N_x == -1) {
            SetPalette(pic->p1_f_l1);
            DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
        }
        // 上停止
        if (p->N_y == -1) {
            SetPalette(pic->p1_f_u1);
            DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
        }
        // 下停止
        if (p->N_y == 1) {
            SetPalette(pic->p1_f_d1);
            DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
        }
    }
    else if(p->flug_Move == 1) {
        // 右移動
        if (p->N_x == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_r2);
                DrawBmp(p->Left, p->Top, pic->p1_f_r2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_r3);
                DrawBmp(p->Left, p->Top, pic->p1_f_r3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 左移動
        if (p->N_x == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_l2);
                DrawBmp(p->Left, p->Top, pic->p1_f_l2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_l3);
                DrawBmp(p->Left, p->Top, pic->p1_f_l3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 上移動
        if (p->N_y == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_u2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_u3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 下移動
        if (p->N_y == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_d2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_d3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }
    }
    // 戦闘画面突入演出
    if (p->flug_changeBattle == 1) {
        for (int i = 0; i < p->change_cnt; i++) {
            for (int y = 0; y < p->change_cnt-i; y++) {
                SetPalette(pic->f_black);
                DrawBmp(i * 32, y * 32, pic->f_black, false);
            }
        }
    }

    PrintFrameBuffer();

    return;
}

void Map1_Update(Player* p, Key* k, Map* m,Enemy* e) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[4], true);
        p->bgm_t = 0;
    }
    //　キャラが今いるマップ座標の更新
    p->F_x = (p->Left + p->Right) / 64;
    p->F_y = (p->Top + p->Bottom) / 64;

    // 敵との遭遇判定
    if (p->flug_Move_finish == 1 && m->map_1[p->F_y][p->F_x] != 5) {

        p->flug_Move_finish = 0;

        int x = rand() % 100 + 1;

        if (1<= x && x <= 15) {
            p->flug_changeBattle = 1;
            p->change_cnt = 0;
        }
    }
    // 移動
    if (p->flug_changeBattle != 1) {

        // 右移動
        if (k->key_right_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_1[p->Top / 32][(p->Left / 32) + 1] != 3) {

                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 1;
                p->N_y = 0;
            }
        }
        // 左移動
        else if (k->key_left_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_1[p->Top / 32][(p->Left / 32) - 1] != 3 ) {
                // 移動フラグON
                p->flug_Move = 1;
                //方向の指定
                p->N_x = -1;
                p->N_y = 0;
            }
        }
        // 上移動
        else if (k->key_up_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_1[(p->Top / 32) - 1][p->Left / 32] != 3) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = -1;
            }
        }
        // 下移動
        else if (k->key_down_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_1[(p->Top / 32) + 1][p->Left / 32] != 3 ) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = 1;
            }
        }


        // 移動処理
        if (p->flug_Move == 1) {
            // 上移動時
            if (p->N_x == 0 && p->N_y == -1) {
                p->Top -= 2;
                p->Bottom -= 2;
            }
            // 下移動時
            else if (p->N_x == 0 && p->N_y == 1) {
                p->Top += 2;
                p->Bottom += 2;
            }
            // 右移動時
            else if (p->N_x == 1 && p->N_y == 0) {
                p->Right += 2;
                p->Left += 2;
            }
            // 左移動時
            else if (p->N_x == -1 && p->N_y == 0) {
                p->Right -= 2;
                p->Left -= 2;
            }

        }
    }
    // 戦闘突入初期化
    else {
        p->change_cnt++;
        if (p->change_cnt>36) {
            p->beforeMap = p->nowMap;
            p->nowMap = 6;// 戦闘マップに移動
            p->flug_changeBattle = 0;
            e->enemy[1][0] = e->enemy[1][7];
            e->now_enemy = 1;
            p->B_Left = 64;
            p->B_Right = 127;
            p->B_Top = 384;
            p->B_Bottom = 447;
            p->B_x = 1;
            e->flug_enemy = 1;
            e->e_cnt = 1;
            e->enemy[e->now_enemy][2] = 575;
            e->enemy[e->now_enemy][3] = 639;
            e->enemy[e->now_enemy][4] = 384;
            e->enemy[e->now_enemy][5] = 447;
        }
    }

    // マップ移動
    if (m->map_1[p->F_y][p->F_x] == 5) {
        p->bgm_t = 1;
        // 王国マップ
        if (p->F_x < 12 && p->F_y < 3) {
            p->changemap[0] = 1;
            p->changemap[1] = 4;
            p->N_x = 0;
            p->N_y = -1;
            p->Left = 288;
            p->Right = 319;
            p->Top = 480;
            p->Bottom = 511;

            p->ani_cnt = 0;
            p->flug_Move = 0;
            p->bgm_t = 1;
        }
        // 森マップ
        if (p->F_x > 12) {
            p->changemap[0] = 1;
            p->changemap[1] = 7;
            p->N_x = 1;
            p->N_y = 0;
            p->Left = 32;
            p->Right = 63;
            p->Top = 448;
            p->Bottom = 479;

            p->ani_cnt = 0;
            p->flug_Move = 0;
            p->text[1] = 0;
            p->text[0] = 0;
            p->bgm_t = 1;

        }
        // 国境マップ
        if (p->F_x < 12 && p->F_y > 10) {
            p->changemap[0] = 1;
            p->changemap[1] = 13;
            p->N_x = 0;
            p->N_y = 1;
            p->Left = 288;
            p->Right = 319;
            p->Top = 448;
            p->Bottom = 479;

            p->ani_cnt = 0;
            p->flug_Move = 0;
            p->bgm_t = 1;
        }
    }


    return;
}

// 森マップ
void Map7_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->map_7[y][x]) {
            case 1:
            case 5:
            case 6:
                SetPalette(pic->f_1);
                DrawBmp(x * 32, y * 32, pic->f_1, false);
                break;
            case 2:
                SetPalette(pic->f_2);
                DrawBmp(x * 32, y * 32, pic->f_2, false);
                break;
            case 3:
                SetPalette(pic->f_3);
                DrawBmp(x * 32, y * 32, pic->f_3, false);
                break;
            }

        }
    }
    // キャラ描写
    if (p->flug_Move == 0) {
        // 右停止
        if (p->N_x == 1) {
            SetPalette(pic->p1_f_r1);
            DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
        }
        // 左停止
        if (p->N_x == -1) {
            SetPalette(pic->p1_f_l1);
            DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
        }
        // 上停止
        if (p->N_y == -1) {
            SetPalette(pic->p1_f_u1);
            DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
        }
        // 下停止
        if (p->N_y == 1) {
            SetPalette(pic->p1_f_d1);
            DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
        }
    }
    else if (p->flug_Move == 1) {
        // 右移動
        if (p->N_x == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_r2);
                DrawBmp(p->Left, p->Top, pic->p1_f_r2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_r3);
                DrawBmp(p->Left, p->Top, pic->p1_f_r3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 左移動
        if (p->N_x == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_l2);
                DrawBmp(p->Left, p->Top, pic->p1_f_l2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_l3);
                DrawBmp(p->Left, p->Top, pic->p1_f_l3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 上移動
        if (p->N_y == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_u2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_u3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 下移動
        if (p->N_y == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_d2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_d3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }
    }
    // 戦闘画面突入演出
    if (p->flug_changeBattle == 1) {
        for (int i = 0; i < p->change_cnt; i++) {
            for (int y = 0; y < p->change_cnt - i; y++) {
                SetPalette(pic->f_black);
                DrawBmp(i * 32, y * 32, pic->f_black, false);
            }
        }
    }
    if (p->text[0] == 1) {
        // テキストボックスの描写
        SetPalette(pic->textbox);
        DrawBmp(0, 352, pic->textbox, false);
        // テキストの描写
        SetPalette(pic->e2_t1[p->text[1]]);
        DrawBmp(160, 352, pic->e2_t1[p->text[1]], true);
        // 立ち絵
        SetPalette(pic->tatie_p);
        DrawBmp(10, 362, pic->tatie_p, true);
    }

    PrintFrameBuffer();

    return;
}

void Map7_Update(Player* p, Key* k, Map* m, Enemy* e) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[5], true);
        p->bgm_t = 0;
    }
    //　キャラが今いるマップ座標の更新
    p->F_x = (p->Left + p->Right) / 64;
    p->F_y = (p->Top + p->Bottom) / 64;

    // 敵との遭遇判定
    if (p->flug_Move_finish == 1 && 
        (m->map_7[p->F_y][p->F_x] == 1 || m->map_7[p->F_y][p->F_x] == 2)) {

        p->flug_Move_finish = 0;

        int x = rand() % 100 + 1;

        if (1 <= x && x <= 15) {
            p->flug_changeBattle = 1;
            p->change_cnt = 0;
        }
    }
    // 移動
    if (p->flug_changeBattle != 1) {

        // 右移動
        if (k->key_right_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_7[p->Top / 32][(p->Left / 32) + 1] != 3) {

                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 1;
                p->N_y = 0;
            }
        }
        // 左移動
        else if (k->key_left_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_7[p->Top / 32][(p->Left / 32) - 1] != 3) {
                // 移動フラグON
                p->flug_Move = 1;
                //方向の指定
                p->N_x = -1;
                p->N_y = 0;
            }
        }
        // 上移動
        else if (k->key_up_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_7[(p->Top / 32) - 1][p->Left / 32] != 3) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = -1;
            }
        }
        // 下移動
        else if (k->key_down_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_7[(p->Top / 32) + 1][p->Left / 32] != 3) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = 1;
            }
        }


        // 移動処理
        if (p->flug_Move == 1) {
            // 上移動時
            if (p->N_x == 0 && p->N_y == -1) {
                p->Top -= 2;
                p->Bottom -= 2;
            }
            // 下移動時
            else if (p->N_x == 0 && p->N_y == 1) {
                p->Top += 2;
                p->Bottom += 2;
            }
            // 右移動時
            else if (p->N_x == 1 && p->N_y == 0) {
                p->Right += 2;
                p->Left += 2;
            }
            // 左移動時
            else if (p->N_x == -1 && p->N_y == 0) {
                p->Right -= 2;
                p->Left -= 2;
            }

        }
    }
    // 戦闘突入初期化
    else {
        p->change_cnt++;
        if (p->change_cnt > 36) {
            p->beforeMap = p->nowMap;
            p->nowMap = 6;// 戦闘マップに移動
         
            p->flug_changeBattle = 0;
            e->enemy[1][0] = e->enemy[1][7];
            e->now_enemy = 1;
            p->B_Left = 64;
            p->B_Right = 127;
            p->B_Top = 384;
            p->B_Bottom = 447;
            p->B_x = 1;
            e->flug_enemy = 1;
            e->e_cnt = 1;
            e->enemy[e->now_enemy][2] = 575;
            e->enemy[e->now_enemy][3] = 639;
            e->enemy[e->now_enemy][4] = 384;
            e->enemy[e->now_enemy][5] = 447;
        }
    }

    // マップ移動
    // 平原マップ
    if (m->map_7[p->F_y][p->F_x] == 5) {
       
            p->changemap[0] = 1;
            p->changemap[1] = 5;
            p->N_x = -1;
            p->N_y = 0;
            p->Left = 576;
            p->Right = 607;
            p->Top = 224;
            p->Bottom = 255;

            p->ani_cnt = 0;
            p->flug_Move = 0;
            p->bgm_t = 1;
    }
    // 村マップ
    if (m->map_7[p->F_y][p->F_x] == 6) {

        p->changemap[0] = 1;
        p->changemap[1] = 10;
        p->N_x = -1;
        p->N_y = 0;
        p->Left = 32;
        p->Right = 63;
        p->Top = 224;
        p->Bottom = 255;

        p->ani_cnt = 0;
        p->flug_Move = 0;
    }

    if ((m->map_7[p->F_y][p->F_x] == 2)
        && p->flug_event[1] == 0) {
        p->text[0] = 1;
        p->flug_event[1] = 1;
    }

    if (p->text[0] == 1) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
    }
    if (p->text[1] >= 7) {
        p->text[0] = 0;
        p->text[1] = 0;
        
    }

    return;
}

// 国境マップ
void Map13_Draw(Player* p, Pic* pic, Map* m) {
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->map_12[y][x]) {
            case 0:
            case 7:
                SetPalette(pic->k_1);
                DrawBmp(x * 32, y * 32, pic->k_1, false);
                break;
            case 1:
            case 5:
            case 8:
                SetPalette(pic->k_2);
                DrawBmp(x * 32, y * 32, pic->k_2, false);
                break;
            case 2:
            case 6:
            case 9:
                SetPalette(pic->k_3);
                DrawBmp(x * 32, y * 32, pic->k_3, false);
                break;
            case 3:
                SetPalette(pic->k_4);
                DrawBmp(x * 32, y * 32, pic->k_4, false);
                break;
            }

        }
    }
    // キャラ描写
    // 停止時
    if (p->flug_Move == 0) {
        // 右停止
        if (p->N_x == 1) {
            SetPalette(pic->p1_f_r1);
            DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
        }
        // 左停止
        if (p->N_x == -1) {
            SetPalette(pic->p1_f_l1);
            DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
        }
        // 上停止
        if (p->N_y == -1) {
            SetPalette(pic->p1_f_u1);
            DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
        }
        // 下停止
        if (p->N_y == 1) {
            SetPalette(pic->p1_f_d1);
            DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
        }
    }
    // 移動時
    else if (p->flug_Move == 1) {
        // 右移動
        if (p->N_x == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_r2);
                DrawBmp(p->Left, p->Top, pic->p1_f_r2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_r3);
                DrawBmp(p->Left, p->Top, pic->p1_f_r3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_r1);
                DrawBmp(p->Left, p->Top, pic->p1_f_r1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 左移動
        if (p->N_x == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_l2);
                DrawBmp(p->Left, p->Top, pic->p1_f_l2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_l3);
                DrawBmp(p->Left, p->Top, pic->p1_f_l3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_l1);
                DrawBmp(p->Left, p->Top, pic->p1_f_l1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 上移動
        if (p->N_y == -1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_u2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_u3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_u1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }

        // 下移動
        if (p->N_y == 1) {
            switch (p->ani_data_1[p->ani_cnt]) {
            case 1:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt++;
                break;
            case 2:
                SetPalette(pic->p1_f_u2);
                DrawBmp(p->Left, p->Top, pic->p1_f_d2, true);
                p->ani_cnt++;
                break;
            case 3:
                SetPalette(pic->p1_f_u3);
                DrawBmp(p->Left, p->Top, pic->p1_f_d3, true);
                p->ani_cnt++;
                break;
            case 0xff:
                SetPalette(pic->p1_f_u1);
                DrawBmp(p->Left, p->Top, pic->p1_f_d1, true);
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->flug_Move_finish = 1;
                break;
            }
        }
    }

    // 騎士描写
    if (true) {
        SetPalette(pic->k_kisi);
        DrawBmp(288, 192, pic->k_kisi, true);
        DrawBmp(320, 192, pic->k_kisi, true);
    }

    PrintFrameBuffer();

    return;


}

void Map13_Update(Player* p, Key* k, Map* m,Enemy* e) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[4], true);
        p->bgm_t = 0;
    }
    //　キャラが今いるマップ座標の更新
    p->F_x = (p->Left + p->Right) / 64;
    p->F_y = (p->Top + p->Bottom) / 64;

    // 移動
    if (p->flug_changeBattle != 1) {

        // 右移動
        if (k->key_right_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_12[p->Top / 32][(p->Left / 32) + 1] != 3 &&
                m->map_12[p->Top / 32][(p->Left / 32) + 1] != 7) {

                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 1;
                p->N_y = 0;
            }
        }
        // 左移動
        else if (k->key_left_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_12[p->Top / 32][(p->Left / 32) - 1] != 3 &&
                m->map_12[p->Top / 32][(p->Left / 32) - 1] != 7) {
                // 移動フラグON
                p->flug_Move = 1;
                //方向の指定
                p->N_x = -1;
                p->N_y = 0;
            }
        }
        // 上移動
        else if (k->key_up_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_12[(p->Top / 32) - 1][p->Left / 32] != 3 &&
                m->map_12[(p->Top / 32) - 1][p->Left / 32] != 7) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = -1;
            }
        }
        // 下移動
        else if (k->key_down_N == 1 && p->flug_Move == 0) {
            // 進む先に障害物があるか判定
            if (m->map_12[(p->Top / 32) + 1][p->Left / 32] != 3 &&
                m->map_12[(p->Top / 32) + 1][p->Left / 32] != 7) {
                // 移動フラグON
                p->flug_Move = 1;
                // 方向の指定
                p->N_x = 0;
                p->N_y = 1;
            }
        }


        // 移動処理
        if (p->flug_Move == 1) {
            // 上移動時
            if (p->N_x == 0 && p->N_y == -1) {
                p->Top -= 2;
                p->Bottom -= 2;
            }
            // 下移動時
            else if (p->N_x == 0 && p->N_y == 1) {
                p->Top += 2;
                p->Bottom += 2;
            }
            // 右移動時
            else if (p->N_x == 1 && p->N_y == 0) {
                p->Right += 2;
                p->Left += 2;
            }
            // 左移動時
            else if (p->N_x == -1 && p->N_y == 0) {
                p->Right -= 2;
                p->Left -= 2;
            }

        }
    }
    
    // 会話
    // マップ移動
    if (m->map_12[p->F_y][p->F_x] == 5 ||
        m->map_12[p->F_y][p->F_x] == 6) {
        // 草原マップ
        p->changemap[0] = 1;
        p->changemap[1] = 5;
        p->N_x = 0;
        p->N_y = 1;
        p->Left = 288;
        p->Right = 319;
        p->Top = 448;
        p->Bottom = 479;
        p->bgm_t = 1;

        p->ani_cnt = 0;
        p->flug_Move = 0;
    }
    if (m->map_12[p->F_y][p->F_x] == 8 ||
        m->map_12[p->F_y][p->F_x] == 9) {
        // マップ
        p->changemap[0] = 1;
        p->changemap[1] = 18;
        p->N_x = 0;
        p->N_y = 1;
        p->Left = 288;
        p->Right = 319;
        p->Top = 448;
        p->Bottom = 479;

        p->text[0] = 1;
        p->text[1] = 0;
        p->ani_cnt = 0;
        p->flug_Move = 0;
        p->Hp = p->HpMax;
        p->B_Left = 64;
        p->B_Right = 127;
        p->B_Top = 384;
        p->B_Bottom = 447;
        p->B_x = 1;
        e->flug_enemy = 1;
        e->e_cnt = 1;
        e->now_enemy = 3;
        p->bgm_t = 1;
        e->enemy[e->now_enemy][0] = e->enemy[e->now_enemy][7];
    }
    return;

}