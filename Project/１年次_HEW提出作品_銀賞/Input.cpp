#include"conioex_New.h"
#include"Game.h"
using namespace std;

void Input(Key* key) {
	// エンターキー処理
	key->key_enter_O = key->key_enter_N;
	if (InputKeyMouse(PK_ENTER) || InputKeyMouse(PK_Z)) {
		key->key_enter_N = 1;
	}
	else {
		key->key_enter_N = 0;
	}
	if (key->key_enter_O == 0 && key->key_enter_N == 1) {
		key->key_enter_T = 1;
	}
	else {
		key->key_enter_T = 0;
	}

	// ESCキー処理
	key->key_esc_O = key->key_esc_N;
	if (InputKeyMouse(PK_ESC)) {
		key->key_esc_N = 1;
	}
	else {
		key->key_esc_N = 0;
	}
	if (key->key_esc_O == 0 && key->key_esc_N == 1) {
		key->key_esc_T = 1;
	}
	else {
		key->key_esc_T = 0;
	}

	// バックキー処理
	key->key_back_O = key->key_back_N;
	if (InputKeyMouse(PK_X)) {
		key->key_back_N = 1;
	}
	else {
		key->key_back_N = 0;
	}
	if (key->key_back_O == 0 && key->key_back_N == 1) {
		key->key_back_T = 1;
	}
	else {
		key->key_back_T = 0;
	}

	// スペースキー処理
	key->key_space_O = key->key_space_N;
	if (InputKeyMouse(PK_SP)) {
		key->key_space_N = 1;
	}
	else {
		key->key_space_N = 0;
	}
	if (key->key_space_O == 0 && key->key_space_N == 1) {
		key->key_space_T = 1;
	}
	else {
		key->key_space_T = 0;
	}

	// 右キー処理
	key->key_right_O = key->key_right_N;
	if (InputKeyMouse(PK_RIGHT)) {
		key->key_right_N = 1;
	}
	else {
		key->key_right_N = 0;
	}
	if (key->key_right_O == 0 && key->key_right_N == 1) {
		key->key_right_T = 1;
	}
	else {
		key->key_right_T = 0;
	}

	// 左キー処理
	key->key_left_O = key->key_left_N;
	if (InputKeyMouse(PK_LEFT)) {
		key->key_left_N = 1;
	}
	else {
		key->key_left_N = 0;
	}
	if (key->key_left_O == 0 && key->key_left_N == 1) {
		key->key_left_T = 1;
	}
	else {
		key->key_left_T = 0;
	}

	// 上キー処理
	key->key_up_O = key->key_up_N;
	if (InputKeyMouse(PK_UP)) {
		key->key_up_N = 1;
	}
	else {
		key->key_up_N = 0;
	}
	if (key->key_up_O == 0 && key->key_up_N == 1) {
		key->key_up_T = 1;
	}
	else {
		key->key_up_T = 0;
	}

	// 下キー処理
	key->key_down_O = key->key_down_N;
	if (InputKeyMouse(PK_DOWN)) {
		key->key_down_N = 1;
	}
	else {
		key->key_down_N = 0;
	}
	if (key->key_down_O == 0 && key->key_down_N == 1) {
		key->key_down_T = 1;
	}
	else {
		key->key_down_T = 0;
	}

	return;
}