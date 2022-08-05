#ifndef PATH_NODE_H
#define PATH_NODE_H

#include "Vertex.h"

#include <vector>
#include <algorithm>

class PathNode;
typedef std::vector<PathNode*> PathNodes;

class PowerUp;
typedef std::vector<PowerUp*> PowerUps;

class PathNode
{
public:
    PathNode(const char* name, Vertex position) :
        mPosition(position)
    {
        mName = new char [strlen(name)];
        strcpy(mName, name);
    }

	PathNode()
	{

	}
    
    ~PathNode()
    {
    }

    void AddLink(PathNode *pathNode)
    {
        mLinks.push_back(pathNode);
    }
    
    void RemoveLink(PathNode *pathNode)
    {
        PathNodes::iterator i = std::find(mLinks.begin(), mLinks.end(), pathNode);
        mLinks.erase(i);
    }

    void AddPowerUp(PowerUp *powerUp)
    {
        mPowerUps.push_back(powerUp);
    }
    
    void RemovePowerUp(PowerUp *powerUp)
    {
        PowerUps::iterator i = std::find(mPowerUps.begin(), mPowerUps.end(), powerUp);
        mPowerUps.erase(i);
    }

    const char* GetName() const
    {
        return(mName);
    }

    const PathNodes& GetLinks() const
    {
        return(mLinks);
    }

    const PowerUps& GetPowerUps() const
    {
        return(mPowerUps); 
    }

	void SetPosition(float x, float y)
	{
		mPosition = Vertex(x, y, 0);
	}

	const Vertex GetPosition()
	{
		return mPosition;
	}

	void setDistance(float d)
	{
		mDistance = d;
	}

	const float getDistance()
	{
		return mDistance;
	}

protected:
    Vertex      mPosition;
    char*       mName;

    PathNodes   mLinks;
    PowerUps    mPowerUps;

	float mDistance;
};

#endif // PATH_NODE_H
