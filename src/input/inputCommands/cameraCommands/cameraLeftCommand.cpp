#include "input/inputCommands/cameraCommands/cameraLeftCommand.hpp"

vortexInput::CameraLeftCommand::CameraLeftCommand()
{
    
}

vortexInput::CameraLeftCommand::~CameraLeftCommand()
{
}

void vortexInput::CameraLeftCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_LEFT);
}

void vortexInput::CameraLeftCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_LEFT);
}

void vortexInput::CameraLeftCommand::repeate()
{
}
