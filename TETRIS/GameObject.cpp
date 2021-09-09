
#include "framework.h"

GameObject::GameObject(string tag, string name, bool active, float px, float py)
{
	this->tag	 = tag;
	this->name	 = name;
	this->active = active;

	this->px = px;
	this->py = py;	

	this->dead = false; //생성자에서..게임오브젝트가 dead가 아님
}

GameObject::~GameObject()
{
	//총돌체...제거하기//
	for (int i = 0; i < boxCollider.size(); i++)
	{
		delete boxCollider[i];
		
	}

	boxCollider.clear();
}

string GameObject::getTag()
{
	return tag;
}

string GameObject::getName()
{
	return name;
}

bool  GameObject::getActive()
{
	return active;
}

float GameObject::getPx()
{
	return px;
}

float GameObject::getPy()
{
	return py;
}

bool GameObject::getDead()
{
	return dead;
}

void GameObject::setTag(string tag)
{
	this->tag = tag;
}

void GameObject::setName(string name)
{
	this->name = name;
}

void GameObject::setActive(bool active)
{
	this->active = active;
}

void GameObject::setPx(float px)
{
	//게임오브젝트의..새로운 좌표까지의 이동량//
	float dx = px - this->px;

	//게임오브젝트...x좌표 지정//
	this->px = px;

	//충돌체...x 위치..변경..적용하기//
	for (int i = 0; i < boxCollider.size(); i++)
	{
		boxCollider[i]->translate(dx, 0);
	}
}

void GameObject::setPy(float py)
{
	//게임오브젝트의..새로운 좌표까지의 이동량//
	float dy = py - this->py;

	//게임오브젝트...y좌표 지정//
	this->py = py;

	//충돌체...y 위치..변경..적용하기//
	for(int i=0 ; i < boxCollider.size() ; i++)
	{
		boxCollider[i]->translate(0, dy);
	}
}

void GameObject::setDead(bool dead)
{
	this->dead = dead;
}

void GameObject::start()
{}

void GameObject::update()
{}

void GameObject::draw()
{}

void GameObject::translate(float x, float y)
{
	//게임오브젝트..이동시키기//
	px = px + x;
	py = py + y;

	//충돌체..이동시키기//
	for(int i=0 ; i < boxCollider.size() ; i++)
	{
		boxCollider[i]->translate(x, y);
	}
}

void GameObject::instantiate(GameObject* o, int layer)
{
	ObjectManager::instantiate(o, layer);
}

void GameObject::destroy(GameObject* o)
{
	ObjectManager::destroy(o);
}

void GameObject::addBoxCollider2D(float x, float y, float width, float height)
{
	boxCollider.push_back( new BoxCollider2D(x+px, y+py, width, height) );
}

vector<BoxCollider2D*> GameObject::getBoxCollider2D()
{
	return boxCollider;
}

void GameObject::onDrawGizmos()
{
	for(int i=0 ; i < boxCollider.size(); i++)
	{
		//충돌체..표시하기 - 충돌체..기즈모//
		float x, y, width, height;
		boxCollider[i]->getBox(x, y, width, height);

		float x0 = x, y0 = y, x1 = x + width, y1 = y + height;
		drawRect(x0, y0, x1, y1, 255, 0, 0);
	}
}

void GameObject::onTriggerStay(GameObject* other)
{}