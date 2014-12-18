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
	m_LookSpeed = 0.001;
	//m_LookSpeed = 10.0f;
	m_Type = "CameraController";
	m_Name = m_Type;
	DeltaTime = NULL;
	m_MouseMouvement = false;
}

CameraController::~CameraController()
{

}

void CameraController::update()
{
	DeltaTime = Timer::getTimer().getDeltaTime();
	//Input::getInput().getMouse()->setMousePositionDefaults();
	if (m_AttachedCamera)
	{
		//lets just use standard FPS Controllers(mouse & keyboard)
		vec3 currentPos = m_AttachedCamera->getParent()->getTransform()->getPosition();
		vec3 currentRot = m_AttachedCamera->getParent()->getTransform()->getRotation();
		vec3 currentLook = m_AttachedCamera->getLookAt();
		//get a forward vector
		vec3 forward = currentLook - currentPos;
		forward.y = 0.0f;
		forward = glm::normalize(forward);

		//calculate a right vector
		vec3 right = glm::cross(m_AttachedCamera->getUp(), forward);
		right = glm::normalize(right);

		//Grab input
		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_w))
		{
			currentPos.z += forward.z*m_ForwardSpeed*(DeltaTime);
			currentLook.z += forward.z*m_ForwardSpeed*(DeltaTime);
			m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_s))
		{
			currentPos.z -= forward.z*m_ForwardSpeed*(DeltaTime);
			currentLook.z -= forward.z*m_ForwardSpeed*(DeltaTime);
			m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_a))
		{
			currentPos += right*m_StrafeSpeed*(DeltaTime);
			currentLook += right*m_StrafeSpeed*(DeltaTime);
			m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		}
		else if (Input::getInput().getKeyboard()->isKeyDown(SDLK_d))
		{
			currentPos += right*(m_StrafeSpeed*-1)*(DeltaTime);
			currentLook += right*(m_StrafeSpeed*-1)*(DeltaTime);
			m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
		}

		if (Input::getInput().getKeyboard()->isKeyDown(SDLK_q))
		{
			m_AttachedCamera->setLook(0.0f, 0.0f, 0.0f);
		}

		//get the mouse values and directly move the yaw & pitch of the camera(the x and y of the camera rotation)

		//use these to caculate the look at
		if (m_MouseMouvement == true)
		{
			int mouseX = Input::getInput().getMouse()->getRelativeMouseX();
			int mouseY = Input::getInput().getMouse()->getRelativeMouseY();

			std::cout << "Mouse Move " << mouseX << " " << mouseY << "Delta Time "<<DeltaTime<<std::endl;

			currentRot.y += mouseX*(DeltaTime*m_LookSpeed);
			currentRot.x += mouseY*(DeltaTime*m_LookSpeed);

			//currentRot.y += mouseX*m_LookSpeed;
			//currentRot.x += mouseY*m_LookSpeed;


			//adjust values
			if (mouseX == 0 && mouseY == 0)
			{
				m_AttachedCamera->setLook(currentLook.x, currentLook.y, currentLook.z);
				m_MouseMouvement = false;
			}
			else{
				m_AttachedCamera->getParent()->getTransform()->setRotation(currentRot.x, currentRot.y, currentRot.z);
				//	m_AttachedCamera->getParent()->getTransform()->setPosition(currentPos.x, currentPos.y, currentPos.z);
				//m_AttachedCamera->setLook(currentLook.x + (cos(currentRot.x)*cos(currentRot.y)), currentLook.y*(sin(currentRot.y)), currentLook.z + (sin(currentRot.x)*cos(currentRot.y)));
				//m_AttachedCamera->setLook(currentLook.x + (cos(currentRot.y)*cos(currentRot.x)), currentLook.y*(sin(currentRot.x)), currentLook.z + (sin(currentRot.y)*cos(currentRot.x)));
				m_AttachedCamera->setLook(currentLook.x + (cos(currentRot.x)*cos(currentRot.y)), currentLook.y + (sin(currentRot.y)), currentLook.z);
				m_MouseMouvement = false;
				Input::getInput().getMouse()->setMousePositionDefaults();
			}
		}
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
}

void CameraController::setCamera(Camera * cam)
{
	m_AttachedCamera = cam;
}

void CameraController::mouseMoved()
{
	m_MouseMouvement = true;
}

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