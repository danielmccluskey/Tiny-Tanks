#include "PathFinding.h"

PathFinding::PathFinding(void)
{
	bInitialisedStart = false;
	bFoundGoal = false;
}
PathFinding::~PathFinding(void)
{

}

void PathFinding::FindPath(Vector3 a_vCurrentPos, Vector3 a_vTargetPos)
{
	if (!bInitialisedStart)
	{
		for (int i = 0; i < vOpenList.size(); i++)
		{
			delete vOpenList[i];
		}
		vOpenList.clear();

		for (int i = 0; i < vClosedList.size(); i++)
		{
			delete vClosedList[i];
		}
		vClosedList.clear();
		for (int i = 0; i < vGoalPath.size(); i++)
		{
			delete vGoalPath[i];
		}
		vGoalPath.clear();

		SearchCell sStart;
		sStart.iX = 
	}
}