/**
 * UIBase.h
 * UIの基本的な処理をするクラス群
 */
#pragma once


class UIBase : public Noncopyable
{
public:
	Transform m_transform;


protected:
	bool isStart = false;
	bool isUpdate = true;
	bool isDraw = true;


public:
	UIBase() {}
	virtual ~UIBase() {}

	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;
};




// ============================================
// 画像を使うUI関連
// ============================================


class UIImage : public UIBase
{
protected:
	SpriteRender m_spriteRender;


protected:
	UIImage();
	~UIImage();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;
};



/**
 * ゲージUI
 */
class UIGauge : public UIImage
{
private:
	UIGauge();
	~UIGauge();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;
};


/**
 * アイコンUI
 */
class UIIcon : public UIImage
{
	friend class UICanvas;

private:
	UIIcon();
	~UIIcon();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	void Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation);
};




// ============================================
// 文字を使うUI関連
// ============================================


class UIText : public UIBase
{
protected:
	FontRender m_fontRender;


private:
	UIText();
	~UIText();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;
};



// ============================================
// ボタンを使うUI関連
// ============================================
class UIButton : public UIImage
{
private:
	/** ボタンが押されたときの処理(外部から委譲される) */
	std::function<void()> m_delegate;


private:
	UIButton();
	~UIButton();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;
};




// ============================================
// キャンバス
// ============================================


/**
 * 絵を書くキャンバスのイメージ
 * UIを作るときにこのクラスを作ってください
 */
class UICanvas
{
	friend class UIBase;
	friend class UIImage;
	friend class UIGauge;
	friend class UIIcon;
	friend class UIText;
	friend class UIButton;


public:
	/** 例外でpublic */
	Transform m_transform;


private:
	/**
	 * NOTE: 各UI自体に親子関係持たせたいけど使わない可能性があるので、一旦ここだけにしてみる
	 */
	std::vector<UIBase*> m_uiList;


public:
	UICanvas();
	~UICanvas();


	bool Start();
	void Update();
	void Render(RenderContext& rc);


public:
	template <typename T>
	T* CreateUI()
	{
		T* ui = new T();
		ui->m_transform.SetParent(&m_transform);
		m_uiList.push_back(ui);
		return ui;
	}
};