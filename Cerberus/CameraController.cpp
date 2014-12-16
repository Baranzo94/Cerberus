#include <iostream>

#include "CameraController.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "Timer.h"
#include "Input.h"

#include <glm/glm.hpp>
using glm::vec3;

CameraController::CameraController()
{
	m_AttachedCamera = NULL;
	m_Speed = 2;
	m_Type = "CameraController";
	m_Name = m_Type;
}

CameraController::~CameraController()
{

}

void CameraController::update()
{
	if (m_AttachedCamera)
	{
		//lets just use standard FPS Controllers(mouse & keyboard)
		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		vec3 forward = currentLook - currentPos;
		forward.z = 0.5f;
		glm::normalize(forward);
		forward *= m_Speed;

		//Grab input
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
		{
			std::cout << "Time " << Timer::getTimer().getDeltaTime() << std::endl;
			currentPos.z += forward.z*m_Speed*Timer::getTimer().getDeltaTime();
			currentLook.z += forward.z*m_Speed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
		{
			currentPos.z -= forward.z*m_Speed*Timer::getTimer().getDeltaTime();
			currentLook.z = forward.z*m_Speed*Timer::getTimer().getDeltaTime();
		}

		//adjust values
		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		m_AttachedCamera->setLook(currentLook.x, currentLook.y, currentLook.z);
	}
}

void CameraController::setCamera(Camera * cam)
{
	m_AttachedCamera = cam;
}

void CameraController::setSpeed(float speed)
{
	m_Speed = speed;
}