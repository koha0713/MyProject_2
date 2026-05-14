/*
	概要:入力関数
*/
#ifndef __INPUT_H__
#define __INPUT_H__

#include <Windows.h>	// Windows API使用
#undef max	// std::max,minとの衝突解決
#undef min

// ライフサイクル
HRESULT InitInput();
void UninitInput();
void UpdateInput();

// 状態取得
bool IsKeyPress(BYTE key);		// 今押されているか
bool IsKeyTrigger(BYTE key);	// 今押した瞬間か
bool IsKeyRelease(BYTE key);	// 今離した瞬間か
bool IsKeyRepeat(BYTE key);		// 長押ししているか

#endif // __INPUT_H__