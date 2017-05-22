//==============================================================================================================================
// Project: WiiTanks
// File: Turret.h
// Author: Daniel McCluskey
// Date Created: 07/01/17
// Brief: This is the header file used to create a turret for each the Playr and the enemies.
// Last Edited by: (See BitBucket Commits: https://bitbucket.org/Danielmclovin/ct4019-wii-tanks-daniel-mccluskey)
//==============================================================================================================================
#ifndef _TURRET_H_
#define _TURRET_H_
class Turret
{
public:
	Turret(char* a_cImagePath);
	int iSpriteID;//Sprite ID
	int iRotDeg = 0;//Rotation of turret.

};


#endif//_TURRET_H_