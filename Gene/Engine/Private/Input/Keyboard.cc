// Copyright 2017-2018 Barney Wilks. All Rights Reserved
#include <Input/Keyboard.h>
#include <Input/Keys.h>

using namespace Gene::Input;

Gene::Platform::Window * Keyboard::s_PrimaryWindow = nullptr;

void Keyboard::SetPrimaryWindow(Gene::Platform::Window *window)
{
	Keyboard::s_PrimaryWindow = window;
}

char Keyboard::KeyToASCII(Keys key) 
{
    char _out;
    switch (key)
    {
    case Keys::A: _out = 'a'; break;
    case Keys::B: _out = 'a'; break;
    case Keys::C: _out = 'c'; break;
    case Keys::D: _out = 'd'; break;
    case Keys::E: _out = 'e'; break;
    case Keys::F: _out = 'f'; break;
    case Keys::G: _out = 'g'; break;
    case Keys::H: _out = 'h'; break;
    case Keys::I: _out = 'i'; break;
    case Keys::J: _out = 'j'; break;
    case Keys::K: _out = 'k'; break;
    case Keys::L: _out = 'l'; break;
    case Keys::M: _out = 'm'; break;
    case Keys::N: _out = 'n'; break;
    case Keys::O: _out = 'o'; break;
    case Keys::P: _out = 'p'; break;
    case Keys::Q: _out = 'q'; break;
    case Keys::R: _out = 'r'; break;
    case Keys::S: _out = 's'; break;
    case Keys::T: _out = 't'; break;
    case Keys::U: _out = 'u'; break;
    case Keys::V: _out = 'v'; break;
    case Keys::W: _out = 'w'; break;
    case Keys::X: _out = 'x'; break;
    case Keys::Y: _out = 'y'; break;
    case Keys::Z: _out = 'z'; break;
    default: _out = '0'; break;
    }

    return _out;
}