#ifndef _PATHFINDING_H_
#define _PATHFINDING_H_
#include "Vector3.h"
#include <vector>
#include "SearchCell.h"

class PathFinding
{
public:
	PathFinding(void);
	~PathFinding(void);

	void FindPath(Vector3 a_vCurrentPos, Vector3 a_vTargetPos);
	Vector3 NextPathPos();
	void ClearOpenList() { vOpenList.clear(); }
	void ClearClosedList() { vClosedList.clear(); }
	void ClearPathToGoal() { vGoalPath.clear(); }

	bool bInitialisedStart;
	bool bFoundGoal;

private:
	void SetStartAndGoal(SearchCell a_sStart, SearchCell a_sGoal);
	void PathOpened(int a_iX, int a_iZ, float a_fCost, SearchCell *a_pParent);
	SearchCell *GetNextCell();
	void ContinuePath();

	SearchCell *pStartCell;
	SearchCell *pGoalCell;
	std::vector<SearchCell*> vOpenList;
	std::vector<SearchCell*> vClosedList;
	std::vector<Vector3*> vGoalPath;
};


#endif