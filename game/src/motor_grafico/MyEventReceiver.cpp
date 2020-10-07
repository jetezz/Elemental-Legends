#include"motor_grafico/MyEventReceiver.hpp"


bool MyEventReceiver::OnEvent(const irr::SEvent& event)
{

	if (event.EventType == irr::EET_KEY_INPUT_EVENT)
		KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;

	if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		switch(event.MouseInput.Event)
		{
		case irr::EMIE_LMOUSE_PRESSED_DOWN:
			MouseState.LeftButtonDown = true;
			break;

		case irr::EMIE_LMOUSE_LEFT_UP:
			MouseState.LeftButtonDown = false;
			break;

		case irr::EMIE_MOUSE_WHEEL:
			MouseState.wheelMoved = true;
			MouseState.valorRuleta = event.MouseInput.Wheel;
			break;
		default:
			break;
		}
	}

	
		

	return false;
}


void MyEventReceiver::reset(int oldX, int oldY, int posX, int posY){
	MouseState.Dx = posX - oldX;
	MouseState.Dy = oldY - posY;

}