/**
 * Character.h
 * キャラクターとなる要素をもったクラス
 */
#pragma once
#include "Actor.h"


class CharacterStatus;


/**
 * キャラクタークラス
 * NOTE:キャラクターとなる要素をもったクラス
 */
class Character : public Actor
{
protected:
	/** キャラクターコントローラー。物理的な判定を使用する。 */
	CharacterController m_characterController;

	/** アニメーションクリップのリスト */
	std::vector<AnimationClip*> m_animationClipList;

public:
	Character();
	~Character();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override;

public:
	CharacterStatus* GetStatus() { return dynamic_cast<CharacterStatus*>(m_status); }

	/**
	 * 当たり判定チェックのため取得
	 * NOTE:それ以外では使用しないこと
	 */
	CharacterController* GetCharacterController() { return &m_characterController; }
};