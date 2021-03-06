#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <mutex>
#include <thread>
#include <chrono>

class Controller
{
public:
	Controller();
	void computePosition();
	void computeDistance();
	void moveControl();
	void rotateControl(int dir);
	glm::mat4 getWrench() const;
	glm::mat4 getNut() const;


	bool isMoving() const;
	bool isRotating() const;
	float getRotation() const;
	float getDistance() const;
	float getHeight() const;
	void setMoving(bool);
	void setRotating(bool);
private:
	void computeRotation();
	void computeHeight();

	float current_rot;
	float current_distance;
	float current_height;
	bool moving;
	bool rotating;
	int move_direction; // 1 - towards nut, -1 - opposite dir
	int rotate_direction; // 1 - left, -1 - right

	const float rotate_speed = 0.001f;
	const float horizontal_speed = 0.002f;
	const float vertical_speed = 0.0002f;


	std::mutex mutex;
};
