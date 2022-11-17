#include "input/inputCommands/cameraCommands/cameraDownCommand.hpp"

vortexInput::CameraDownCommand::CameraDownCommand()
{
    
}

vortexInput::CameraDownCommand::~CameraDownCommand()
{
}

void vortexInput::CameraDownCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_DOWN);
}

void vortexInput::CameraDownCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_DOWN);
}

void vortexInput::CameraDownCommand::repeate()
{
}
