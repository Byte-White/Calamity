#include"Calamity/Calamity.h"
#include <iostream>

namespace clm
{
    int CalamityInit()
    {
        // Initialize GLFW
        if (!glfwInit()) {
            return CALAMITY_FAILED;
        }
        // version
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Request OpenGL 4.x
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5); // Request OpenGL x.5
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Request a core profile
        
        return CALAMITY_OK;
    }
    void CalamityDestroy()
    {
        glfwTerminate();
    }


    //---------- Input ----------
	Window* Input::m_window = nullptr;

	bool Input::IsKeyPressed(const KeyCode key)
	{
		auto state = glfwGetKey(Input::GetWindow()->GetGLFWWindow(), static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(const MouseCode button)
	{
		auto state = glfwGetMouseButton(Input::GetWindow()->GetGLFWWindow(), static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	glm::vec2 Input::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(Input::GetWindow()->GetGLFWWindow(), &xpos, &ypos);

		return glm::vec2{ (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}

} // namespace clm
