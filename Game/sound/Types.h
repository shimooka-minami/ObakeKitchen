/**
 * Types.h
 * サウンド用の定数など必要な情報を定義するファイル
 */
#pragma once
#include <string>


/** サウンドの種類 */
enum enSoundKind
{
	enSoundKind_SE = 0,
	enSoundKind_Cut = enSoundKind_SE,
	enSoundKind_Has,
	enSoundKind_Throw,
	enSoundKind_End,
	enSoundKind_Button,
	enSoundKind_SE_Max,
	enSoundKind_BGM = enSoundKind_SE_Max,
	enSoundKind_Game = enSoundKind_BGM,
	enSoundKind_Title,
	enSoundKind_Voice,
	enSoundKind_BootA = enSoundKind_Voice,
	enSoundKind_BootB,
	enSoundKind_Max,
	enSoundKind_None = enSoundKind_Max,
};


/** サウンドの情報の構造体 */
struct SoundInformation
{
	std::string assetPath;
	//
	SoundInformation(const std::string& path) : assetPath(path) {}
};


/** 情報を保持 */
static SoundInformation soundInformation[enSoundKind_Max] =
{
	// SE
	SoundInformation("Assets/sound/cut.wav"),
	SoundInformation("Assets/sound/has.wav"),
	SoundInformation("Assets/sound/throw.wav"),
	SoundInformation("Assets/sound/end.wav"),
	SoundInformation("Assets/sound/button.wav"),
	// BGM
	SoundInformation("Assets/sound/bgm/stage_1.wav"),
	SoundInformation("Assets/sound/bgm/title.wav"),
	// Voice
	SoundInformation("Assets/sound/voice/bootA.wav"),
	SoundInformation("Assets/sound/voice/bootB.wav"),
};

