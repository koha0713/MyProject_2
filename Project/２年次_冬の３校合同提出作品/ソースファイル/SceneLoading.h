#pragma once
#include "SceneBase.h"

class SceneLoading : public SceneBase
{

public:
    void Init() override;
    void UnInit() override;
    void Update() override;
    void Draw() override;
    void Draw(Camera*) override {}
};
