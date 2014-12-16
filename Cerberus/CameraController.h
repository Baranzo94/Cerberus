#ifndef CameraController_h
#define CameraController_h

#include "Component.h"

class Camera;

class CameraController :public Component
{
public:
	CameraController();
	~CameraController();

	void update();

	void setCamera(Camera * cam);
	void setSpeed(float speed);
private:
	//float m_Speed;
	float m_ForwardSpeed;
	float m_StrafeSpeed;
	float m_LookSpeed;
	Camera * m_AttachedCamera;

};


#endif
