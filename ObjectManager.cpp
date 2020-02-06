// w16016982	Stephen Dixon	KV6003

#include "ObjectManager.h"

ObjectManager::ObjectManager()
{}

void ObjectManager::addObject(GameObject* object)
{
	m_gameObjects.push_back(object);
}

void ObjectManager::update(float frameTime)
{
	for (auto &it : m_gameObjects) 
	{
		it->update();
	}
}

void ObjectManager::render()
{
	for (auto &it : m_gameObjects) 
	{
		it->render();
	}
}

void ObjectManager::processCollision()
{
	std::list<GameObject*>::iterator it1;
	std::list<GameObject*>::iterator it2;

	for (it1 = m_gameObjects.begin(); it1 != m_gameObjects.end(); it1++)
	{
		for (it2 = std::next(it1); it2 != m_gameObjects.end(); it2++)
		{
			if ((*it1)->GetRect().x + (*it1)->GetRect().w >= ((*it2)->GetRect().x) &&
			    (*it2)->GetRect().x + (*it2)->GetRect().w >= ((*it1)->GetRect().x) &&
			    (*it1)->GetRect().y + (*it1)->GetRect().h >= ((*it2)->GetRect().y) &&
				(*it2)->GetRect().y + (*it2)->GetRect().h >= ((*it1)->GetRect().y))
			{
				(*it1)->processCollision((*it2));
			}
		}
	}
}

void ObjectManager::clean()
{
	// Clean the inactive objects up
	for (GameObject* &nextObjectPointer : m_gameObjects)
	{
		if (nextObjectPointer->isActive() == false)
		{
			delete nextObjectPointer;
			nextObjectPointer = nullptr;
		}
	}

	auto it = std::remove(m_gameObjects.begin(), m_gameObjects.end(), nullptr);
	m_gameObjects.erase(it, m_gameObjects.end());
}

void ObjectManager::gameOver()
{
	// Clean the inactive objects up
	for (GameObject* &nextObjectPointer : m_gameObjects)
	{
		delete nextObjectPointer;
		nextObjectPointer = nullptr;
	}

	auto it = std::remove(m_gameObjects.begin(), m_gameObjects.end(), nullptr);
	m_gameObjects.erase(it, m_gameObjects.end());
}