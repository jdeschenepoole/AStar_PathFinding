//*************************************************************************
// Programmer: Joseph Deschnene-Poole
// Due Date: September 30th, 2011
// Project: AI Project 1
//*************************************************************************

#include "PathNode.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "Health.h"
#include "Armor.h"


#include <stdio.h>
#include <iostream>
#include <math.h>

static PathNodes sPathNodes;
static PowerUps sPowerUps;
extern bool PathFind(PathNodes *path, PathNode *currentNode, PowerUp pow, PowerUp::PowerUpType mType, PathNodes *openNodes);

float Heuristics( Vertex start, Vertex destination)
{
	return abs(start.x-destination.x) + abs(start.y-destination.y);
}

bool FindPowerUp(PathNodes& path, PowerUp::PowerUpType mType, PathNode *start)
{
    // Iterate Through The Powerups to get the nodes they are on
	float powerUpDist = 0.0f;
	PowerUp* pow;

	// first need to determine what IS the shortest powerup
	for(PowerUps::iterator itr = sPowerUps.begin(); itr != sPowerUps.end(); itr++)
	{
		float powerUpPos = abs( (*itr)->GetPosition().x + (*itr)->GetPosition().y);
		float startPos = abs(start->GetPosition().x + start->GetPosition().y);

		if(mType == (*itr)->GetPowerUpType() )
		{
			//this powerup is a win
			if( abs( startPos - powerUpPos) < powerUpDist || powerUpDist == 0.0f ) 
			{
				pow = (*itr);
				powerUpDist = abs( startPos - powerUpPos);
			}
		}
	}

	// Adds an estimated distance for each node to the power up selected above
	for (PathNodes::iterator itr = sPathNodes.begin(); itr != sPathNodes.end(); itr++)
	{
		float distance = Heuristics((*itr)->GetPosition(), pow->GetPosition());
		(*itr)->setDistance(distance);
	}

	// Prints Out Closet Power Up
	printf("%s ", pow->getName()); 

	bool found = false;

	while (!found)
	{
		PathNodes openNodes;	 // Nodes left open

	    found = PathFind(&path, start, *pow, mType, &openNodes);
		return found;
	}
	
	return(false); // No path found.
}

// Uses AStar to find the shorest path
bool PathFind(PathNodes *path, PathNode *currentNode, PowerUp pow, PowerUp::PowerUpType mType, PathNodes *openNodes)
{
	bool found = false;
	PathNodes openList;		 // CurrentList of Links
	openList = currentNode->GetLinks();

	//Checks if the currentNode has the PowerUpType
	PowerUps p = currentNode->GetPowerUps();
	for (PowerUps::iterator itr2 = p.begin(); itr2 != p.end(); itr2++)
	{
		if ( (*itr2)->GetPowerUpType() == mType )
		{
			path->push_back(currentNode);
			//found = true;
			return true;
		}
	}

	PathNode *nextNode = currentNode;

	// Finds the node with the shortest distance to the powerup
	for (PathNodes::iterator itr2 = openList.begin(); itr2 != openList.end(); itr2++)
	{
		
		if ((*itr2)->getDistance() <= nextNode->getDistance())
		{
			nextNode =  (*itr2);
		}
		openNodes->push_back(*itr2);
	}
 
	path->push_back(currentNode);
	found = PathFind(path, nextNode, pow, mType, openNodes);

	return found;
}
	
	/* Example:
    path.push_back(start);
    path.push_back(secondNode);
    path.push_back(endNode);
    return(true);
    */

// For this example, all links are symmetric.
inline void LinkNodes(PathNode *n1, PathNode *n2)
{
    n1->AddLink(n2);
    n2->AddLink(n1);
}

int main(int, char*[])
{
    sPathNodes.push_back(new PathNode("Node0", Vertex(300, 60, 0)));
    sPathNodes.push_back(new PathNode("Node1", Vertex(100, 60, 0)));
    sPathNodes.push_back(new PathNode("Node2", Vertex(80, 560, 0)));
    sPathNodes.push_back(new PathNode("Node3", Vertex(280, 650, 0)));
    sPathNodes.push_back(new PathNode("Node4", Vertex(300, 250, 0)));
    sPathNodes.push_back(new PathNode("Node5", Vertex(450, 400, 0)));
    sPathNodes.push_back(new PathNode("Node6", Vertex(450, 60, 0)));
    sPathNodes.push_back(new PathNode("Node7", Vertex(450, 400, 0)));

    LinkNodes(sPathNodes[1], sPathNodes[4]);
    LinkNodes(sPathNodes[0], sPathNodes[1]);
    LinkNodes(sPathNodes[0], sPathNodes[6]);
    LinkNodes(sPathNodes[0], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[4]);
    LinkNodes(sPathNodes[7], sPathNodes[5]);
    LinkNodes(sPathNodes[2], sPathNodes[4]);
    LinkNodes(sPathNodes[2], sPathNodes[3]);
    LinkNodes(sPathNodes[3], sPathNodes[5]);

    sPowerUps.push_back(new Weapon("Weapon0", Vertex(340, 670, 0)));
    sPathNodes[3]->AddPowerUp(sPowerUps[0]);    
    sPowerUps.push_back(new Weapon("Weapon1", Vertex(500, 220, 0)));
    sPathNodes[7]->AddPowerUp(sPowerUps[1]);    

    sPowerUps.push_back(new Health("Health0", Vertex(490, 10, 0)));
    sPathNodes[6]->AddPowerUp(sPowerUps[2]);    
    sPowerUps.push_back(new Health("Health1", Vertex(120, 20, 0)));
    sPathNodes[1]->AddPowerUp(sPowerUps[3]);    

    sPowerUps.push_back(new Armor("Armour0", Vertex(500, 360, 0)));
    sPathNodes[5]->AddPowerUp(sPowerUps[4]);    
    sPowerUps.push_back(new Armor("Armour1", Vertex(180, 525, 0)));
    sPathNodes[2]->AddPowerUp(sPowerUps[5]);    

    PathNodes path;

    if(!FindPowerUp(path, PowerUp::ARMOUR, sPathNodes[4]))
    {
        printf("No path found: IMPOSSIBLE!\n");
    }
    else
    {
        printf("Path found: ");

        for(PathNodes::iterator i = path.begin(); i != path.end(); ++i)
        {
            PathNode *n = *i;
            printf("%s ", n->GetName());
        }
	}
}