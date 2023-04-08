#pragma once
namespace aim {
	std::vector<float> getNearEnemyPos(uintptr_t localPlayerPtr, uintptr_t entityList, int totalPlayers);
	void pointCursorToPos(uintptr_t localPlayerPtr, std::vector<float> enemyPosition);
}