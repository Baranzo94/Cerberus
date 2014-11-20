//TO DO: Add includes for GameObject.h and Transform.h, as well as include their functionality
#include "Camera.h"


Camera::Camera()
{
	m_Type = "Camera";
	m_LookAt = vec3(0.0f, 0.0f, 0.0f);
	m_Up = vec3(0.0f, 1.0f, 0.0f);
	m_NearClip = 0.1f;
	m_FarClip = 100.0f;
	m_FOV = 45.0f;
	m_AspectRatio = 16.0f / 9.0f;
	m_View = mat4();
	m_Projection = mat4();
}

Camera::~Camera()
{

}

void Camera::update()
{
	//Inteaction with GameObject and Transform, thus those header files and sourcce files
	//must first be created.
}

void Camera::SetLook(float x, float y, float z)
{
	m_LookAt = vec3(x, y, z);

}

void Camera::SetUp(float x, float y, float z)
{
	m_Up = vec3(x, y, z);
}

void Camera::setNearClip(float nearClip)
{
	m_NearClip = nearClip;
}

void Camera::setFarClip(float farClip)
{
	m_FarClip = farClip;
}

void Camera::setFOV(float FOV)
{
	m_FOV = FOV;
}

void Camera::setAspectRatio(float ratio)
{
	m_AspectRatio = ratio;
}

mat4& Camera::getView()
{
	return m_View;
}

mat4& Camera::getProjection()
{
	return m_Projection;
}