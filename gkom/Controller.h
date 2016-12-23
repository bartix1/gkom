#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Controller
{
public:
	Controller();
	glm::mat4 computeRotation();
	glm::mat4 computeDistance();
	bool isMoving() const;
	bool isRotating() const;
	float getRotation() const;
	float getDistance() const;
	void setMoving(bool);
	void setRotating(bool);
private:
	float current_rot;
	float current_distance;
	bool moving;
	bool rotating;
};
