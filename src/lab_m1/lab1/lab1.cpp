#include "lab_m1/lab1/lab1.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Lab1::Lab1()
{  
    myTeapot = nullptr;
    myIterativeMesh = nullptr;
    myMeshIteration = 0;
    myCircus = false;
    myCircusIterator = 0;
}


Lab1::~Lab1()
{
}


void Lab1::Init()
{
    myBackgroundColor = glm::vec3(0, 0, 0);

    myCameraPos = glm::vec3(3, 2, 2);
    myCameraRot = glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0));
	auto camera = GetSceneCamera();
	camera->SetPositionAndRotation(myCameraPos, myCameraRot);

    // Load a mesh from file into GPU memory. We only need to do it once,
    // no matter how many times we want to draw this mesh

    if (!myTeapot) {
        myTeapot = new Mesh("teapot");
        myTeapot->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "teapot.obj");
        meshes[myTeapot->GetMeshID()] = myTeapot;
        myTeapotPos = glm::vec3(3, 0.5f, 0);
    }
    if (!myBunny) {
        myBunny = new Mesh("bunny");
        myBunny->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "animals"), "bunny.obj");
        meshes[myBunny->GetMeshID()] = myBunny;
    }
    if (!myIterativeMesh) {
        myIterativeMesh = new Mesh("myIterativeMesh");
    }
}


void Lab1::FrameStart()
{
}


void Lab1::Update(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->props.resolution;

    // Sets the clear color for the color buffer

	if (myCircus) {
		switch (myCircusIterator % 3) {
		case 0:
			++myCircusIterator;
			myBackgroundColor = glm::vec3(1, 0, 0);
			break;
		case 1:
			++myCircusIterator;
			myBackgroundColor = glm::vec3(0, 1, 0);
			break;
		case 2:
			myCircusIterator = 0;
			myBackgroundColor = glm::vec3(0, 0, 1);
			break;
		}
	}

    // TODO(student): Generalize the arguments of `glClearColor`.
    // You can, for example, declare three variables in the class header,
    // that will store the color components (red, green, blue).
    glClearColor(myBackgroundColor.x, myBackgroundColor.y, myBackgroundColor.z, 1);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);

    // Render the object

    RenderMesh(meshes["teapot"], myTeapotPos, glm::vec3(2.f));

    RenderMesh(meshes["bunny"] ,glm::vec3(-2.f, 1.50f, 0), glm::vec3(0.1f));

    // Render the object again but with different properties
    RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

    // TODO(student): We need to render (a.k.a. draw) the mesh that
    // was previously loaded. We do this using `RenderMesh`. Check the
    // signature of this function to see the meaning of its parameters.
    // You can draw the same mesh any number of times.

    if (myIterativeMesh) {
        RenderMesh(meshes["myIterativeMesh"], glm::vec3(0, 0.5f, 0), glm::vec3(0.5f));
    }

}


void Lab1::FrameEnd()
{
    DrawCoordinateSystem();
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab1::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
        // Treat continuous update based on input
        if (window->KeyHold(GLFW_KEY_A)) {
            myTeapotPos.x -= 5 * deltaTime;

            myCameraPos.x -= 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            myTeapotPos.x += 5 * deltaTime;

            myCameraPos.x += 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
        if (window->KeyHold(GLFW_KEY_W)) {
            myTeapotPos.z -= 5 * deltaTime;

            myCameraPos.z -= 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            myTeapotPos.z += 5 * deltaTime;

            myCameraPos.z += 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
        if (window->KeyHold(GLFW_KEY_E)) {
            myTeapotPos.y -= 5 * deltaTime;

            myCameraPos.y -= 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
        if (window->KeyHold(GLFW_KEY_Q)) {
            myTeapotPos.y += 5 * deltaTime;

            myCameraPos.y += 5 * deltaTime;
            auto camera = GetSceneCamera();
            camera->SetPositionAndRotation(myCameraPos, glm::quat(glm::vec3(-30 * TO_RADIANS, 0, 0)));
            camera->Update();
        }
    }

    // TODO(student): Add some key hold events that will let you move
    // a mesh instance on all three axes. You will also need to
    // generalize the position used by `RenderMesh`.

}


void Lab1::OnKeyPress(int key, int mods)
{
    if (key == GLFW_KEY_C) {
        myCircus = true;
    }
    if (key == GLFW_KEY_X) {
        myCircus = false;
		myCircusIterator = 0;
		myBackgroundColor = glm::vec3(0, 0, 0);
    }
    //// Add key press event
    if (key == GLFW_KEY_R) {
        myBackgroundColor = glm::vec3(1, 0, 0);
    }
    if (key == GLFW_KEY_G) {
        myBackgroundColor = glm::vec3(0, 1, 0);
    }
	if (key == GLFW_KEY_B) {
        myBackgroundColor = glm::vec3(0, 0, 1);
	}
    if (key == GLFW_KEY_ENTER) {
        myBackgroundColor = glm::vec3(0, 0, 0);
    }
    if (key == GLFW_KEY_SPACE) {
        switch (myMeshIteration % 3)
        {
        case 0:
            ++myMeshIteration;
			myIterativeMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
			meshes[myIterativeMesh->GetMeshID()] = myIterativeMesh;
            break;
        case 1:
            ++myMeshIteration;
			myIterativeMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
			meshes[myIterativeMesh->GetMeshID()] = myIterativeMesh;
			break;
        case 2:
            myMeshIteration = 0;
			myIterativeMesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "quad.obj");
			meshes[myIterativeMesh->GetMeshID()] = myIterativeMesh;
			break;
        }
    }

    // TODO(student): Add a key press event that will let you cycle
    // through at least two meshes, rendered at the same position.
    // You will also need to generalize the mesh name used by `RenderMesh`.

}


void Lab1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Lab1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Lab1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Lab1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    // Treat mouse scroll event
}


void Lab1::OnWindowResize(int width, int height)
{
    // Treat window resize event
}
