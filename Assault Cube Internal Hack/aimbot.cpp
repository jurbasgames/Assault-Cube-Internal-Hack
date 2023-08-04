#include "pch.h"
#include "mem.h"
#include "aimbot.h"
#include "offsets.h"
#include <cmath>
#include <limits>
#include <iostream>

# define M_PI           3.14159265358979323846  /* pi */

std::vector<float> aim::getNearEnemyPos(uintptr_t localPlayerPtr, uintptr_t entityList, int totalPlayers) {
	int i;
	std::vector<float> playerPos = { *(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerX}) ,*(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerY }) ,*(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerZ }) };
	int playerTeam = *(int*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { teamOffset });
	std::vector<float> target = {}; // define a default position for the target
	float minDistance = std::numeric_limits<float>::infinity(); // define a very large default distance

	for (i = 1; i <= totalPlayers; i++) {
		uintptr_t enemy = mem::FindDMAAddy(entityList, { (unsigned int)(0x4 * i) });
		int enemyHealth = *(int*)mem::FindDMAAddy((uintptr_t)enemy, { PlayerHealth });
		int enemyTeam = *(int*)mem::FindDMAAddy((uintptr_t)enemy, { teamOffset });

		if (enemyTeam != playerTeam && enemyHealth > 0) {
			std::vector<float> enemyPos = { *(float*)mem::FindDMAAddy((uintptr_t)enemy, { playerX}) ,*(float*)mem::FindDMAAddy((uintptr_t)enemy, { playerY }) ,*(float*)mem::FindDMAAddy((uintptr_t)enemy, { playerZ }) };
			float distance = std::sqrt(std::pow(enemyPos[0] - playerPos[0], 2) + std::pow(enemyPos[1] - playerPos[1], 2) + std::pow(enemyPos[2] - playerPos[2], 2));
			if (distance < minDistance) {
				target = enemyPos; // set the target to the position of the closest enemy
				minDistance = distance; // update the minimum distance
			}
		}
	}

	return target; // return the coordinates of the closest enemy
}

void aim::pointCursorToPos(uintptr_t localPlayerPtr, std::vector<float> enemyPosition) {
	// Get the current position of the local player
	std::vector<float> playerPosition = { *(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerX}) ,*(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerY }) ,*(float*)mem::FindDMAAddy((uintptr_t)localPlayerPtr, { playerZ }) };
	float dx = enemyPosition[0] - playerPosition[0];
	float dy = enemyPosition[1] - playerPosition[1];
	double angleYaw = atan2(dy, dx) * 180 / M_PI;

	double distance = sqrt(dx * dx + dy * dy);
	float dz = enemyPosition[2] - playerPosition[2];
	double anglePitch = atan2(dz, distance) * 180 / M_PI;

	*(float*)mem::FindDMAAddy(localPlayerPtr, { playerPitch }) = (float)anglePitch;
	*(float*)mem::FindDMAAddy(localPlayerPtr, { playerYaw }) = (float)angleYaw + 90;
}
