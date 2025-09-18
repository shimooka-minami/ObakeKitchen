#pragma once

class Player;
class PlayerStatus;

class IState;
class IdleState;

enum enPlayerState
{
	enPlayerIdle,
	enPlayerWalk,
	enPlayerDash,
	enPlayerNum,
};


class StateMachine
{
private:
	/** ���̃X�e�[�^�X*/
	IState* m_currentState;
	/** �X�e�[�g�̃��X�g*/
	IState* m_stateList[enPlayerNum];

	/** �v���C���[�̕��������ϐ�(�X�e�B�b�N���͂̕���) */
	Vector3 m_direction = Vector3::Zero;

	/** ���W */
	Vector3 m_position = Vector3::Zero;
	/** �g�k */
	Vector3 m_scale = Vector3::One * 1.0f;
	/** ��] */
	Quaternion m_rotation = Quaternion::Identity;

	/** ��l������ ����{�G��Ȃ�! */
	Player* m_owner = nullptr;
	/** ��l�̃X�e�[�^�X������ */
	PlayerStatus* m_ownerStatus = nullptr;

	/** �_�b�V���ł��邩�ǂ��� */
	bool m_isDash = false;


public:
	StateMachine();
	~StateMachine();
	
	/** �X�V */
	void Update();
	/** �X�e�[�g�ύX */
	void ChangeState();


private:
	/** �ύX����X�e�[�g���擾 */
	IState* GetChangeState() const;

	/** ������ԂɕύX�ł��邩 */
	bool CanChangeWalk() const;
	/** �����ԂɕύX�ł��邩 */ 
	bool CanChangeDash() const; 


public:
	/** �����ݒ�p�̊֐� */
	void Setup(Player* owner);

public:
	/** ��l�̃X�e�[�^�X�擾 */
	PlayerStatus* GetOwnerStatus() { return m_ownerStatus; }

	/** ��l�̃A�j���[�V�����𐶐� */
	void PlayAnimation(const int animationIndex);


public:
	/** �����̃Q�b�^�[ */
	const Vector3& GetDirection() { return m_direction; }
	/** �����̃Z�b�^�[ */
	void SetDirection(const Vector3& direction) { m_direction = direction; }

	/**
	 * ���W�擾
	 */
	inline const Vector3& GetPosition() const { return m_position; }
	/**
	 * ���W�ݒ�
	 */
	inline void SetPosition(const Vector3& position) { m_position = position; }

	/**
	 * �g�k�擾
	 */
	inline const Vector3& GetScale() const { return m_scale; }
	/**
	 * �g�k�ݒ�
	 */
	inline void SetScale(const Vector3& scale) { m_scale = scale; }

	/**
	 * ��]�擾
	 */
	inline const Quaternion& GetRotation() const { return m_rotation; }
	/**
	 * ��]�ݒ�
	 */
	inline void SetRotation(const Quaternion& rotation) { m_rotation = rotation; }

	/**
	 * �_�b�V���̐ݒ�
	 */
	inline void SetDash(const bool isDash) { m_isDash = isDash; }
};

