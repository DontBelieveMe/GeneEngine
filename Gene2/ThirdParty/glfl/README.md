# What is GLFL

GLFL is an OpenGL function loader, much like GLEW.

When working with more or less modern OpenGL (at least 3.0+) on some platforms (at least on Windows), you have to use a 3rd party library to get pointers to all needed functions from the API. That's what the library does.

It fully supports OpenGL up to 4.5, OpenGL ES up to 3.2 and OpenGL SC up to 2.0, as well as all official extensions.

# GLFL vs GLEW

GLFL supports logging all OpenGL calls, including their arguments and return values. Optionally it can do `glGetError()` after every call.

You can also load different pointers for different contexts.

GLFL seems to compile faster (on my MinGW-w64(GCC 6.2.0) it's faster by 33%, which is 0.1s, with `-Wall -Wextra -O3`).

No GLX and EGL support.

You have to manually specify `void *get_gl_proc_address(const char *func_name)`, which should be provided by your window-creating library.

### Other cons:

There is no way to not load functions which were removed from the core profile.



# How GLFL is generated

GLFL is generated using a short shell script, which parses [OpenGL XML Registry](https://raw.githubusercontent.com/KhronosGroup/OpenGL-Registry/master/xml/gl.xml).
