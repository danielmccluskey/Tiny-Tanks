#include "UGFW.h"
#include "Enumerations.h"
#include <iostream>
#include <sstream>
#include <iomanip>


int main(int argv, char* argc[])
{
	
	if (UG::Create(1024, 768, false, "Pong", 100, 100))
	{
		
		UG::SetBackgroundColor(UG::SColour(0x2A, 0x57, 0x66, 0xFF));
		UG::AddFont("./fonts/invaders.fnt");
		



		do 
		{
			
			UG::ClearScreen();			
			UG::SetFont(nullptr);

		} while (UG::Process());

		UG::Dispose();


	}
	return 0;
}

