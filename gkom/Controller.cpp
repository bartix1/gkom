#include "Controller.h"

Controller::Controller()
{
	current_rot = 0.52358f;
	current_distance = -5.0f;
	moving = false;
	rotating = false;
}

glm::mat4 Controller::computeRotation()
{
	glm::mat4 WMM(1.0);
	glm::vec3 tr(0, 0, -2.5);
	current_rot += 0.001f;
	if (current_rot >= 2 * 3.1415)
		current_rot -= 2 * 3.1415;
	glm::vec3 rot(0, 1, 0);
	WMM = glm::rotate(WMM, current_rot, rot);
	WMM = glm::translate(WMM, tr);
	return WMM;
}

glm::mat4 Controller::computeDistance()
{
	glm::mat4 WMM(1.0);
	glm::vec3 tr(0, 0, current_distance);
	current_distance += 0.001f;
	if (current_distance >= -2.5f)
		rotating = true;
	glm::vec3 rot(0, 1, 0);
	WMM = glm::rotate(WMM, current_rot, rot);
	WMM = glm::translate(WMM, tr);
	return WMM;
}

bool Controller::isMoving() const
{
	return moving;
}

bool Controller::isRotating() const
{
	return rotating;
}

float Controller::getRotation() const
{
	return current_rot;
}

float Controller::getDistance() const
{
	return current_distance;
}

void Controller::setMoving(bool x)
{
	moving = x;
}

void Controller::setRotating(bool x)
{
	rotating = x;
}
