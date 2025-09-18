#pragma once

/* è∞ */

class BackGround : public IGameObject
{
private:
	ModelRender m_modelRender;
	PhysicsStaticObject physicsStaticObject;

public:
	BackGround();
	~BackGround();
	
	void Render(RenderContext&rc);


public:
	// TODO: âº
	ModelRender* GetModelRender() { return &m_modelRender; }
};

