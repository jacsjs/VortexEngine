#include "input/inputCommands/cameraCommands/cameraUpCommand.hpp"

vortexInput::CameraUpCommand::CameraUpCommand()
{
    
}

vortexInput::CameraUpCommand::~CameraUpCommand()
{
}

void vortexInput::CameraUpCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_UP);
}

void vortexInput::CameraUpCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_UP);
}

void vortexInput::CameraUpCommand::repeate()
{
}
