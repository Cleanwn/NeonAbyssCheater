#include "pch.h"
#include "GameEntry.h"
#include "ProcessUtil.h"

CString GameEntry::getGameName() const
{
	return process_name;
}

CString GameEntry::getGameMainClass() const
{
	return process_class;
}

DWORD GameEntry::getGameProcessID()
{
	DWORD tmpProcessID = ProcessUtil::GetProcessIDByTitle(getGameName(), getGameMainClass());
	if (tmpProcessID != proccessID) {	// 更新
		proccessID = tmpProcessID;
		pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, proccessID);
		auto p = ProcessUtil::GetModule(proccessID, unity_player_dll.GetBuffer());
		upd_base = p.first;
	}

	return proccessID;
}

BOOL GameEntry::isGameRunning()
{
	return getGameProcessID() != 0;
}

std::map<std::string, std::any> GameEntry::getHeroBasicInfo()
{
	std::map<std::string, std::any> ans;
	if (isGameRunning()) {
		QWORD roleBase = ProcessUtil::ReadMultiLevelPointer(pHandle, upd_base, BASIC_INFO_OFFSET);
		for (auto i : basic_map) {
			QWORD offset = i.second.first;
			std::string typ = i.second.second;
			QWORD eAddr = ProcessUtil::ReadMultiLevelPointer(pHandle, roleBase, { 0, offset });
			if (typ == T_DOUBLE) ans[i.first] = ProcessUtil::Read<double>(pHandle, eAddr);
			else if (typ == T_FLOAT) ans[i.first] = ProcessUtil::Read<float>(pHandle, eAddr);
		}
	}
	return ans;
}

void GameEntry::toggleFixedEntry(std::string key, bool addOrDel)
{
	if (basic_map.find(key) != basic_map.end() && isGameRunning()) {
		fixedSetMu.lock();
		if (addOrDel) {
			// 只添加不更新
			if (fixedSet.find(key) == fixedSet.end()) {
				QWORD roleBase = ProcessUtil::ReadMultiLevelPointer(pHandle, upd_base, BASIC_INFO_OFFSET);
				auto keyInfo = basic_map.at(key);
				QWORD offset = keyInfo.first;
				std::string typ = keyInfo.second;
				QWORD eAddr = ProcessUtil::ReadMultiLevelPointer(pHandle, roleBase, { 0, offset });
				if (typ == T_DOUBLE) fixedSet[key] = ProcessUtil::Read<double>(pHandle, eAddr);
				else if (typ == T_FLOAT) fixedSet[key] = ProcessUtil::Read<float>(pHandle, eAddr);
			}
		}
		else fixedSet.erase(key);
		fixedSetMu.unlock();
	}
}

void GameEntry::fixEntriesValue()
{
	if (isGameRunning()) {
		fixedSetMu.lock();
		for (auto item : fixedSet) {
			if (item.second.type().name() == T_DOUBLE) writeBasicInfo<double>(item.first, std::any_cast<double>(item.second));
			else if(item.second.type().name() == T_FLOAT) writeBasicInfo<float>(item.first, std::any_cast<float>(item.second));
		}
		fixedSetMu.unlock();
	}
}
