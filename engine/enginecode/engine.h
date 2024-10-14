/** \file engine.h
* A header file which includes relevant headers for development
*/

#pragma once

#include "core/application.h"

#include "cameras/camera.h"
#include "cameras/FixedOrthoController.h"
#include "cameras/FreeEulerController.h"
#include "cameras/FollowController.h"
#include "platform/OpenGL//vertexArray.h"
#include "platform/OpenGL/OpenGLShader.h"
#include "platform/OpenGL/OpenGLTexture.h"
#include "rendering/Renderer3D.h"
#include "platform/OpenGL/OpenGLUniformBuffer.h"

#include "core/assimpLoader/loadModelFile.h"

#include "components/transform.h"
#include "components/render.h"

#include "components/nativeScripting.h"