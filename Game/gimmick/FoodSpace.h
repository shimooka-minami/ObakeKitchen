/**
 * FoodSpace.h
 * 食材が出てくる場所の判定を提供する
 */
#pragma once
#include "collision/GhostBody.h"


/**
 * FoodSpace
 */
class FoodSpace : public IGameObject
{
public:
	/** 例外でpublic */
	Transform m_transform;

protected:
	/** 判定の半径 */
	float m_radius = 0.0f;

	/** 当たり判定 */
	std::unique_ptr<SphereGhostBody> m_ghostBody;

	// Lesson ここにAssetsPathを文字列でもてるようにして
	std::string m_assetPath;
	std::string m_coockedAssetPath;
	std::string m_plateAssetPath;

public:
	FoodSpace();
	~FoodSpace();

	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& renderContect) override {} // 描画はない


private:
	void UpdateTransform();


public:
	/** 半径の設定 */
	inline void SetRadius(const float radius) { m_radius = radius; }


	// Lesson ここでAssetPathを取得できるようなゲッター関数を追加して
	/** AssetPathの取得 */
	inline std::string GetAssetPath() const { return m_assetPath; };

	// Lesson ここでAssetPathを設定するセッター関数を追加して
	inline void SetAssetPath(const std::string assetPath) { m_assetPath = assetPath; };

	/** AssetPathを取得(調理済みのもの) */
	inline std::string GetCookedAssetsPath() const { return m_coockedAssetPath; };

	/** AssetPathを設定(調理済みのもの) */
	inline void SetCookedAssetsPath(const std::string cookedAssetsPath) { m_coockedAssetPath = cookedAssetsPath; };

	/** AssetPathを取得(お皿を乗せた皿) */
	inline std::string GetPlateAssetsPath() const { return m_plateAssetPath; };

	/** AssetPathを設定(お皿を乗せた皿) */
	inline void SetPlateAssetsPath(const std::string plateAssetsPath) { m_plateAssetPath = plateAssetsPath; };
};