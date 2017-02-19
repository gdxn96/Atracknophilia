#include "stdafx.h"
#include "Controller.h"
#include "EntityFactory.h"

PlayerControllerComponent::PlayerControllerComponent(int id) : IControllerComponent(id)
{
	InputManager::GetInstance()->AddKey(EventListener::ARROW_LEFT, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->ApplyForceToCenter(b2Vec2(-10000, 0), true);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::ARROW_RIGHT, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->ApplyForceToCenter(b2Vec2(10000, 0), true);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_B, new ReleaseCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			EntityFactory::SpawnSlowShot(c->body->GetPosition().x, c->body->GetPosition().y, 5, 5, 32, ID);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_LEFT, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->ApplyForceToCenter(b2Vec2(-10000, 0), true);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_DPAD_RIGHT, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->ApplyForceToCenter(b2Vec2(10000, 0), true);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new HoldCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c) {
			c->body->SetGravityScale(-1);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new PressCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c && c->body->GetContactList() && c->body->GetGravityScale() < 0) {
			c->body->SetGravityScale(1);
		}
	}));

	InputManager::GetInstance()->AddKey(EventListener::BUTTON_A, new ReleaseCommand([&]() {
		auto c = getComponent<Box2DComponent>();
		if (c && !c->body->GetContactList()) {
			c->body->SetGravityScale(1);
		}
	}));
}

void PlayerControllerComponent::process()
{
	auto vec = InputManager::GetInstance()->GetLeftStickVectorNormal();
	auto c = getComponent<Box2DComponent>();
	c->body->ApplyForceToCenter(b2Vec2(vec.x * 10000, 0), true);
}