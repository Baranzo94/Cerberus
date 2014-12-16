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
	//m_Speed = 2;
	m_ForwardSpeed = 2;
	m_StrafeSpeed = 1;
	m_LookSpeed = 3;
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
		vec3 currentRot = m_AttachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		vec3 forward = currentLook - currentPos;
		forward.y = 0.0f;
		forward = glm::normalize(forward);
		

		//Calculate a right vector
		vec3 right = glm::cross(m_AttachedCamera->getUp(), forward);
		right = glm::normalize(right);

		//Grab input
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
		{
			//std::cout << "Time " << Timer::getTimer().getDeltaTime() << std::endl;
			currentPos.z += forward.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
			currentLook.z += forward.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
		{
			currentPos.z -= forward.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
			//currentLook.z = forward.z*m_Speed*Timer::getTimer().getDeltaTime();
			currentLook.z -= forward.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
			 {
			currentPos += right*m_StrafeSpeed*Timer::getTimer().getDeltaTime();
			currentLook += right*m_StrafeSpeed*Timer::getTimer().getDeltaTime();
			}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
			 {
			currentPos += right*(m_StrafeSpeed*-1)*Timer::getTimer().getDeltaTime();
			currentLook += right*(m_StrafeSpeed*-1)*Timer::getTimer().getDeltaTime();
			}
		
			 //get the mouse values and directly move the yaw & pitch of the camera(the x and y of the camera rotation)
			
			 //use these to caculate the look at

		int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
		int mouseY = Input::getInput().getMouse()->getRelativeMouseY();
		
		currentRot.y += mouseX*Timer::getTimer().getDeltaTime()*m_LookSpeed;
		currentRot.x += mouseY*Timer::getTimer().getDeltaTime()*m_LookSpeed;

		//adjust values
		m_AttachedCamera->getParent()->getTransform()->setRotation(currentRot.x, currentRot.y, currentRot.z);
		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		//m_AttachedCamera->setLook(currentLook.x, currentLook.y, currentLook.z);
		m_AttachedCamera->setLook(currentLook.x + (cos(currentRot.x)*cos(currentRot.y)),
			currentLook.y,
			currentLook.z + (sin(currentRot.x)*cos(currentRot.y)));
	}
}

void CameraController::setCamera(Camera * cam)
{
	m_AttachedCamera = cam;
}
