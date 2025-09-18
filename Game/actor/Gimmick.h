/**
 * Gimmick.h
 * ステージに配置されるギミックの基底クラス
 */
#pragma once
#include "Actor.h"


/**
 * ギミッククラス
 */
class Gimmick : public Actor
{
protected:


public:
	Gimmick();
	~Gimmick();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override;

public:
	void Initialize(const char* assetName, const Vector3& position, const Vector3& scale, const Quaternion& rotation);
};




/*************************************/


class StaticGimmick : public Gimmick
{
public:
	StaticGimmick() {}
	~StaticGimmick() {}

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override;
};