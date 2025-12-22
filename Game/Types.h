/**
 * Types.h
 * 定数などゲーム全体にかかわる定義を行う
 */
#pragma once


/** 最大プレイヤー数 */
static constexpr  uint8_t  MAX_PLAYER_NUM = 4;
/** NPC難易度 */
static constexpr uint8_t   NPC_TYPE_NUM = 3;


enum EnGameObjectPriority
{
	enGameObjectPriority_Default = 0,
	enGameObjectPriority_Fade = 100,
};


enum EnInteractType
{
	enInteractType_Cooking,
	enInteractType_Delivery,
	enInteractType_Plate,
};