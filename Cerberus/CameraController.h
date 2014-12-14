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
	float m_Speed;
	Camera * m_AttachedCamera;

};


#endif
