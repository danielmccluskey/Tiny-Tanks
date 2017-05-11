#ifndef _OTHERFUNCTIONS_H_
#define _OTHERFUNCTIONS_H_


/*SpriteMatrix
[0] = Scales X Axis
[1] = Skews +RightUp -RightDown
[2] = Crops Sprites X axis +Right -Left
[3] = ?????
[4] = Skews -Left +Right
[5] = Scales Y Axis
[6] = ?????
[7] =
[8] =
[9] =
[10] =
[11] =
[12] = XPOS
[13] = YPOS
*/
struct AABB;

class OtherFunctions
{
public:

	~OtherFunctions()
	{
	}
	friend class Vector2;

	static float GetSpriteWidth(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	//Function to return the height of a given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	static float GetSpriteHeight(int a_iSpriteWidth, int a_iSpriteHeight, float a_fRad);
	//Function to Get just the Xpos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	static float GetSpriteXPos(int a_uiSpriteID);
	//Function to Get just the Ypos of a sprite.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	static float GetSpriteYPos(int a_uiSpriteID);
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	static float GetBearingRad(Vector2 &a_V1, Vector2 &a_V2);
	//Gets the Angle between two Vector2 co-ordinates. Mainly Used for rotating tank turret.
	//Equation used - http://wikicode.wikidot.com/get-angle-of-line-between-two-points
	static float GetBearingDeg(Vector2 &a_V1, Vector2 &a_V2);

	//Sets the rotation to a certain angle instead of incrementing it like UG::SetSpriteRotation does.
	//Used from Daniel Budworth-Mead's UGFW++ linked on the Facebook group http://pastebin.com/fHGNgjrL
	//Will Convert to 4x4 Matrix later.
	static void SetRotationRad(float a_fRad, int a_iSpriteID);
	//Sets the rotation to a certain angle in Degrees instead of incrementing it like UG::SetSpriteRotation does.
	static void SetRotationDeg(float a_fDeg, int a_iSpriteID);
	static Vector2 GetForwardVector(float a_fDeg);

	static int GetMapTile(int a_iTileWidth, Vector2 a_vPos, int a_iCollisionMap[]);

	//Function to cast a ray at a sprite from anotherto see if they can see each other.
	static bool RayCast(int a_iSpriteIDEnemy, int a_iSpriteIDPlayer, int a_iCollisionMap[]);

	static Vector2 GetMousePosition();

	

	

};

namespace DANM //Incase other includes use the same function names as my functions
{
	//Function that returns the width of the given sprite.
	//Equation from Stack overflow - http://stackoverflow.com/a/6657768
	

}


#endif // _MATHUTIL_H_