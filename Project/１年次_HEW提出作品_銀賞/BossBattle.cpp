#include"conioex_New.h"
#include"Game.h"
using namespace std;

// ラスボス一戦目
void Boss2_1_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {

    // 背景描写
    SetPalette(pic->b2_1_buck);
    DrawBmp(0, 0, pic->b2_1_buck, true);
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->boss2_stage1[y][x]) {
            case 1:
                SetPalette(pic->c_4);
                DrawBmp(x * 32, y * 32, pic->c_4, true);
                break;
            }

        }
    }
    // 敵描写
    if (e->flug_enemy == 1) {
        if (e->flug_e_walk == 1) {
            if (e->enemy[e->now_enemy][6] == -1) {
                SetPalette(pic->boss_walk_l[e->anime[e->e_anime_cnt]]);
                DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_walk_l[e->anime[e->e_anime_cnt]], true);
            }
            else {
                SetPalette(pic->boss_walk_r[e->anime[e->e_anime_cnt]]);
                DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_walk_r[e->anime[e->e_anime_cnt]], true);
            }
        }
        else {
            SetPalette(pic->boss_nomal_l);
            DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_nomal_l, true);
        }
        // ダメージエフェクト
        if (e->flug_damage == 1) {
            if (p->ani_cnt2 < 2) {
                switch (p->B_x) {
                case 1:
                    e->blood_x = 10;
                    break;
                case -1:
                    e->blood_x = -10;
                    break;
                }
            }
            SetPalette(pic->b_blood1);
            DrawBmp(e->enemy[e->now_enemy][2] + e->blood_x, e->enemy[e->now_enemy][4], pic->b_blood1, true);
            if (p->ani_cnt2 > 3) {
                e->flug_damage = 0;
            }
        }
    }
    // プレイヤー描写
    // 無敵状態の確認
    if (p->flug_damage == 1 && (p->muteki_cnt/2)%2 == 1) {
        if (p->ani_data_2[p->ani_cnt] == 0xff) {
            p->ani_cnt = 0;
        }
    }
    else {
        // 待機・走り・ジャンプ・抜刀の判定
        // 走り
        if (p->flug_Move == 1) {
            if (p->ani_data_2[p->ani_cnt] == 0xff) {
                p->ani_cnt = 0;
            }

            // 右に向かって走る
            if (p->B_x == 1) {
                SetPalette(pic->b_r_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r_run[p->ani_data_2[p->ani_cnt]], true);
            }
            // 左に向かって走る
            else if (p->B_x == -1) {
                SetPalette(pic->b_l_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l_run[p->ani_data_2[p->ani_cnt]], true);
            }
        }
        // 待機時
        else {
            //向きによってキャラを描写
            if (p->B_x == 1) {
                SetPalette(pic->b_r);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r, true);
            }
            else if (p->B_x == -1) {
                SetPalette(pic->b_l);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l, true);
            }
        }
    }

    // 斬撃エフェクト描写
    // 斬撃
    if (p->flug_Zan == 1 && p->ani_cnt2 < 8) {
        switch (p->ani_data_3[p->ani_cnt2]) {
        case 0:
            p->zan_y = p->B_Top;
            if (p->B_x == 1) {
                p->zan_x = p->B_Left + 24;
            }
            else if (p->B_x == -1) {
                p->zan_x = p->B_Left - 24;
            }
            p->ani_cnt2++;
            break;
        case 1:
            SetPalette(pic->b_zan1);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan1, true);
            p->ani_cnt2++;
            break;
        case 2:
            SetPalette(pic->b_zan2);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan2, true);
            p->ani_cnt2++;
            break;
        case 3:
            SetPalette(pic->b_zan3);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan3, true);
            p->ani_cnt2++;
            break;
        case 0xff:

            break;
        }
    }
    // その他各種
    // HP表示
    for (int i = 0; i < p->Hp; i++) {
        SetPalette(pic->hp);
        DrawBmp(i * 32, 0, pic->hp, true);
    }

    // 戦闘前会話文
    if (p->flug_event[2] == 0) {
        if (p->text[0] == 1) {
            // テキストボックスの描写
            SetPalette(pic->textbox);
            DrawBmp(0, 352, pic->textbox, false);
            // テキストの描写
            SetPalette(pic->b2_t1[p->text[1]]);
            DrawBmp(160, 352, pic->b2_t1[p->text[1]], true);
            // キャラアイコン
            switch (p->text[1]) {
            case 0:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 1:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 2:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 3:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 4:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 5:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            }

        }
        // 戦闘画面突入演出
        if (p->text[1] > 5) {
            
            for (int i = 0; i < p->change_cnt; i++) {
                for (int y = 0; y < p->change_cnt - i; y++) {
                    SetPalette(pic->f_black);
                    DrawBmp(i * 32, y * 32, pic->f_black, false);
                }
            }
        }

    }
    // 戦闘終了後会話文
    if (e->flug_enemy == 0) {
        if (p->text[0] == 1) {
            // テキストボックスの描写
            SetPalette(pic->textbox);
            DrawBmp(0, 352, pic->textbox, false);
            // テキストの描写
            SetPalette(pic->b2_t2[p->text[1]]);
            DrawBmp(160, 352, pic->b2_t2[p->text[1]], true);
            // キャラアイコン
            switch (p->text[1]) {
            case 0:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 1:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 2:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 3:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 4:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 5:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            }
        }
        // 戦闘画面突入演出
        if (p->text[1] > 5) {

            for (int i = 0; i < p->change_cnt; i++) {
                for (int y = 0; y < p->change_cnt - i; y++) {
                    SetPalette(pic->f_black);
                    DrawBmp(i * 32, y * 32, pic->f_black, false);
                }
            }
        }
    }
    PrintFrameBuffer();
}
void Boss2_1_Update(Player* p, Key* k, Map* m, Enemy* e) {
    if (p->bgm_t == 1) {
        MciPlaySound(p->bgm[6], true);
        p->bgm_t = 0;
    }
    // 戦闘前イベント
    if (p->flug_event[2] == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 5) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->flug_event[2] = 1;
                p->change_cnt = 0;
            }
        }

    }
    // 敵を倒した時の処理
    else if (e->flug_enemy == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 5) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->text[0] = 1;
                p->flug_event[2] = 1;
                p->change_cnt = 0;
                p->changemap[0] = 1;
                p->changemap[1] = 19;
                p->ani_cnt = 0;
                p->flug_Move = 0;
                e->flug_enemy = 1;
                e->now_enemy = 4;
                e->e_anime_cnt = 0;
                e->flug_e_walk = 0;
                e->next_maho = 0;
                e->now_maho = 0;
                e->mahodan[0][0] = 0;
                e->mahodan[1][0] = 0;
                e->mahodan[2][0] = 0;
                e->mahodan[3][0] = 0;
                e->mahodan[4][0] = 0;
                // 主人公位置
                p->bgm_t = 1;
                MciStopSound(p->bgm[6]);
                e->enemy[e->now_enemy][0] = e->enemy[e->now_enemy][7];
            }
        }
    }
    // プレイヤーが死んだ時の処理
    else if (p->Hp <= 0) {
        p->bgm_t = 1;
        MciStopSound(p->bgm[6]);
        // エンディング分岐
        // 隠しエンディング
        if (p->flug_event[1] == 1) {
            p->end_number = 6;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
        // エンディング3
        else {
            p->end_number = 3;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
    }
    // 戦い中の処理
    else{
        // プレイヤーの中心座標更新
        p->Center[0] = (p->B_Left + p->B_Right) / 2;// x座標
        p->Center[1] = (p->B_Top + p->B_Bottom) / 2;// y座標

        // プレイヤーの動き
        // 右移動
        if (k->key_right_N == 1) {
            //座標の加算
            p->B_Left += 3;
            p->B_Right += 3;
            // ani_cntの加算
            p->ani_cnt++;
            // 方向の指定
            p->B_x = 1;
            // フラグのON
            p->flug_Move = 1;
        }
        // 左移動
        else if (k->key_left_N == 1) {
            //座標の加算
            p->B_Left -= 3;
            p->B_Right -= 3;
            // ani_cntの加算
            p->ani_cnt++;
            //方向の指定
            p->B_x = -1;
            // フラグのON
            p->flug_Move = 1;
        }
        else {
            // フラグのOFF
            p->flug_Move = 0;
        }
        // ジャンプ
        if (k->key_space_T == 1 && p->flug_Ground == 1) {
            p->flug_Jump = 1;
            p->flug_Ground = 0;
            p->JumpCount = 0;
            p->FallCount = 0;
            MciPlaySound(p->se_jump1, false);
        }
        // ジャンプ中
        if (p->flug_Jump == 1) {

            switch (p->JumpCount) {
            case 0:
            case 1:
            case 2:
                p->B_Bottom -= 15;
                p->B_Top -= 15;
                p->JumpCount++;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                p->B_Bottom -= 10;
                p->B_Top -= 10;
                p->JumpCount++;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                p->B_Bottom -= 7;
                p->B_Top -= 7;
                p->JumpCount++;
                break;
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                p->B_Bottom -= 4;
                p->B_Top -= 4;
                p->JumpCount++;
                break;
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
                p->B_Bottom -= 2;
                p->B_Top -= 2;
                p->JumpCount++;
                break;
            case 40:
                p->flug_Jump = 0;
                break;
            }

        }


        // 敵の動き
        // 一定コマごとにプレイヤーの位置を判断して追いかける
        e->e_cnt++;
        if (e->e_cnt % 5 == 0) {
            // プレイヤーの右側に敵がいるとき
            if ((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2 > p->Center[0]) {
                e->enemy[e->now_enemy][6] = -1;
            }
            // プレイヤーの左側に敵がいるとき
            else if ((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2 < p->Center[0]) {
                e->enemy[e->now_enemy][6] = 1;
            }
        }
        if (e->enemy[e->now_enemy][6] == 1) {
            e->enemy[e->now_enemy][2] += 1;
            e->enemy[e->now_enemy][3] += 1;
            e->e_anime_cnt++;
            e->flug_e_walk = 1;
        }
        else {
            e->enemy[e->now_enemy][2] -= 1;
            e->enemy[e->now_enemy][3] -= 1;
            e->e_anime_cnt++;
            e->flug_e_walk = 1;
        }

        if (e->anime[e->e_anime_cnt] == 0xff) {
            e->e_anime_cnt = 0;
        }

        // 敵との接触判定
            // 無敵状態かの判定
        if (p->flug_damage == 0) {
            // プレイヤーのBottomが範囲内かつ、プレイヤーのCenter[0]が範囲内
            if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 &&
                ((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                // プレイヤーのHPを減らす
                p->Hp -= e->enemy[e->now_enemy][1];
                // 無敵状態のフラグを上げる
                p->flug_damage = 1;
                MciPlaySound(p->se_damage, false);
            }
        }

        // 無敵状態のカウント処理
        if (p->flug_damage == 1) {
            p->muteki_cnt++;
            if (p->muteki_cnt > 30) {
                p->flug_damage = 0;
                p->muteki_cnt = 0;
            }
        }

        // 斬撃
        if (k->key_enter_T == 1 && p->flug_Zan == 0) {
            p->flug_Zan = 1;
            // 斬撃の範囲内に敵がいるか
            if (p->B_x == 1) {
                // X座標が範囲内か
                if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) + 1 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) + 2) {
                    // Y座標が範囲内か
                    if (((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                        e->enemy[e->now_enemy][0] -= 1;
                        e->flug_damage = 1;
                        MciPlaySound(p->se_attack, false);
                    }
                }
            }
            if (p->B_x == -1) {
                // X座標が範囲内か
                if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) - 1 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) - 2) {
                    // Y座標が範囲内か
                    if (((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                        e->enemy[e->now_enemy][0] -= 1;
                        e->flug_damage = 1;
                        MciPlaySound(p->se_attack, false);
                    }
                }
            }
        }
        // 斬撃クールタイム
        if (p->flug_Zan == 1 && p->ani_cnt2 >= 7) {
            p->ani_cnt2++;
            if (p->ani_cnt2 > 20) {
                p->ani_cnt2 = 0;
                p->flug_Zan = 0;
            }
        }

        // 敵の生存確認
        if (e->enemy[e->now_enemy][0] <= 0 && e->flug_enemy == 1) {
            e->flug_enemy = 0;
            p->text[0] = 1;
        }

        //　当たり判定
        // マップ外(右)
        if (p->B_Right / 32 >= 20) {
            p->B_Right -= 3;
            p->B_Left -= 3;
        }
        // マップ外(左)
        if (p->B_Left < 0) {
            p->B_Right += 3;
            p->B_Left += 3;
        }
        // 落下時障害物判定(下)
        if (p->flug_Jump == 0) {
            switch (m->boss2_stage1[(p->B_Bottom / 32) + 1][p->Center[0] / 32]) {
            case 3:
                switch (p->FallCount) {
                case 0:
                case 1:
                    p->B_Bottom += 2;
                    p->B_Top += 2;
                    p->FallCount++;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    p->B_Bottom += 4;
                    p->B_Top += 4;
                    p->FallCount++;
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                    p->B_Bottom += 7;
                    p->B_Top += 7;
                    p->FallCount++;
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                    p->B_Bottom += 10;
                    p->B_Top += 10;
                    p->FallCount++;
                    break;
                default:
                    p->B_Bottom += 15;
                    p->B_Top += 15;
                    break;
                }
                break;
            case 1:
            case 2:
                p->flug_Ground = 1;
                p->B_Top = (p->B_Bottom / 32) * 32;
                p->B_Top -= 32;
                p->B_Bottom = p->B_Top + 63;
                MciPlaySound(p->se_jump2, false);
                break;
            }
        }
    }

    return;
}

// ラスボス二戦目
void Boss2_2_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {

    // 背景描写
    SetPalette(pic->b2_2_buck);
    DrawBmp(0, 0, pic->b2_2_buck, true);
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->boss2_stage1[y][x]) {
            case 1:
                SetPalette(pic->c_4);
                DrawBmp(x * 32, y * 32, pic->c_4, true);
                break;
            }

        }
    }
    // 敵描写
    if (e->flug_enemy == 1) {
        SetPalette(pic->boss_nomal_l);
        DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_nomal_l, true);
        if (e->flug_damage == 1) {
            if (p->ani_cnt2 < 2) {
                switch (p->B_x) {
                case 1:
                    e->blood_x = 10;
                    break;
                case -1:
                    e->blood_x = -10;
                    break;
                }
            }
            SetPalette(pic->b_blood1);
            DrawBmp(e->enemy[e->now_enemy][2] + e->blood_x, e->enemy[e->now_enemy][4], pic->b_blood1, true);
            if (p->ani_cnt2 > 3) {
                e->flug_damage = 0;
            }
        }
    }
    // プレイヤー描写
    // 無敵状態の確認
    if (p->flug_damage == 1 && (p->muteki_cnt / 2) % 2 == 1) {
        if (p->ani_data_2[p->ani_cnt] == 0xff) {
            p->ani_cnt = 0;
        }
    }
    else {
        // 待機・走り・ジャンプ・抜刀の判定
        // 走り
        if (p->flug_Move == 1) {
            if (p->ani_data_2[p->ani_cnt] == 0xff) {
                p->ani_cnt = 0;
            }
            // 右に向かって走る
            if (p->B_x == 1) {
                SetPalette(pic->b_r_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r_run[p->ani_data_2[p->ani_cnt]], true);
            }
            // 左に向かって走る
            else if (p->B_x == -1) {
                SetPalette(pic->b_l_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l_run[p->ani_data_2[p->ani_cnt]], true);
            }
        }
        // 待機時
        else {
            //向きによってキャラを描写
            if (p->B_x == 1) {
                SetPalette(pic->b_r);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r, true);
            }
            else if (p->B_x == -1) {
                SetPalette(pic->b_l);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l, true);
            }
        }
    }
    // 戦闘エフェクト
    // 魔法弾
    if (e->now_maho > 0) {
        // 三つの弾のフラグをチェック、それぞれ描写
        for (int i = 0; i < 5; i++) {
            if (e->mahodan[i][0] == 1) {
                SetPalette(pic->boss_maho[e->e_anime_cnt]);
                DrawBmp(e->mahodan[i][1], e->mahodan[i][2], pic->boss_maho[e->e_anime_cnt], true);
            }
        }
    }

    // 斬撃エフェクト描写
    if (p->flug_Zan == 1 && p->ani_cnt2 < 8) {
        switch (p->ani_data_3[p->ani_cnt2]) {
        case 0:
            p->zan_y = p->B_Top;
            if (p->B_x == 1) {
                p->zan_x = p->B_Left + 24;
            }
            else if (p->B_x == -1) {
                p->zan_x = p->B_Left - 24;
            }
            p->ani_cnt2++;
            break;
        case 1:
            SetPalette(pic->b_zan1);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan1, true);
            p->ani_cnt2++;
            break;
        case 2:
            SetPalette(pic->b_zan2);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan2, true);
            p->ani_cnt2++;
            break;
        case 3:
            SetPalette(pic->b_zan3);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan3, true);
            p->ani_cnt2++;
            break;
        case 0xff:

            break;
        }
    }
    // その他各種
    // HP表示
    for (int i = 0; i < p->Hp; i++) {
        SetPalette(pic->hp);
        DrawBmp(i * 32, 0, pic->hp, true);
    }

    // 戦闘前会話文
    if (p->flug_event[3] == 0) {
        if (p->text[0] == 1) {
            // テキストボックスの描写
            SetPalette(pic->textbox);
            DrawBmp(0, 352, pic->textbox, false);
            // テキストの描写
            SetPalette(pic->b2_t3[p->text[1]]);
            DrawBmp(160, 352, pic->b2_t3[p->text[1]], true);
            // キャラアイコン
            switch (p->text[1]) {
            case 0:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 1:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 2:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 3:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 4:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 5:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            }
        }
        // 戦闘画面突入演出
        if (p->text[1] > 5) {

            for (int i = 0; i < p->change_cnt; i++) {
                for (int y = 0; y < p->change_cnt - i; y++) {
                    SetPalette(pic->f_black);
                    DrawBmp(i * 32, y * 32, pic->f_black, false);
                }
            }
        }

    }
    // 戦闘終了後会話文
    if (e->flug_enemy == 0) {
        if (p->text[0] == 1) {
            // テキストボックスの描写
            SetPalette(pic->textbox);
            DrawBmp(0, 352, pic->textbox, false);
            // テキストの描写
            SetPalette(pic->b2_t4[p->text[1]]);
            DrawBmp(160, 352, pic->b2_t4[p->text[1]], true);
            // キャラアイコン
            switch (p->text[1]) {
            case 0:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 2:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            case 1:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            
            }
        }
        // 戦闘画面突入演出
        if (p->text[1] > 2) {

            for (int i = 0; i < p->change_cnt; i++) {
                for (int y = 0; y < p->change_cnt - i; y++) {
                    SetPalette(pic->f_black);
                    DrawBmp(i * 32, y * 32, pic->f_black, false);
                }
            }
        }
    }
    PrintFrameBuffer();

}
void Boss2_2_Update(Player* p, Key* k, Map* m, Enemy* e) {
    if (p->bgm_t == 1) {
        MciStopSound(p->bgm[6]);
        MciPlaySound(p->bgm[6], true);
        p->bgm_t = 0;
    }
    // 戦闘前イベント
    if (p->flug_event[3] == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 5) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->flug_event[3] = 1;
                p->change_cnt = 0;
                e->flug_enemy = 1;
            }
        }

    }
    // 敵を倒した時の処理
    else if (e->flug_enemy == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 2) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->text[0] = 1;
                p->flug_event[3] = 1;
                p->change_cnt = 0;
                p->changemap[0] = 1;
                p->changemap[1] = 20;
                p->ani_cnt = 0;
                p->flug_Move = 0;
                e->flug_enemy = 1;
                e->now_enemy = 5;
                p->bgm_t = 1;
                MciStopSound(p->bgm[6]);
                e->enemy[e->now_enemy][0] = e->enemy[e->now_enemy][7];
            }
        }
    }
    // プレイヤーが死んだ時の処理
    else if (p->Hp <= 0) {
        p->bgm_t = 1;
        MciStopSound(p->bgm[6]);
        // エンディング分岐
        // 隠しエンディング
        if (p->flug_event[1] == 1) {
            p->end_number = 6;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
        // エンディング２
        else {
            p->end_number = 2;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
    }
    // 戦い中の処理
    else {
        // プレイヤーの中心座標更新
        p->Center[0] = (p->B_Left + p->B_Right) / 2;// x座標
        p->Center[1] = (p->B_Top + p->B_Bottom) / 2;// y座標

        // プレイヤーの動き
        // 右移動
        if (k->key_right_N == 1) {
            //座標の加算
            p->B_Left += 3;
            p->B_Right += 3;
            // ani_cntの加算
            p->ani_cnt++;
            // 方向の指定
            p->B_x = 1;
            // フラグのON
            p->flug_Move = 1;
        }
        // 左移動
        else if (k->key_left_N == 1) {
            //座標の加算
            p->B_Left -= 3;
            p->B_Right -= 3;
            // ani_cntの加算
            p->ani_cnt++;
            //方向の指定
            p->B_x = -1;
            // フラグのON
            p->flug_Move = 1;
        }
        else {
            // フラグのOFF
            p->flug_Move = 0;
        }
        // ジャンプ
        if (k->key_space_T == 1 && p->flug_Ground == 1) {
            p->flug_Jump = 1;
            p->flug_Ground = 0;
            p->JumpCount = 0;
            p->FallCount = 0;
            MciPlaySound(p->se_jump1, false);
        }
        // ジャンプ中
        if (p->flug_Jump == 1) {

            switch (p->JumpCount) {
            case 0:
            case 1:
            case 2:
                p->B_Bottom -= 15;
                p->B_Top -= 15;
                p->JumpCount++;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                p->B_Bottom -= 10;
                p->B_Top -= 10;
                p->JumpCount++;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                p->B_Bottom -= 7;
                p->B_Top -= 7;
                p->JumpCount++;
                break;
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                p->B_Bottom -= 4;
                p->B_Top -= 4;
                p->JumpCount++;
                break;
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
                p->B_Bottom -= 2;
                p->B_Top -= 2;
                p->JumpCount++;
                break;
            case 40:
                p->flug_Jump = 0;
                break;
            }

        }


        // 敵の動き
        // 一定コマごとに魔法弾の設置
        e->e_cnt++;
        if (e->e_cnt % 60 == 0) {
            if (e->now_maho < 5) {
                int flug = 1;
                // srand((unsigned int)time(NULL));
                MciPlaySound(p->se_fire, false);
                int y = rand() % 8;
                // 魔法弾の設置
                e->mahodan[e->next_maho][0] = 1;
                e->mahodan[e->next_maho][2] = 0;// 座標設定
                e->mahodan[e->next_maho][4] = 63;
                switch (y) {
                case 0:
                    e->mahodan[e->next_maho][1] = 96;
                    break;
                case 1:
                    e->mahodan[e->next_maho][1] = 160;
                    break;
                case 2:
                    e->mahodan[e->next_maho][1] = 224;
                    break;
                case 3:
                    e->mahodan[e->next_maho][1] = 288;
                    break;
                case 4:
                    e->mahodan[e->next_maho][1] = 352;
                    break;
                case 5:
                    e->mahodan[e->next_maho][1] = 416;
                    break;
                case 6:
                    e->mahodan[e->next_maho][1] = 448;
                    break;
                case 7:
                    e->mahodan[e->next_maho][1] = 256;
                    break;
                }
                e->mahodan[e->next_maho][3] = e->mahodan[e->next_maho][1] + 63;
                flug = 0;
                e->now_maho++;
                e->next_maho++;
                if (e->next_maho == 5) {
                    e->next_maho = 0;
                }
            }
        }
        // 魔法弾の動き
        for (int i = 0; i < 5; i++) {
            if (e->mahodan[i][0] == 1) {
                e->mahodan[i][2]+=2;
                e->mahodan[i][4]+=2;
            }
        }
        switch (e->e_anime_cnt) {
        case 0:
            e->e_anime_cnt = 1;
            break;
        case 1:
            e->e_anime_cnt = 0;
            break;
        }

        // 範囲外で消滅
        for (int i = 0; i < 5; i++) {
            if (e->mahodan[i][0] == 1) {
                if (e->mahodan[i][2] > 512) {
                    e->mahodan[i][0] = 0;
                    e->now_maho--;
                }
            }
        }

        // 魔法との接触判定
            // 無敵状態かの判定
        if (p->flug_damage == 0 && e->now_maho > 0) {
            // 今現在ある魔法全ての接触をそれぞれ確認する
            for (int i = 0; i < 5; i++) {
                if (e->mahodan[i][0] == 1) {
                    if (e->mahodan[i][1] < p->Center[0] && e->mahodan[i][3] > p->Center[0] &&
                        e->mahodan[i][2] < p->Center[1] && e->mahodan[i][4] > p->Center[1]) {
                        // プレイヤーのHPを減らす
                        p->Hp -= e->enemy[e->now_enemy][1];
                        // 無敵状態のフラグを上げる
                        p->flug_damage = 1;
                        MciPlaySound(p->se_damage, false);
                    }
                }
            }
        }
        // 無敵状態のカウント処理
        if (p->flug_damage == 1) {
            p->muteki_cnt++;
            if (p->muteki_cnt > 30) {
                p->flug_damage = 0;
                p->muteki_cnt = 0;
            }
        }

        // 斬撃
        if (k->key_enter_T == 1 && p->flug_Zan == 0) {
            p->flug_Zan = 1;
            // 斬撃の範囲内に魔法弾がいるか
            if (p->B_x == 1) {
                for (int i = 0; i < 5; i++) {
                    if (e->mahodan[i][0] == 1) {
                        // X座標が範囲内か
                        if (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32 == p->Center[0] / 32 ||
                            (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32) == (p->Center[0] / 32) + 1 ||
                            (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32) == (p->Center[0] / 32) + 2) {
                            // Y座標が範囲内か
                            if (((e->mahodan[i][2] + e->mahodan[i][4]) / 2) / 32 == p->Center[1] / 32||
                                ((e->mahodan[i][2] + e->mahodan[i][4]) / 2) / 32 == (p->Center[1] / 32)-1) {
                                e->enemy[e->now_enemy][0] -= 1;
                                e->flug_damage = 1;
                                e->mahodan[i][0] = 0;
                                e->now_maho--;
                                MciPlaySound(p->se_attack, false);
                            }
                        }
                    }
                }
            }
            if (p->B_x == -1) {
                for (int i = 0; i < 5; i++) {
                    if (e->mahodan[i][0] == 1) {
                        // X座標が範囲内か
                        if (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32 == p->Center[0] / 32 ||
                            (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32) == (p->Center[0] / 32) - 1 ||
                            (((e->mahodan[i][1] + e->mahodan[i][3]) / 2) / 32) == (p->Center[0] / 32) - 2) {
                            // Y座標が範囲内か
                            if (((e->mahodan[i][2] + e->mahodan[i][4]) / 2) / 32 == p->Center[1] / 32||
                                ((e->mahodan[i][2] + e->mahodan[i][4]) / 2) / 32 == (p->Center[1] / 32)-1) {
                                e->enemy[e->now_enemy][0] -= 1;
                                e->flug_damage = 1;
                                e->mahodan[i][0] = 0;
                                e->now_maho--;
                                MciPlaySound(p->se_attack, false);
                            }
                        }
                    }
                }
            }
        }
        // 斬撃クールタイム
        if (p->flug_Zan == 1 && p->ani_cnt2 >= 7) {
            p->ani_cnt2++;
            if (p->ani_cnt2 > 20) {
                p->ani_cnt2 = 0;
                p->flug_Zan = 0;
            }
        }

        // 敵の生存確認
        if (e->enemy[e->now_enemy][0] <= 0 && e->flug_enemy == 1) {
            e->flug_enemy = 0;
            p->text[0] = 1;
        }

        //　当たり判定
        // マップ外(右)
        if (p->B_Right / 32 >= 20) {
            p->B_Right -= 3;
            p->B_Left -= 3;
        }
        // マップ外(左)
        if (p->B_Left < 0) {
            p->B_Right += 3;
            p->B_Left += 3;
        }
        // 落下時障害物判定(下)
        if (p->flug_Jump == 0) {
            switch (m->boss2_stage1[(p->B_Bottom / 32) + 1][p->Center[0] / 32]) {
            case 3:
                switch (p->FallCount) {
                case 0:
                case 1:
                    p->B_Bottom += 2;
                    p->B_Top += 2;
                    p->FallCount++;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    p->B_Bottom += 4;
                    p->B_Top += 4;
                    p->FallCount++;
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                    p->B_Bottom += 7;
                    p->B_Top += 7;
                    p->FallCount++;
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                    p->B_Bottom += 10;
                    p->B_Top += 10;
                    p->FallCount++;
                    break;
                default:
                    p->B_Bottom += 15;
                    p->B_Top += 15;
                    break;
                }
                break;
            case 1:
            case 2:
                p->flug_Ground = 1;
                p->B_Top = (p->B_Bottom / 32) * 32;
                p->B_Top -= 32;
                p->B_Bottom = p->B_Top + 63;
                MciPlaySound(p->se_jump2, false);
                break;
            }
        }
    }


}

// ラスボス三戦目
void Boss2_3_Draw(Player* p, Pic* pic, Map* m, Enemy* e) {

    // 背景描写
    SetPalette(pic->b2_2_buck);
    DrawBmp(0, 0, pic->b2_2_buck, true);
    // マップチップ描写
    for (int x = 0; x < 20; x++) {
        for (int y = 0; y < 16; y++) {
            switch (m->boss2_stage1[y][x]) {
            case 1:
                SetPalette(pic->c_4);
                DrawBmp(x * 32, y * 32, pic->c_4, true);
                break;
            }

        }
    }
    // 敵描写
    if (e->flug_enemy == 1) {
        if (e->flug_e_walk == 1) {
            if (e->enemy[e->now_enemy][6] == -1) {
                SetPalette(pic->boss_walk_l[e->anime[e->e_anime_cnt]]);
                DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_walk_l[e->anime[e->e_anime_cnt]], true);
            }
            else {
                SetPalette(pic->boss_walk_r[e->anime[e->e_anime_cnt]]);
                DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_walk_r[e->anime[e->e_anime_cnt]], true);
            }
        }
        else {
            SetPalette(pic->boss_nomal_l);
            DrawBmp(e->enemy[e->now_enemy][2], e->enemy[e->now_enemy][4], pic->boss_nomal_l, true);
        }
        // ダメージエフェクト
        if (e->flug_damage == 1) {
            if (p->ani_cnt2 < 2) {
                switch (p->B_x) {
                case 1:
                    e->blood_x = 10;
                    break;
                case -1:
                    e->blood_x = -10;
                    break;
                }
            }
            SetPalette(pic->b_blood1);
            DrawBmp(e->enemy[e->now_enemy][2] + e->blood_x, e->enemy[e->now_enemy][4], pic->b_blood1, true);
            if (p->ani_cnt2 > 3) {
                e->flug_damage = 0;
            }
        }
    }
    // プレイヤー描写
    // 無敵状態の確認
    if (p->flug_damage == 1 && (p->muteki_cnt / 2) % 2 == 1) {
        if (p->ani_data_2[p->ani_cnt] == 0xff) {
            p->ani_cnt = 0;
        }
    }
    else {
        // 待機・走り・ジャンプ・抜刀の判定
        // 走り
        if (p->flug_Move == 1) {
            if (p->ani_data_2[p->ani_cnt] == 0xff) {
                p->ani_cnt = 0;
            }
            // 右に向かって走る
            if (p->B_x == 1) {
                SetPalette(pic->b_r_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r_run[p->ani_data_2[p->ani_cnt]], true);
            }
            // 左に向かって走る
            else if (p->B_x == -1) {
                SetPalette(pic->b_l_run[p->ani_data_2[p->ani_cnt]]);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l_run[p->ani_data_2[p->ani_cnt]], true);
            }
        }
        // 待機時
        else {
            //向きによってキャラを描写
            if (p->B_x == 1) {
                SetPalette(pic->b_r);
                DrawBmp(p->B_Left, p->B_Top, pic->b_r, true);
            }
            else if (p->B_x == -1) {
                SetPalette(pic->b_l);
                DrawBmp(p->B_Left, p->B_Top, pic->b_l, true);
            }
        }
    }
    // 戦闘エフェクト
    // 斬撃エフェクト描写
    if (p->flug_Zan == 1 && p->ani_cnt2 < 8) {
        switch (p->ani_data_3[p->ani_cnt2]) {
        case 0:
            p->zan_y = p->B_Top;
            if (p->B_x == 1) {
                p->zan_x = p->B_Left + 24;
            }
            else if (p->B_x == -1) {
                p->zan_x = p->B_Left - 24;
            }
            p->ani_cnt2++;
            break;
        case 1:
            SetPalette(pic->b_zan1);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan1, true);
            p->ani_cnt2++;
            break;
        case 2:
            SetPalette(pic->b_zan2);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan2, true);
            p->ani_cnt2++;
            break;
        case 3:
            SetPalette(pic->b_zan3);
            DrawBmp(p->zan_x, p->zan_y, pic->b_zan3, true);
            p->ani_cnt2++;
            break;
        case 0xff:

            break;
        }
    }
    // その他各種
    // HP表示
    for (int i = 0; i < p->Hp; i++) {
        SetPalette(pic->hp);
        DrawBmp(i * 32, 0, pic->hp, true);
    }

    // 戦闘前会話文
    if (p->flug_event[4] == 0) {
        if (p->text[0] == 1) {
            // テキストボックスの描写
            SetPalette(pic->textbox);
            DrawBmp(0, 352, pic->textbox, false);
            // テキストの描写
            SetPalette(pic->b2_t5[p->text[1]]);
            DrawBmp(160, 352, pic->b2_t5[p->text[1]], true);
            // キャラアイコン
            switch (p->text[1]) {
            case 0:
                SetPalette(pic->tatie_maou);
                DrawBmp(10, 362, pic->tatie_maou, true);
                break;
            case 1:
                SetPalette(pic->tatie_p);
                DrawBmp(10, 362, pic->tatie_p, true);
                break;
            }
        }
        // 戦闘画面突入演出
        if (p->text[1] > 1) {

            for (int i = 0; i < p->change_cnt; i++) {
                for (int y = 0; y < p->change_cnt - i; y++) {
                    SetPalette(pic->f_black);
                    DrawBmp(i * 32, y * 32, pic->f_black, false);
                }
            }
        }

    }
    // 戦闘終了後会話文
    if (e->flug_enemy == 0) {

    }
    PrintFrameBuffer();

}
void Boss2_3_Update(Player* p, Key* k, Map* m, Enemy* e) {
    if (p->bgm_t == 1) {
        MciStopSound(p->bgm[6]);
        MciPlaySound(p->bgm[7], true);
        p->bgm_t = 0;
    }
    // 戦闘前イベント
    if (p->flug_event[4] == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 1) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->flug_event[4] = 1;
                p->change_cnt = 0;
                e->flug_enemy = 1;
            }
        }

    }
    // 敵を倒した時の処理
    else if (e->flug_enemy == 0) {
        if (k->key_enter_T == 1) {
            p->text[1]++;
        }
        if (p->text[1] > 2) {
            p->change_cnt++;
            p->text[0] = 0;
            if (p->change_cnt > 36) {
                // テキスト関係初期化
                p->text[1] = 0;
                p->flug_event[3] = 1;
                p->change_cnt = 0;
                p->changemap[0] = 1;
                p->changemap[1] = 21;
                p->ani_cnt = 0;
                p->flug_Move = 0;
                p->end_number = 1;
                p->bgm_t = 1;
            }
        }
    }
    // プレイヤーが死んだ時の処理
    else if (p->Hp <= 0) {
        // エンディング分岐
        p->bgm_t = 1;
        // 隠しエンディング
        if (p->flug_event[1] == 1) {
            p->end_number = 6;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
        // エンディング２
        else {
            p->end_number = 2;
            p->changemap[0] = 1;
            p->changemap[1] = 21;
        }
    }
    // 戦い中の処理
    else {
        // プレイヤーの中心座標更新
        p->Center[0] = (p->B_Left + p->B_Right) / 2;// x座標
        p->Center[1] = (p->B_Top + p->B_Bottom) / 2;// y座標

        // プレイヤーの動き
        // 右移動
        if (k->key_right_N == 1) {
            //座標の加算
            p->B_Left += 3;
            p->B_Right += 3;
            // ani_cntの加算
            p->ani_cnt++;
            // 方向の指定
            p->B_x = 1;
            // フラグのON
            p->flug_Move = 1;
        }
        // 左移動
        else if (k->key_left_N == 1) {
            //座標の加算
            p->B_Left -= 3;
            p->B_Right -= 3;
            // ani_cntの加算
            p->ani_cnt++;
            //方向の指定
            p->B_x = -1;
            // フラグのON
            p->flug_Move = 1;
        }
        else {
            // フラグのOFF
            p->flug_Move = 0;
        }
        // ジャンプ
        if (k->key_space_T == 1 && p->flug_Ground == 1) {
            p->flug_Jump = 1;
            p->flug_Ground = 0;
            p->JumpCount = 0;
            p->FallCount = 0;
            MciPlaySound(p->se_jump1, false);
        }
        // ジャンプ中
        if (p->flug_Jump == 1) {

            switch (p->JumpCount) {
            case 0:
            case 1:
            case 2:
                p->B_Bottom -= 15;
                p->B_Top -= 15;
                p->JumpCount++;
                break;
            case 3:
            case 4:
            case 5:
            case 6:
                p->B_Bottom -= 10;
                p->B_Top -= 10;
                p->JumpCount++;
                break;
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                p->B_Bottom -= 7;
                p->B_Top -= 7;
                p->JumpCount++;
                break;
            case 14:
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
            case 24:
            case 25:
                p->B_Bottom -= 4;
                p->B_Top -= 4;
                p->JumpCount++;
                break;
            case 26:
            case 27:
            case 28:
            case 29:
            case 30:
            case 31:
            case 32:
            case 33:
            case 34:
            case 35:
            case 36:
            case 37:
            case 38:
            case 39:
                p->B_Bottom -= 2;
                p->B_Top -= 2;
                p->JumpCount++;
                break;
            case 40:
                p->flug_Jump = 0;
                break;
            }

        }


        // 敵の動き
        // 一定コマごとにプレイヤーの位置を判断して追いかける
        e->e_cnt++;
        if (e->e_cnt % 5 == 0) {
            // プレイヤーの右側に敵がいるとき
            if ((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2 > p->Center[0]) {
                e->enemy[e->now_enemy][6] = -1;
            }
            // プレイヤーの左側に敵がいるとき
            else if ((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2 < p->Center[0]) {
                e->enemy[e->now_enemy][6] = 1;
            }
        }
        if (e->enemy[e->now_enemy][6] == 1) {
            e->enemy[e->now_enemy][2] += 1;
            e->enemy[e->now_enemy][3] += 1;
            e->e_anime_cnt++;
            e->flug_e_walk = 1;
        }
        else {
            e->enemy[e->now_enemy][2] -= 1;
            e->enemy[e->now_enemy][3] -= 1;
            e->e_anime_cnt++;
            e->flug_e_walk = 1;
        }

        if (e->anime[e->e_anime_cnt] == 0xff) {
            e->e_anime_cnt = 0;
        }

        // 敵との接触判定
            // 無敵状態かの判定
        if (p->flug_damage == 0) {
            // プレイヤーのBottomが範囲内かつ、プレイヤーのCenter[0]が範囲内
            if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 &&
                ((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                // プレイヤーのHPを減らす
                p->Hp -= e->enemy[e->now_enemy][1];
                // 無敵状態のフラグを上げる
                p->flug_damage = 1;
                MciPlaySound(p->se_damage, false);
            }
        }
        // 無敵状態のカウント処理
        if (p->flug_damage == 1) {
            p->muteki_cnt++;
            if (p->muteki_cnt > 30) {
                p->flug_damage = 0;
                p->muteki_cnt = 0;
            }
        }

        // 斬撃
        if (k->key_enter_T == 1 && p->flug_Zan == 0) {
            p->flug_Zan = 1;
            // 斬撃の範囲内に敵がいるか
            if (p->B_x == 1) {
                // X座標が範囲内か
                if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) + 1 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) + 2) {
                    // Y座標が範囲内か
                    if (((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                        e->enemy[e->now_enemy][0] -= 1;
                        e->flug_damage = 1;
                        MciPlaySound(p->se_attack, false);
                    }
                }
            }
            if (p->B_x == -1) {
                // X座標が範囲内か
                if (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32 == p->Center[0] / 32 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) - 1 ||
                    (((e->enemy[e->now_enemy][2] + e->enemy[e->now_enemy][3]) / 2) / 32) == (p->Center[0] / 32) - 2) {
                    // Y座標が範囲内か
                    if (((e->enemy[e->now_enemy][4] + e->enemy[e->now_enemy][5]) / 2) / 32 == p->Center[1] / 32) {
                        e->enemy[e->now_enemy][0] -= 1;
                        e->flug_damage = 1;
                        MciPlaySound(p->se_attack, false);
                    }
                }
            }
        }
        // 斬撃クールタイム
        if (p->flug_Zan == 1 && p->ani_cnt2 >= 7) {
            p->ani_cnt2++;
            if (p->ani_cnt2 > 20) {
                p->ani_cnt2 = 0;
                p->flug_Zan = 0;
            }
        }

        // 敵の生存確認
        if (e->enemy[e->now_enemy][0] <= 0 && e->flug_enemy == 1) {
            e->flug_enemy = 0;
            p->text[0] = 1;
        }

        //　当たり判定
        // マップ外(右)
        if (p->B_Right / 32 >= 20) {
            p->B_Right -= 3;
            p->B_Left -= 3;
        }
        // マップ外(左)
        if (p->B_Left < 0) {
            p->B_Right += 3;
            p->B_Left += 3;
        }
        // 落下時障害物判定(下)
        if (p->flug_Jump == 0) {
            switch (m->boss2_stage1[(p->B_Bottom / 32) + 1][p->Center[0] / 32]) {
            case 3:
                switch (p->FallCount) {
                case 0:
                case 1:
                    p->B_Bottom += 2;
                    p->B_Top += 2;
                    p->FallCount++;
                    break;
                case 2:
                case 3:
                case 4:
                case 5:
                    p->B_Bottom += 4;
                    p->B_Top += 4;
                    p->FallCount++;
                    break;
                case 6:
                case 7:
                case 8:
                case 9:
                case 10:
                case 11:
                case 12:
                case 13:
                    p->B_Bottom += 7;
                    p->B_Top += 7;
                    p->FallCount++;
                    break;
                case 14:
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                case 20:
                case 21:
                case 22:
                case 23:
                case 24:
                case 25:
                    p->B_Bottom += 10;
                    p->B_Top += 10;
                    p->FallCount++;
                    break;
                default:
                    p->B_Bottom += 15;
                    p->B_Top += 15;
                    break;
                }
                break;
            case 1:
            case 2:
                p->flug_Ground = 1;
                p->B_Top = (p->B_Bottom / 32) * 32;
                p->B_Top -= 32;
                p->B_Bottom = p->B_Top + 63;
                MciPlaySound(p->se_jump2, false);
                break;
            }
        }
    }


}