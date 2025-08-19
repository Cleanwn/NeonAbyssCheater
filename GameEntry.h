#pragma once
#include "ProcessUtil.h"
#include "pch.h"
#include "any"
#include "mutex"
// Learn from: https://github.com/Geedium/pvz-trainer

#define GAME_BASIC_MONEY "money"
#define GAME_BASIC_HP "hp"
#define GAME_BASIC_CRYSTAL "crystal"
#define GAME_BASIC_SHIELD "shield"
#define GAME_BASIC_ICE_BOMB "iceBomb"
#define GAME_BASIC_NORMAL_BOMB "normalBomb"
#define GAME_BASIC_ALCOHOL_BOMB "alcoholBomb"
#define GAME_BASIC_FIRE_BOMB "fireBomb"
#define GAME_BASIC_NORMAL_KEY "normalKey"
#define GAME_BASIC_RAINBOW_KEY "rainbowKey"
#define GAME_BASIC_FAITH_GEMS "faithGems"
#define GAME_BASIC_JUMP_LEVEL "jumpLevel"
#define GAME_BASIC_JUMP_BASE_HEIGHT "jumpHeight"
#define GAME_BASIC_JUMP_COUNT "jumpCount"
#define GAME_BASIC_RUN_SPEED "runSpeed"

#define GAME_BASIC_BULLET_RADIUS "bulletRadius"
#define GAME_BASIC_BULLET_ATTACK_SPEED "bulletSpeed"
#define GAME_BASIC_BULLET_FISSION_COUNT "bulletFisson"

#define GAME_BASIC_XRAY_EYE "XrayEye"

const std::string T_DOUBLE = "double";
const std::string T_FLOAT = "float";

class GameEntry
{
private:
	CString process_name = "Neon Abyss";
	CString process_class = "UnityWndClass";
	CString unity_player_dll = "UnityPlayer.dll";

	DWORD proccessID = 0;
	// unity_player_dll's base address
	QWORD upd_base = 0;
	// the HANDLE of process
	HANDLE pHandle = 0;

	// ===== Basic info part ======
	const std::vector<QWORD> BASIC_INFO_OFFSET = { 0x01542940, 0, 0x10, 0x28, 0x40, 0x18, 0x18, 0x10, 0x18 };
	// name: (addr, type)
	const std::map<std::string, std::pair<QWORD, const std::string>> basic_map = {
		{GAME_BASIC_MONEY, {0x210, T_DOUBLE}}, { GAME_BASIC_HP, {0x258, T_DOUBLE} }, { GAME_BASIC_CRYSTAL, {0x270, T_DOUBLE} }, { GAME_BASIC_SHIELD, {0x288, T_DOUBLE} },
		{ GAME_BASIC_NORMAL_BOMB, {0x2a0, T_DOUBLE} }, { GAME_BASIC_ICE_BOMB, {0x450, T_DOUBLE} }, { GAME_BASIC_JUMP_LEVEL, {0x3f0, T_DOUBLE} }, { GAME_BASIC_RAINBOW_KEY, {0x468, T_DOUBLE} },
		{ GAME_BASIC_NORMAL_KEY, {0x510, T_DOUBLE} }, { GAME_BASIC_ALCOHOL_BOMB, {0x558, T_DOUBLE} }, { GAME_BASIC_FIRE_BOMB, {0xc30, T_DOUBLE} },
		{ GAME_BASIC_JUMP_BASE_HEIGHT, {0x4f8, T_DOUBLE} }, { GAME_BASIC_RUN_SPEED, {0x6d8, T_DOUBLE} }, { GAME_BASIC_BULLET_RADIUS, {0x870, T_DOUBLE} },
		{ GAME_BASIC_BULLET_ATTACK_SPEED, {0x8a4, T_FLOAT} }, { GAME_BASIC_XRAY_EYE, {0xa50, T_DOUBLE}}, {GAME_BASIC_BULLET_FISSION_COUNT, {0x858, T_DOUBLE}},
		{ GAME_BASIC_JUMP_COUNT, {0xA80, T_DOUBLE}}, {GAME_BASIC_FAITH_GEMS, {0xCD8, T_DOUBLE}}
	};

	// Use to fix the number of cheater entries.
	std::map<std::string, std::any> fixedSet;
	std::recursive_mutex fixedSetMu;

public:
	/**
	Get the name of neon abyss process
	*/
	CString getGameName() const;

	// Return the class name of game window
	CString getGameMainClass() const;

	DWORD getGameProcessID();
	/*
	Return if the game is running
	*/
	BOOL isGameRunning();
	/*
	Get the player's hero basic infomation when in battle mode.
	Return: map -> (type: (key, type-value))
	*/
	std::map<std::string, std::any> getHeroBasicInfo();

	/*
	Toggle fixSet in cheater sheet.(Similar to the fix function in Cheat Engine.)
	1. Key: the cheat entry key
	2. addOrDel: Add to fixedSet if true, false to delete.
	*/
	void toggleFixedEntry(std::string key, bool addOrDel);

	/*
	Fix the key entries in fixSet;
	*/
	void fixEntriesValue();

	/*
	Write the basic hero info of neon abyss.
	*/
	template<typename T>
	inline void writeBasicInfo(std::string key, T value) {
		if (isGameRunning()) {
			fixedSetMu.lock();
			if (fixedSet.find(key) != fixedSet.end()) {
				fixedSet[key] = value;
			}
			fixedSetMu.unlock();
			QWORD roleBase = ProcessUtil::ReadMultiLevelPointer(pHandle, upd_base, BASIC_INFO_OFFSET);
			QWORD eAddr = ProcessUtil::ReadMultiLevelPointer(pHandle, roleBase, { 0, basic_map.at(key).first });
			ProcessUtil::Write<T>(pHandle, eAddr, value);
		}
	}

	/*
	Increment or decrement a info.
	*/
	template<typename T>
	void incrOrDecrBasicInfo(std::string key, bool incr = true, int incrStep = 1) {
		if (isGameRunning()) {
			fixedSetMu.lock();
			if (fixedSet.find(key) != fixedSet.end()) {
				// 在固定集合中则添加即可。
				auto typName = fixedSet[key].type().name();
				if (!incr) incrStep = -incrStep;
				if (typName == T_DOUBLE) fixedSet[key] = std::any_cast<double>(fixedSet[key]) + incrStep;
				else if (typName == T_FLOAT) fixedSet[key] = std::any_cast<float>(fixedSet[key]) + incrStep;
			}
			else 
			{
				QWORD roleBase = ProcessUtil::ReadMultiLevelPointer(pHandle, upd_base, BASIC_INFO_OFFSET);
				QWORD eAddr = ProcessUtil::ReadMultiLevelPointer(pHandle, roleBase, { 0, basic_map.at(key).first });
				T value = ProcessUtil::Read<T>(pHandle, eAddr);
				value = incr ? value + incrStep : value - incrStep;
				ProcessUtil::Write<T>(pHandle, eAddr, value);
			}
			fixedSetMu.unlock();
		}
	}

};

