#ifndef WEAPON_H
#define WEAPON_H

#include "PowerUp.h"

class Weapon : public PowerUp
{
public:
    Weapon(const char* name, Vertex position) :
        PowerUp(name, position)
    {
        mType = WEAPON;
		mDurablity = 100.00f;
		mDamage = 20.0f;
    }
	const void setDurablity(float d)
	{
		mDurablity = d;
	}
	float getDurablity()
	{
		return mDurablity;
	}
	const void setDamage(float d)
	{
		mDamage = d;
	}
	float getDamage()
	{
		return mDamage;
	}
protected:
		float mDamage;
		float mDurablity;;
};


#endif // WEAPON_H

