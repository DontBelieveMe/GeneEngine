/* Freetype GL - A C OpenGL Freetype engine
 *
 * Distributed under the OSI-approved BSD 2-Clause License.  See accompanying
 * file `LICENSE` for more details.
 */
#ifndef __OPEN_GL_H__
#define __OPEN_GL_H__

// Modified to integrate with GeneEngine
#include <Platform/OS.h>

#if defined(__APPLE__)
#   include "TargetConditionals.h"
#   if TARGET_OS_SIMULATOR || TARGET_OS_IPHONE
#     if defined(FREETYPE_GL_ES_VERSION_3_0)
#       include <OpenGLES/ES3/gl.h>
#     else
#       include <OpenGLES/ES2/gl.h>
#     endif
#   else
#     include <OpenGL/gl.h>
#   endif
#elif defined(GENE_OS_WINDOWS) || defined(_WIN64)
#include <Platform/OpenGL.h>
#else
#  include <GL/glew.h>
#  include <GL/gl.h>
#endif

#endif /* OPEN_GL_H */
