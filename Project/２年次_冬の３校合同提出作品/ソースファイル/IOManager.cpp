#include "IOManager.h"
#include "Application.h"

//#include "controllerSW.h"

IOManager::IOManager()
{
	Init();
}

void IOManager::Init()
{
	m_keyBindTable[MODE_KEYBORD] =
	{
		{TYPE_OK, VK_RETURN},
		{TYPE_CANCEL, VK_CANCEL},
	};

	//InitController();
}
void IOManager::UnInit()
{
	
	//UninitController();
}

void IOManager::Update()
{
	m_Input.Update();
	IOManager::UpdateMouse();
	//UpdateController();
}

void IOManager::SetInputMode(INPUT_MODE _mode)
{
	m_mode = _mode;
}

INPUT_MODE IOManager::GetInputMode()
{
	return m_mode;
}

bool IOManager::GetKeyDown(INPUT_TYPE _key)
{
	bool ret = false;

	assert(_key < TYPE_COUNT);		// エラーチェック

	switch (m_mode)
	{
	case MODE_KEYBORD:
		ret = GetKeyDownKeyBord(m_keyBindTable[MODE_KEYBORD][_key]);
		break;
	case MODE_CONTROLLER_XBOX:
		break;
	case MODE_BOTH:
		break;
	default:
		break;
	}
	
	return ret;
}
bool IOManager::GetKeyPress(INPUT_TYPE _key)
{
	bool ret = false;

	assert(_key < TYPE_COUNT);		// エラーチェック

	switch (m_mode)
	{
	case MODE_KEYBORD:
		ret = GetKeyPressKeyBord(m_keyBindTable[MODE_KEYBORD][_key]);
		break;
	case MODE_CONTROLLER_XBOX:
		break;
	case MODE_BOTH:
		break;
	default:
		break;
	}

	return ret;
}
bool IOManager::GetKeyUp(INPUT_TYPE _key)
{
	bool ret = false;

	assert(_key < TYPE_COUNT);		// エラーチェック

	switch (m_mode)
	{
	case MODE_KEYBORD:
		ret = GetKeyUpKeyBord(m_keyBindTable[MODE_KEYBORD][_key]);
		break;
	case MODE_CONTROLLER_XBOX:
		break;
	case MODE_BOTH:
		break;
	default:
		break;
	}

	return ret;
}


// キー押下
bool IOManager::GetKeyDownController(INPUT_TYPE _key)
{
	bool ret = false;

#ifndef _WIN64
	ret = GetControllerTrigger(ChangeKeycode_SW(_key));
#endif //_WIN64
	return ret;
}

// キー長押し検知
bool IOManager::GetKeyPressController(INPUT_TYPE _key)
{
	bool ret = false;

#ifndef _WIN64
	ret = GetControllerPress(ChangeKeycode_SW(_key));
#endif //_WIN64
	return ret;
}

// キーが離された
bool IOManager::GetKeyUpController(INPUT_TYPE _key)
{
	bool ret = false;

#ifndef _WIN64
	ret = GetControllerRelease(ChangeKeycode_SW(_key));
#endif //_WIN64
	return ret;
}

bool IOManager::GetKeyDownKeyBord(int _key)
{
	return m_Input.GetKeyTrigger(_key);
}
bool IOManager::GetKeyPressKeyBord(int _key)
{
	return m_Input.GetKeyPress(_key);
}
bool IOManager::GetKeyUpKeyBord(int _key)
{
	return m_Input.GetKeyRelease(_key);
}

bool IOManager::GetMouseDown(int vk)
{
	return m_Input.GetKeyTrigger(vk);
}

bool IOManager::GetMousePress(int vk)
{
	return m_Input.GetKeyPress(vk);
}

bool IOManager::GetMouseUp(int vk)
{
	return m_Input.GetKeyRelease(vk);
}

static POINT prevMousePos = { 0, 0 };
static bool firstFrameMouse = true;

