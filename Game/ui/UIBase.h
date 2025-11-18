/**
 * UIBase.h
 * UIの基本的な処理をするクラス群
 */
#pragma once


class SpriteAnimationBase;


class UIBase : public Noncopyable
{
public:
	Transform m_transform;


protected:
	bool isStart = false;
	bool isUpdate = true;
	bool isDraw = true;

	std::vector<SpriteAnimationBase*> m_spriteAnimationList;


public:
	UIBase()
	{
		m_spriteAnimationList.clear();
	}
	virtual ~UIBase()
	{
		for (auto* spriteAnimation : m_spriteAnimationList) {
			delete spriteAnimation;
			spriteAnimation = nullptr;
		}
		m_spriteAnimationList.clear();
	}

	virtual bool Start() = 0;
	virtual void Update() = 0;
	virtual void Render(RenderContext& rc) = 0;


public:
	/** スプライトアニメーションの追加 */
	void AddSpriteAnimation(SpriteAnimationBase* animation)
	{
		m_spriteAnimationList.push_back(animation);
	}
	void PlaySpriteAnimation();
	void StopSpriteAnimation();
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

public:
	/** スプライトレンダーの取得 */
	SpriteRender* GetSpriteRender() { return &m_spriteRender; }
};



/**
 * ゲージUI
 */
class UIGauge : public UIImage
{
	friend class UICanvas;
	

private:
	UIGauge();
	~UIGauge();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;

public:
	void Initialize(const char* assetName, const float width, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation);
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
// UI桁表示(スコア表示などで使用)
// ============================================
class UIDigit : public UIBase
{
private:
	/** 画像表示機能の可変長配列 */
	std::vector<SpriteRender*> m_renderList;
	/** 表示される数字 */
	int m_number;
	int m_requestNumber;
	int m_digit;
	/** 数字表示に必要な画像が入った */
	std::string m_assetPath;

	// あとでかえて
	int w;
	int h;



public:
	UIDigit();
	~UIDigit();


public:
	virtual bool Start() override;
	virtual void Update() override;
	virtual void Render(RenderContext& rc) override;


public:
	/**
	 * ・アセットの名前
	 * ・何桁かの情報（数）
	 * ・表示する数
	 * ・横
	 * ・高さ
	 * ・位置
	 * ・大きさ
	 * ・回転
	 */
	void Initialize(const char* assetPath, const int digit, const int number, const float widht, const float height, const Vector3& position, const Vector3& scale, const Quaternion& rotation);

	/** 数字を設定 */
	void SetNumber(const int number) { m_requestNumber = number; }

	// @todo for test
	//void SetCustomChar(int targetDigit, const std::string& assetPath);

	std::vector<SpriteRender*>& GetSpriteRenderList() { return m_renderList; }

	void ForEach(const std::function<void(SpriteRender*)>& func)
	{
		for (auto* render : m_renderList) {
			func(render);
		}
	}


private:
	void UpdateNumber(const int targetDigit, const int number);
	void UpdatePosition(const int index);

	/** 対象の桁 */
	int GetDigit(int digit);
};




// ============================================
// キャンバス
// ============================================


/**
 * 絵を書くキャンバスのイメージ
 * UIを作るときにこのクラスを作ってください
 */
class UICanvas : public UIBase
{
	friend class UIBase;
	friend class UIImage;
	friend class UIGauge;
	friend class UIIcon;
	friend class UIText;
	friend class UIButton;


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