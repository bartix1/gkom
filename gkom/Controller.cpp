#include "Controller.h"

Controller::Controller()
{
	current_rot = 0.52358f;
	current_distance = -5.0f;
	moving = false;
	rotating = false;
	move_direction = -1;
	rotate_direction = -1;
	current_height = 0;
}

void Controller::computePosition()
{
	if ((rotate_direction == 1 && current_height >= 2.0f) || (rotate_direction == -1 && current_height <= -1.5f))
	{
		rotating = false;
		return;
	}
	computeRotation();
	computeHeight();
}

void Controller::computeRotation()
{
	current_rot += rotate_speed * rotate_direction;
	if (current_rot >= 2 * 3.1415)
		current_rot -= 2 * 3.1415;
	else if (current_rot <= 2 * 3.1415)
		current_rot += 2 * 3.1415;
}

void Controller::computeDistance()
{
	current_distance += horizontal_speed * move_direction;
	if (current_distance >= -2.5f || current_distance <= -5.0f)
		moving = false;
}

void Controller::computeHeight()
{
	current_height += vertical_speed * rotate_direction;
}

void Controller::moveControl()
{
	if (rotating || moving)
		return;
	move_direction = -move_direction;
	moving = true;
}

void Controller::rotateControl(int dir)
{
	//std::lock_guard<std::mutex> lock(mutex);
	std::unique_lock<std::mutex> lock(mutex, std::try_to_lock);
	if (!lock.owns_lock()) {
		return;
	}
	if (moving)
		return;
	// HOLDING NUT
	if (current_distance >= -2.5f)
	{
		//HEIGHT BOUNDARIES
		if ((dir == 1 && current_height >= 2.0f) || (dir == -1 && current_height <= -1.5f))
			return;

		//STOP-START ROTATING
		if (dir == rotate_direction)
			rotating = !rotating;
		//CHANGE DIRECTION
		else
		{
			rotating = true;
			rotate_direction = dir;
		}
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

glm::mat4 Controller::getWrench() const
{
	glm::mat4 WMM(1.0);
	glm::vec3 tr(0, current_height, current_distance);
	glm::vec3 rot(0, 1, 0);
	WMM = glm::rotate(WMM, current_rot, rot);
	WMM = glm::translate(WMM, tr);
	return WMM;
}

glm::mat4 Controller::getNut() const
{
	glm::mat4 NMM(1.0);
	glm::vec3 tr(0, current_height, 0);
	glm::vec3 rot(0, 1, 0);
	NMM = glm::rotate(NMM, current_rot - 0.52358f, rot);
	NMM = glm::translate(NMM, tr);
	return NMM;
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

float Controller::getHeight() const
{
	return current_height;
}

void Controller::setMoving(bool x)
{
	moving = x;
}

void Controller::setRotating(bool x)
{
	rotating = x;
}
