#include "PhysicsComponent.h"
#include "Actor.h"
#include "SDL.h"

PhysicsComponent::PhysicsComponent(Actor* owner, int updateOrder):
	Component(owner, updateOrder),
	sumOfForces(0.f,0.f),
	velocity(0.f,0.f),
	acceleration(0.f,0.f)
{
	mass = 1.f;
	gravity.x = 0.f;
	gravity.y = 980.f;

	useGravity = false;
}

void PhysicsComponent::SetMass(float mass)
{
	this->mass = mass;

	//중력 = 힘, F = mg
	gravity.y *= mass;
}

void PhysicsComponent::SetUseGravity(bool use)
{
	useGravity = use;
}

void PhysicsComponent::Update(float deltaTime)
{
	//중력이 작용되고있으면 매번 중력을 더해주기
	if (useGravity)
	{
		AddForce(gravity);
	}

	//힘이 추가되었으면 다시 계산하기
	//힘의 변동이 없으면 가속도 0


	//가속도 뽑아낸 뒤
	acceleration.x = sumOfForces.x / mass;
	acceleration.y = sumOfForces.y / mass;
	sumOfForces.x = 0.f;
	sumOfForces.y = 0.f;

	//속도계산
	velocity += acceleration * deltaTime;

	//포지션 바꾸기
	Vector2 pos = mOwner->GetPosition();
	pos += velocity * deltaTime;

	//창을 벗어날 때
	if (pos.y > 768.f)
	{
		//튕기게 하고싶다?
		velocity.y = -1 * velocity.y;
	}

	if (pos.x > 1024.f)
	{
		mOwner->SetState(Actor::State::EDead);
	}

	mOwner->SetPosition(pos);
}

void PhysicsComponent::AddForce(Vector2 force)
{
	sumOfForces += force;
}
