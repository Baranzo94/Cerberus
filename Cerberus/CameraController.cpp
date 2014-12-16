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
	m_Speed = -0.2;
	m_Type = "CameraController";
	m_Name = m_Type;
	DeltaTime = NULL;
}

CameraController::~CameraController()
{

}

void CameraController::update()
{

	//DeltaTime = timer->getDeltaTime();
	/*if (m_AttachedCamera)
	{
		//lets just use standard FPS Controllers(mouse & keyboard)
		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		vec3 forward = currentLook - currentPos;
		//vec3 forward = currentLook - m_AttachedCamera->m_Position;
		forward.y = 0.0f;
		forward=glm::normalize(forward);
		forward *= m_Speed;

		//Grab input
		if (InputSystem.getKeyboard().isKeyDown(SDLK_w))
		{
			m_AttachedCamera->m_Position.z += forward.z*m_Speed*Time.getDeltaTime();
			printf("Key press W detected\n");
		}
		else if (InputSystem.getKeyboard().isKeyDown(SDLK_s))
		{
			m_AttachedCamera->m_Position.z -= forward.z*m_Speed*Time.getDeltaTime();
		}

		//adjust values
		m_AttachedCamera->getParent()->getTransform()->setPosition(m_AttachedCamera->m_Position.x, m_AttachedCamera->m_Position.y, m_AttachedCamera->m_Position.z);
	}*/
}

void CameraController::setCamera(Camera * cam)
{
	m_AttachedCamera = cam;
}

//void CameraController::setSpeed(float speed)
//{
//	m_Speed = speed;
//}

void CameraController::moveForward()
{
	if (m_AttachedCamera)
	{

		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		vec3 forward = currentLook - currentPos;
		forward.y = 0.0f;
		forward = glm::normalize(forward);
		//forward *= m_Speed;

		//currentPos.z = currentPos.z - 2 +(m_Speed*forward.z*Time.getDeltaTime());
		currentPos.z = currentPos.z + m_Speed;
		printf("Key press W detected\n");

		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
	}
}

void CameraController::moveBackward()
{
	if (m_AttachedCamera)
	{

		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		vec3 forward = currentLook - currentPos;
		forward.y = 0.0f;
		forward = glm::normalize(forward);
		//forward *= m_Speed;

		currentPos.z -= m_Speed;
		printf("Key press S detected\n");
		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
	}
}