#pragma once

#include "Component.h"
#include "Math.h"


class PhysicsComponent : Component
{
public:
	PhysicsComponent(class Actor* owner, int updateOrder = 10);

	void Update(float deltaTime) override;

	void AddForce(Vector2 force);

	void SetMass(float mass);

	void SetUseGravity(bool use);

private:
	float mass;
	Vector2 sumOfForces;
	Vector2 acceleration;
	Vector2 velocity;
	Vector2 gravity; //중력, 매프레임마다 작용하도록
	bool useGravity;
};