void IOManager::UpdateMouse()
{
	// カーソル情報取得
	CURSORINFO ci = { 0 };
	ci.cbSize = sizeof(CURSORINFO);
	if (!GetCursorInfo(&ci))
		return; // 取得失敗したら何もしない

	// カーソルが見えていない場合だけ中央固定
	if (!(ci.flags & CURSOR_SHOWING))
	{
		POINT centerPos;
		RECT clientRect;

		// ウィンドウのクライアント座標を取得
		GetClientRect(Application::GetWindow(), &clientRect);
		centerPos.x = (clientRect.right - clientRect.left) / 2;
		centerPos.y = (clientRect.bottom - clientRect.top) / 2;

		// クライアント座標をスクリーン座標に変換
		ClientToScreen(Application::GetWindow(), &centerPos);

		POINT mousePos;
		GetCursorPos(&mousePos);

		// マウス移動量を計算
		m_mouseDelta.x = static_cast<float>(mousePos.x - centerPos.x);
		m_mouseDelta.y = static_cast<float>(mousePos.y - centerPos.y);

		// カーソルを中央に戻す
		SetCursorPos(centerPos.x, centerPos.y);
	}
	else
	{
		// 通常のマウス差分計算
		POINT p;
		GetCursorPos(&p);

		static POINT prevMousePos = p;
		m_mouseDelta.x = static_cast<float>(p.x - prevMousePos.x);
		m_mouseDelta.y = static_cast<float>(p.y - prevMousePos.y);

		prevMousePos = p;
	}
}


DirectX::SimpleMath::Vector2 IOManager::GetMouseDelta()
{
	return m_mouseDelta;
}

int IOManager::ChangeKeycode_SW(INPUT_TYPE _inpput)
{
	int ret = -1;
#ifndef _WIN64
	switch (_inpput)
	{
	case INPUT_TYPE_A:
		ret = NpadButton::A::Index;
		break;
	case INPUT_TYPE_B:
		ret = NpadButton::B::Index;
		break;
	case INPUT_TYPE_X:
		ret = NpadButton::X::Index;
		break;
	case INPUT_TYPE_Y:
		ret = NpadButton::Y::Index;
		break;
	case INPUT_TYPE_UP:
		ret = NpadButton::Up::Index;
		break;
	case INPUT_TYPE_DOWN:
		ret = NpadButton::Down::Index;
		break;
	case INPUT_TYPE_RIGHT:
		ret = NpadButton::Right::Index;
		break;
	case INPUT_TYPE_LEFT:
		ret = NpadButton::Left::Index;
		break;
	case INPUT_TYPE_RS:
		break;
	case INPUT_TYPE_LS:
		break;
	case INPUT_TYPE_R:
		break;
	case INPUT_TYPE_ZR:
		break;
	case INPUT_TYPE_L:
		break;
	case INPUT_TYPE_ZL:
		break;
	case INPUT_TYPE_PLUS:
		break;
	case INPUT_TYPE_MINUS:
		break;
	case INPUT_TYPE_NUM:
		break;
		// スティックの判定は要検討
	case INPUT_TYPE_RS_UP:
		break;
	case INPUT_TYPE_RS_DOWN:
		break;
	case INPUT_TYPE_RS_RIGHT:

		break;
	case INPUT_TYPE_RS_LEFT:
		break;
	case INPUT_TYPE_LS_UP:
		break;
	case INPUT_TYPE_LS_DOWN:
		break;
	case INPUT_TYPE_LS_RIGHT:
		break;
	case INPUT_TYPE_LS_LEFT:
		break;
	default:
		break;
	}

#endif //_WIN64
	return ret;
}

//Vector2 IOManager::GetLeftStickInclination()
//{
//	Vector2 ret = {0, 0};
//#ifndef _WIN64
//	Float2 data = GetControllerLeftStick();
//	ret.x = data.x;
//	ret.y = data.y;
//#endif //_WIN64
//	return ret;
//}
//Vector2 IOManager::GetRightStickInclination()
//{
//	Vector2 ret = { 0, 0 };
//#ifndef _WIN64
//	Float2 data = ::GetControllerRightStick();
//	ret.x = data.x;
//	ret.y = data.y;
//#endif //_WIN64
//	return ret;
//}