// ----------------------------------------------------------------
// From Game Programming in C++ by Sanjay Madhav
// Copyright (C) 2017 Sanjay Madhav. All rights reserved.
// 
// Released under the BSD License
// See LICENSE in root directory for full details.
// ----------------------------------------------------------------

#include "Asteroid.h"
#include "SpriteComponent.h"
#include "PhysicsComponent.h"
#include "Game.h"
#include "Random.h"
#include "CircleComponent.h"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	// 어디서 호출이 될 것인지??
	Vector2 randPos = Random::GetVector(Vector2(0.f,0.f),Vector2(0.0f, 200.0f));
	SetPosition(randPos);

	//SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	// Create a sprite component
	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	/*MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(150.0f);*/

	PhysicsComponent* pc = new PhysicsComponent(this);
	pc->SetUseGravity(true);
	pc->AddForce(Vector2(20000.f, 0.f));
	pc->SetMass(5.f);


	// Create a circle component (for collision)
	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
