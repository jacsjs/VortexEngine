#include "input/inputCommands/cameraCommands/cameraInCommand.hpp"

vortexInput::CameraInCommand::CameraInCommand()
{
    
}

vortexInput::CameraInCommand::~CameraInCommand()
{
}

void vortexInput::CameraInCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_IN);
}

void vortexInput::CameraInCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_IN);
}

void vortexInput::CameraInCommand::repeate()
{
}
