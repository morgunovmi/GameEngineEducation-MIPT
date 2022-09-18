#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

namespace Keyboard {
    enum Key
    {
        Unknown = -1,
        A = 0,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        Num0,
        Num1,
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Escape,
        LControl,
        LShift,
        LAlt,
        LSystem,
        RControl,
        RShift,
        RAlt,
        RSystem,
        Menu,
        LBracket,
        RBracket,
        Semicolon,
        Comma,
        Period,
        Quote,
        Slash,
        Backslash,
        Tilde,
        Equal,
        Hyphen,
        Space,
        Enter,
        Backspace,
        Tab,
        PageUp,
        PageDown,
        End,
        Home,
        Insert,
        Delete,
        Add,
        Subtract,
        Multiply,
        Divide,
        Left,
        Right,
        Up,
        Down,
        Numpad0,
        Numpad1,
        Numpad2,
        Numpad3,
        Numpad4,
        Numpad5,
        Numpad6,
        Numpad7,
        Numpad8,
        Numpad9,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
        F13,
        F14,
        F15,
        Pause
    };

    inline bool IsKeyPressed(Key key)
    {
        int vkey = 0;

        switch (key)
        {
        default:         vkey = 0;             break;
        case A:          vkey = 'A';           break;
        case B:          vkey = 'B';           break;
        case C:          vkey = 'C';           break;
        case D:          vkey = 'D';           break;
        case E:          vkey = 'E';           break;
        case F:          vkey = 'F';           break;
        case G:          vkey = 'G';           break;
        case H:          vkey = 'H';           break;
        case I:          vkey = 'I';           break;
        case J:          vkey = 'J';           break;
        case K:          vkey = 'K';           break;
        case L:          vkey = 'L';           break;
        case M:          vkey = 'M';           break;
        case N:          vkey = 'N';           break;
        case O:          vkey = 'O';           break;
        case P:          vkey = 'P';           break;
        case Q:          vkey = 'Q';           break;
        case R:          vkey = 'R';           break;
        case S:          vkey = 'S';           break;
        case T:          vkey = 'T';           break;
        case U:          vkey = 'U';           break;
        case V:          vkey = 'V';           break;
        case W:          vkey = 'W';           break;
        case X:          vkey = 'X';           break;
        case Y:          vkey = 'Y';           break;
        case Z:          vkey = 'Z';           break;
        case Num0:       vkey = '0';           break;
        case Num1:       vkey = '1';           break;
        case Num2:       vkey = '2';           break;
        case Num3:       vkey = '3';           break;
        case Num4:       vkey = '4';           break;
        case Num5:       vkey = '5';           break;
        case Num6:       vkey = '6';           break;
        case Num7:       vkey = '7';           break;
        case Num8:       vkey = '8';           break;
        case Num9:       vkey = '9';           break;
        case Escape:     vkey = VK_ESCAPE;     break;
        case LControl:   vkey = VK_LCONTROL;   break;
        case LShift:     vkey = VK_LSHIFT;     break;
        case LAlt:       vkey = VK_LMENU;      break;
        case LSystem:    vkey = VK_LWIN;       break;
        case RControl:   vkey = VK_RCONTROL;   break;
        case RShift:     vkey = VK_RSHIFT;     break;
        case RAlt:       vkey = VK_RMENU;      break;
        case RSystem:    vkey = VK_RWIN;       break;
        case Menu:       vkey = VK_APPS;       break;
        case LBracket:   vkey = VK_OEM_4;      break;
        case RBracket:   vkey = VK_OEM_6;      break;
        case Semicolon:  vkey = VK_OEM_1;      break;
        case Comma:      vkey = VK_OEM_COMMA;  break;
        case Period:     vkey = VK_OEM_PERIOD; break;
        case Quote:      vkey = VK_OEM_7;      break;
        case Slash:      vkey = VK_OEM_2;      break;
        case Backslash:  vkey = VK_OEM_5;      break;
        case Tilde:      vkey = VK_OEM_3;      break;
        case Equal:      vkey = VK_OEM_PLUS;   break;
        case Hyphen:     vkey = VK_OEM_MINUS;  break;
        case Space:      vkey = VK_SPACE;      break;
        case Enter:      vkey = VK_RETURN;     break;
        case Backspace:  vkey = VK_BACK;       break;
        case Tab:        vkey = VK_TAB;        break;
        case PageUp:     vkey = VK_PRIOR;      break;
        case PageDown:   vkey = VK_NEXT;       break;
        case End:        vkey = VK_END;        break;
        case Home:       vkey = VK_HOME;       break;
        case Insert:     vkey = VK_INSERT;     break;
        case Delete:     vkey = VK_DELETE;     break;
        case Add:        vkey = VK_ADD;        break;
        case Subtract:   vkey = VK_SUBTRACT;   break;
        case Multiply:   vkey = VK_MULTIPLY;   break;
        case Divide:     vkey = VK_DIVIDE;     break;
        case Left:       vkey = VK_LEFT;       break;
        case Right:      vkey = VK_RIGHT;      break;
        case Up:         vkey = VK_UP;         break;
        case Down:       vkey = VK_DOWN;       break;
        case Numpad0:    vkey = VK_NUMPAD0;    break;
        case Numpad1:    vkey = VK_NUMPAD1;    break;
        case Numpad2:    vkey = VK_NUMPAD2;    break;
        case Numpad3:    vkey = VK_NUMPAD3;    break;
        case Numpad4:    vkey = VK_NUMPAD4;    break;
        case Numpad5:    vkey = VK_NUMPAD5;    break;
        case Numpad6:    vkey = VK_NUMPAD6;    break;
        case Numpad7:    vkey = VK_NUMPAD7;    break;
        case Numpad8:    vkey = VK_NUMPAD8;    break;
        case Numpad9:    vkey = VK_NUMPAD9;    break;
        case F1:         vkey = VK_F1;         break;
        case F2:         vkey = VK_F2;         break;
        case F3:         vkey = VK_F3;         break;
        case F4:         vkey = VK_F4;         break;
        case F5:         vkey = VK_F5;         break;
        case F6:         vkey = VK_F6;         break;
        case F7:         vkey = VK_F7;         break;
        case F8:         vkey = VK_F8;         break;
        case F9:         vkey = VK_F9;         break;
        case F10:        vkey = VK_F10;        break;
        case F11:        vkey = VK_F11;        break;
        case F12:        vkey = VK_F12;        break;
        case F13:        vkey = VK_F13;        break;
        case F14:        vkey = VK_F14;        break;
        case F15:        vkey = VK_F15;        break;
        case Pause:      vkey = VK_PAUSE;      break;
        }

        return (GetAsyncKeyState(vkey) & 0x8000) != 0;
    }
}