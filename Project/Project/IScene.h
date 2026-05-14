#pragma once
#include <cstdint>

// シーンインタフェース
class IScene {
public:
	//====================
	// ライフサイクル
	//====================
	IScene() = default;
	virtual ~IScene() = default;

	virtual void Init() = 0;
	virtual void UnInit() = 0;
	virtual void Update(uint64_t delta) = 0;
	virtual void Draw(uint64_t delta) = 0;
};
