#include "input/inputCommands/cameraCommands/cameraRightCommand.hpp"

vortexInput::CameraRightCommand::CameraRightCommand()
{
}

vortexInput::CameraRightCommand::~CameraRightCommand()
{
}

void vortexInput::CameraRightCommand::release()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_RIGHT);
}

void vortexInput::CameraRightCommand::press()
{
    renderManager->getCurrentScene()->activeCamera()->updateDirection(vortexGraphics::CAMERA_RIGHT);
}

void vortexInput::CameraRightCommand::repeate()
{
}

