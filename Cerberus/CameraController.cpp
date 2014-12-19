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
	m_ForwardSpeed = 2;
	m_StrafeSpeed = 1;
	m_LookSpeed = 0.1f;
	m_Type = "CameraController";
	m_Name = m_Type;
}

CameraController::~CameraController()
{

}

void CameraController::update()
{
	DeltaTime = Timer::getTimer().getDeltaTime();
	if (m_AttachedCamera)
	{
		//lets just use standard FPS Controllers(mouse & keyboard)
		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentRot = m_AttachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = m_AttachedCamera->getLookAt();

		//get the mouse values and directly move the yaw & pitch of the camera(the x and y of the camera rotation)

		//use these to caculate the look at
		int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
		int mouseY = Input::getInput().getMouse()->getRelativeMouseY();

		currentRot.x += mouseX*Timer::getTimer().getDeltaTime()*m_LookSpeed;
		currentRot.y += mouseY*Timer::getTimer().getDeltaTime()*m_LookSpeed;

		vec3 direction(cos(currentRot.y) * sin(currentRot.x),
			sin(currentRot.y),
			cos(currentRot.y) * cos(currentRot.x));

		vec3 right = vec3(sin(currentRot.x - 3.14f / 2.0f), 0, cos(currentRot.y - 3.14 / 2.0f));

		glm::vec3 up = glm::cross(direction, right);

		std::cout << "Mouse " << mouseX << " " << mouseY << std::endl;
		std::cout << "Direction " << direction.x << " " << direction.y << " " << direction.z << std::endl;

		//Grab input
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
		{
			currentPos.z += direction.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
			//currentLook.z+=direction.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
		{
			currentPos.z -= direction.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
			//currentLook.z-=direction.z*m_ForwardSpeed*Timer::getTimer().getDeltaTime();
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
		{
			currentPos += right*m_StrafeSpeed*Timer::getTimer().getDeltaTime();
			//currentLook+=right*m_StrafeSpeed*Timer::getTimer().getDeltaTime();
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
		{
			currentPos -= right*m_StrafeSpeed*Timer::getTimer().getDeltaTime();
			//currentLook+=right*(m_StrafeSpeed*-1)*Timer::getTimer().getDeltaTime();
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_q))
		{
			currentLook = vec3(0.0f, 0.0f, 0.0f);
		}

		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		m_AttachedCamera->getParent()->getTransform()->setRotation(currentRot.x, currentRot.y, currentRot.z);
		m_AttachedCamera->setUp(up.x, up.y, up.z);
		m_AttachedCamera->setLook(currentPos.x + direction.x, currentPos.y + direction.y, currentPos.z + direction.z);

	}
}

void CameraController::setCamera(Camera * cam)
{
	m_AttachedCamera = cam;
}



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


//void CameraController::setCamera(Camera * cam)
//{
	//m_AttachedCamera = cam;
//}

//void CameraController::mouseMoved()
//{
//	m_MouseMouvement = true;
//}

//void CameraController::setSpeed(float speed)
//{
//	m_Speed = speed;
//}

/*
void CameraController::moveForward()
{
	if (m_AttachedCamera)
	{

		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		// Same as moveForward the code works without the below code 
		//vec3 currentLook = m_AttachedCamera->getLookAt();
		//vec3 forward = currentLook - currentPos;
		//forward.y = 0.0f;
		//forward = glm::normalize(forward);
				//forward *= m_Speed; Not needed

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
		//vec3 currentLook = m_AttachedCamera->getLookAt();
		//vec3 forward = currentLook - currentPos;
		//forward.y = 0.0f;
		//forward = glm::normalize(forward);
				//forward *= m_Speed; Not needed

		currentPos.z -= m_Speed;
		printf("Key press S detected\n");
		m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
	}
}

void CameraController::camRot()
{
	if (m_AttachedCamera)
	{

		//int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
		//int mouseY = Input::getInput().getMouse()->getRelativeMouseY();
		//currentRot.y += mouseX*DeltaTime*m_Speed;
		//currentRot.x += mouseY*DeltaTime*m_Speed;

		//InputSystem.getMouse().setMousePosition(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);

		vec3 currentRot = m_AttachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		//printf("Mouse is moving\n");
		m_AttachedCamera->getParent()->getTransform()->setRotation(currentRot.x, currentRot.y, currentRot.z);
		
		//This code here controls the rotation but mucks up the forward and backward movement and causes everything to rotate
		//Note i believe this is because of the mixed up inputs in main.cpp Mouse Motion case
		//m_AttachedCamera->setLook(currentLook.x + (cos(currentRot.x)*cos(currentRot.y)), currentLook.y, currentLook.z + (sin(currentRot.x)*cos(currentRot.y)));
	
	}

}
*/