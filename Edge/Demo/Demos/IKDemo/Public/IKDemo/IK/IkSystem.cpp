#include "IkSystem.h"

#include "EdgeCommon/Assert/AssertCore.h"

void EdgeDemo::IkSystem::clear()
{
	m_links.clear();
	m_joints.clear();
}

void EdgeDemo::IkSystem::addLink(IkLink* link)
{
	m_links.push_back(link);
}

void EdgeDemo::IkSystem::addJoint(IkJoint* joint)
{
	m_joints.push_back(joint);
}

void EdgeDemo::IkSystem::setEffectorLink(IkLink* effector)
{
	EDGE_ASSERT(effector);
	m_effector = effector;
}

void EdgeDemo::IkSystem::setRootLink(IkLink* root)
{
	EDGE_ASSERT(root);
	m_root = root;
}
