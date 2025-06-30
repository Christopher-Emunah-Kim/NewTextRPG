#pragma once
#include "../../Common.h"


enum class EInputEvent
{
	NONE = 0,
	PRESSED,
	RELEASED,
	HOLD,
	MAX_COUNT
};

enum class EMoveDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	MAX_COUNT
};

enum class EItemType : int8
{
	None = 0,
	Weapon,
	Armor,
	Consumable,
	Material,
	Max
};

enum class EBattleState : int8
{
	BattleStart,
	BattleEnd,
	PlayerTurn,
	MonsterTurn,
	WaitForPlayerInput
};

enum class EKeyCode : uint8
{
	RETURN = 0x0D,
	SPACE = 0x20,
	LEFT = 0x25,
	UP = 0x26,
	RIGHT = 0x27,
	DOWN = 0x28,

	NUM_0 = 0x30,
	NUM_1 = 0x31,
	NUM_2 = 0x32,
	NUM_3 = 0x33,
	NUM_4 = 0x34,
	NUM_5 = 0x35,
	NUM_6 = 0x36,
	NUM_7 = 0x37,
	NUM_8 = 0x38,
	NUM_9 = 0x39,

	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,

	MAX_COUNT
};