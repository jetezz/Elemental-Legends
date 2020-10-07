#pragma once

#include <irrlicht/irrlicht.h>

class MyEventReceiver: public irr::IEventReceiver
{

	

public:


	struct SMouseState
	{
		int PosX;
		int PosY;
		int Dx {0}; //Diferencia de x en el ultimo update de raton
		int Dy {0}; //Diferencia de y en el ultimo update de raton
		float valorRuleta {0};	//Direccion de la ruleta va de -1 a 1 float
		bool wheelMoved = false;    //Indica si se ha movido la ruleta

		bool LeftButtonDown;
		SMouseState() : LeftButtonDown(false) { }
		bool SMouseLeftClicked();
	} MouseState;



	virtual bool OnEvent(const irr::SEvent& event);
	
		
	const SMouseState & GetMouseState(void) const
	{
		return MouseState;
	}
	
	bool SMouseLeftClicked()
	{
		
		if(MouseState.LeftButtonDown)
			return true;
	
		return false;
	}
	
	virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const
	{
		return KeyIsDown[keyCode];
	}
	
	MyEventReceiver()
	{
		for (irr::u32 i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

	void reset(int oldX, int oldY, int posX, int posY);


private:

	bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];


};