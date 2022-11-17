#include "input/inputCommands/cameraCommands/cameraOutCommand.hpp"

vortexInput::CameraOutCommand::CameraOutCommand()
{
    
}

vortexInput::CameraOutCommand::~CameraOutCommand()
{
}

void vortexInput::CameraOutCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_OUT);
}

void vortexInput::CameraOutCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_OUT);
}

void vortexInput::CameraOutCommand::repeate()
{
}
