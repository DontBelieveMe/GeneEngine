// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include <Platform/OS.h>
#include <Math/Vector2.h>
#include <Input/Mouse.h>
#include <Input/Keyboard.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysymdef.h>
#include <X11/keysym.h>
#include <X11/XKBlib.h>

#include <GL/glx.h>
#include <stdio.h>

#include "X11Window.h"
#include "../GLFLLoad.h"

using namespace Gene::Platform::X11;

static Window s_XRoot;
static Window s_XWindow;
static Atom   s_XEvtDestroyWIndowMessage;

X11Window::~X11Window()
{
}

void X11Window::Destroy()
{
    XCloseDisplay(static_cast<Display*>(m_Display));
}

void X11Window::SetPointerPosition(int32 x, int32 y)
{
    Display *dpy = static_cast<Display*>(m_Display);
    int32 tmpX, tmpY;
    ::Window child;

    XWindowAttributes attribs;
    XGetWindowAttributes(dpy, s_XWindow, &attribs);
    XTranslateCoordinates(
                dpy,
                s_XWindow,
                s_XRoot,
                0, 0,
                &tmpX, &tmpY,
                &child
    );

    /*
        Make the specified mouse coordinates be relative to window
        and not screen
    */
    x += tmpX - attribs.x;
    y += tmpY - attribs.y;

    XWarpPointer(
                dpy,
                None,
                s_XRoot,
                0, 0, 0, 0,
                x, y
    );
}

void X11Window::Create()
{
    Display *dpy = XOpenDisplay(NULL);
    s_XRoot = DefaultRootWindow(dpy);

    GLint att[] =
    {
        GLX_RGBA,
        GLX_DEPTH_SIZE,
        24,
        GLX_DOUBLEBUFFER,
        None
    };

    XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
    Colormap cmap = XCreateColormap(dpy, s_XRoot, vi->visual, AllocNone);

    XSetWindowAttributes swa;
    swa.colormap   = cmap;
    swa.event_mask = ExposureMask |
                     KeyPressMask |
                     KeyReleaseMask |
                     StructureNotifyMask;


    s_XWindow = XCreateWindow(dpy,
                              s_XRoot,
                              0,
                              0,
                              Width(),
                              Height(),
                              0,
                              vi->depth,
                              InputOutput,
                              vi->visual,
                              CWColormap | CWEventMask,
                              &swa
    );

    XStoreName(dpy, s_XWindow, m_WindowConfig.Title);    

    m_Display    = dpy;
    m_VisualInfo = vi;

    // Configure/register window destroy message
    s_XEvtDestroyWIndowMessage = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(dpy, s_XWindow, &s_XEvtDestroyWIndowMessage, 1);

    // Configure input handlers.
    Input::Mouse::SetPrimaryWindow(this);
    Input::Keyboard::SetPrimaryWindow(this);

    m_Window = &s_XWindow;
}

static void *GetProcAddress(const char *address)
{
    return (void*) glXGetProcAddress((GLubyte*)address);
}

void X11Window::CreateGLContext()
{
    Display *dpy = static_cast<Display*>(m_Display);

    GLXContext glc = glXCreateContext(dpy, (XVisualInfo*)m_VisualInfo, NULL, GL_TRUE);
    glXMakeCurrent(dpy, s_XWindow, glc);
    m_Context->Context = glc;

    GLFLUtil::GLFLInit(GetProcAddress);
   
    glGetIntegerv(GL_MAJOR_VERSION, &(m_Context->MajorVersion)); 
    glGetIntegerv(GL_MINOR_VERSION, &(m_Context->MinorVersion));
}

void X11Window::Show()
{
    XMapWindow((Display*)m_Display, s_XWindow);
}

void X11Window::PollEvents()
{
    Display *dpy = static_cast<Display*>(m_Display);

    int pending = XPending(dpy);
    while(pending--)
    {
        XEvent evt;
        XNextEvent(dpy, &evt);

        switch(evt.type)
        {
            case ClientMessage:
            {
                if(evt.xclient.data.l[0] == s_XEvtDestroyWIndowMessage)
                {
                    XDestroyWindow(dpy, evt.xclient.window);
                    m_Running = false;
                    return;
                }
                break;
            }
            case KeyPress:
            {
                //KeySym pressSym = XkbKeycodeToKeysym(dpy, evt.xkey.keycode, 0, 0);
                KeySym pressSym = XLookupKeysym(&evt.xkey, 0);

                m_KeyState.KeyMap[pressSym] = true;
                break;
            }
            case KeyRelease:
            {
                //KeySym releaseSym = XkbKeycodeToKeysym(dpy, evt.xkey.keycode, 0, 0);
                KeySym releaseSym = XLookupKeysym(&evt.xkey, 0);
                m_KeyState.KeyMap[releaseSym] = false;
                break;
            }
            case ConfigureNotify:
            {
                XConfigureEvent confEvent = evt.xconfigure;
                if(confEvent.width != Width() || confEvent.height != Height())
                {
                    if(m_Callbacks.Resize)
                    {
                        m_WindowConfig.Width = confEvent.width;
                        m_WindowConfig.Height = confEvent.height;
                        m_Callbacks.Resize(confEvent.width, confEvent.height);
                    }
                }
                break;
            }
        }
    }
    
    int x,y, c, d;
    unsigned e;
    ::Window a, b;

    XQueryPointer(dpy, s_XWindow, &a, &b, &c, &d, &x, &y, &e);
    m_MouseState.Position.X = x;
    m_MouseState.Position.Y = y;
 
    XFlush(dpy);
}

void X11Window::SwapBuffers()
{
    glXSwapBuffers((Display*)m_Display, s_XWindow);
}

X11Window::Vector2 X11Window::ScreenToWindow(const Vector2 &point)
{

}

X11Window::Vector2 X11Window::WindowToScreen(const Vector2 &point)
{

}
