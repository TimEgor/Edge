#include "PhysicsScene.h"

Edge::PhysicsScene::PhysicsScene(const PhysicsWorldReference& world)
	: m_world(world) {}

bool Edge::PhysicsScene::init()
{
	return true;
}

void Edge::PhysicsScene::release()
{
}

void Edge::PhysicsScene::update(float deltaTime)
{
}

Edge::PhysicsWorldWeakReference Edge::PhysicsScene::getWorld()
{
	return m_world;
}
