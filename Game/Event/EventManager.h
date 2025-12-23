/**
 * 客からの注文を管理する
 * 
 * EventManager.h
 */
#pragma once


/**
 * 注文の種類
 */
enum EnEventType
{
	enEventType_Tomato,		// トマト
	enEventType_Lettuce,	// レタス
	enEventType_Beef,		// 肉
};


/**
 * 注文書
 */
class Event : public Noncopyable
{
private:
	/** 注文の種類 */
	EnEventType m_type;


public:
	Event();
	~Event();

	void Initialize(const EnEventType type);
	void Update();


public:
	const EnEventType GetEventType() const { return m_type; }
};


/**
 * 注文管理`
 */
class EventManager
{
private:
	/** 注文書リスト */
	std::vector<Event*> m_eventList;


private:
	EventManager();
	~EventManager();


public:
	void Update();




	/**
	 * シングルトン関連
	 */
private:
	static EventManager* m_instance;


public:
	static void Create()
	{
		if (m_instance == nullptr) {
			m_instance = new EventManager();
		}
	}
	static bool IsAvailable()
	{
		return m_instance != nullptr;
	}
	static EventManager& Get()
	{
		return *m_instance;
	}
	static void Delete()
	{
		if (m_instance != nullptr) {
			delete m_instance;
			m_instance = nullptr;
		}
	}
};