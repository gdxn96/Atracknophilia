#include "stdafx.h"
#include "Player.h"


Player::Player(int id, float x, float y, float w, float h) : IEntity(id,
{
	new CollisionBoxComponent(id, x, y, w, h, false),
	new PlayerControllerComponent(id),
	new InvertGravityOnEdgeComponent(id),
	new RacePositionComponent(id),
})
{

}