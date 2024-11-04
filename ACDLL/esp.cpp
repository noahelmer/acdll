#include "esp.h"
#include "constants.h"
#include <stdio.h>
#include "geom.h"
#include <iostream>
const float FOV = 90;


bool isValidTarget(Player* player) {
	if (player->health > 100 || player->health <= 0) {
		return false;
	}
	return true;
}

Player* ESP::getNearestPlayer() { 
	Player * nearestPlayer = nullptr;
	float nearestDistance = 9999999.0f;
	for (int i = 1; i < numPlayers + 1; i++) {
		Player* player = players->players[i];
		std::cout << "health " << player->health << std::endl;
		if (!isValidTarget(player)) {
			continue;
		}
		float distance = localPlayerPtr->position.Distance(player->position);
		if (distance <= 0) {
			continue;
		}
		std::cout << "distance " << distance << " nearestDistance " << nearestDistance << std::endl;
		if (distance < nearestDistance) {
			nearestDistance = distance;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

void normalizeAngle(vec3& angle) {
	if (angle.x > 360)
		angle.x -= 360;
	if (angle.x < 0)
		angle.x += 360;
	if (angle.y > 90)
		angle.y -= 90;
	if (angle.y < -90)
		angle.y += 90;
}

Player* ESP::getNearestEntityAngle() {
	Vec3 playerAngle{ localPlayerPtr->yaw + 100, localPlayerPtr->pitch, 0 };
	normalizeAngle(playerAngle);
	Player* nearestPlayer = nullptr;
	float smallestAngle = 9999999.0f;

	for (int i = 1; i < numPlayers + 1; i++) {
		Player* player = players->players[i];
		if (!isValidTarget(player)) {
			continue;
		}
		vec3 targetAngle = CalcAngle(localPlayerPtr->position, player->position);
		vec3 angleDiff = playerAngle - targetAngle;
		normalizeAngle(angleDiff);
		float angleMagnitude = angleDiff.Length();
		if (angleMagnitude < smallestAngle) {
			smallestAngle = angleMagnitude;
			nearestPlayer = player;
		}
	}
	return nearestPlayer;
}

void ESP::aimbot() {
	if (!GetAsyncKeyState(VK_CONTROL))
		return;
	Player* target = getNearestEntityAngle();
	std::cout << "nearest player " << target << std::endl;
	Vec3 angle = CalcAngle(localPlayerPtr->position, target->position);

	std::cout << "angle x " << angle.x << std::endl;
	std::cout << "angle y " << angle.y << std::endl;
	angle.x += 180;
	normalizeAngle(angle);

	localPlayerPtr->yaw = angle.x;
	localPlayerPtr->pitch = angle.y;
}