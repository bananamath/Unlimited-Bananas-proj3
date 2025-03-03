#include "InputManager.h"
#include "DisplayManager.h"
#include "EventKeyboard.h"
#include "EventMouse.h"
#include "LogManager.h"

using namespace df;
using namespace Keyboard;
using namespace Mouse;

InputManager::InputManager()
{
    setType("InputManager");
}

InputManager& InputManager::getInstance()
{
    static InputManager single;
    return single;
}

int InputManager::startUp()
{
    if (DM.isStarted() == false)
    {
        return -1;
    }

    sf::RenderWindow *window = DM.getWindow();

    window -> setKeyRepeatEnabled(false);

    Manager::startUp();

    return 0;
}

void InputManager::shutDown()
{
    sf::RenderWindow *window = DM.getWindow();

    window -> setKeyRepeatEnabled(true);

    Manager::shutDown();
}

void InputManager::getInput(bool output) const
{
    while (const std::optional<sf::Event> p_event = DM.getWindow() -> pollEvent())
    {
        // Get event.
        sf::Event e = p_event.value();

        // Key was pressed?
        if (p_event -> getIf<sf::Event::KeyPressed>())
        {
            // Setup as KeyPressed event.
            sf::Event::KeyPressed *p_kb_event = reinterpret_cast<sf::Event::KeyPressed *> (&e);

            // Get SFML keyboard code.
            sf::Keyboard::Key key;
            key = p_kb_event -> code;

            EventKeyboard eventKeyboard;
            eventKeyboard.setKeyboardAction(KEY_PRESSED);

            switch (key) {
                case sf::Keyboard::Key::Space:
                    eventKeyboard.setKey(SPACE);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Space");
                    }
                    break;

                case sf::Keyboard::Key::Enter:
                    eventKeyboard.setKey(RETURN);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Return");
                    }
                    break;

                case sf::Keyboard::Key::Escape:
                    eventKeyboard.setKey(ESCAPE);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Escape");
                    }
                    break;

                case sf::Keyboard::Key::Tab:
                    eventKeyboard.setKey(TAB);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Tab");
                    }
                    break;

                case sf::Keyboard::Key::Left:
                    eventKeyboard.setKey(LEFTARROW);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key LeftArrow");
                    }
                    break;

                case sf::Keyboard::Key::Right:
                    eventKeyboard.setKey(RIGHTARROW);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key RightArrow");
                    }
                    break;

                case sf::Keyboard::Key::Up:
                    eventKeyboard.setKey(UPARROW);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key UpArrow");
                    }
                    break;

                case sf::Keyboard::Key::Down:
                    eventKeyboard.setKey(DOWNARROW);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key DownArrow");
                    }
                    break;

                case sf::Keyboard::Key::Pause:
                    eventKeyboard.setKey(PAUSE);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Pause");
                    }
                    break;

                case sf::Keyboard::Key::Subtract:
                    eventKeyboard.setKey(MINUS);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Minus");
                    }
                    break;

                case sf::Keyboard::Key::Add:
                    eventKeyboard.setKey(PLUS);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Plus");
                    }
                    break;

                case sf::Keyboard::Key::Grave:
                    eventKeyboard.setKey(TILDE);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Tilde");
                    }
                    break;

                case sf::Keyboard::Key::Period:
                    eventKeyboard.setKey(PERIOD);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Period");
                    }
                    break;

                case sf::Keyboard::Key::Comma:
                    eventKeyboard.setKey(COMMA);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Comma");
                    }
                    break;

                case sf::Keyboard::Key::Slash:
                    eventKeyboard.setKey(SLASH);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Slash");
                    }
                    break;

                case sf::Keyboard::Key::LControl:
                    eventKeyboard.setKey(LEFTCONTROL);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key LeftControl");
                    }
                    break;

                case sf::Keyboard::Key::RControl:
                    eventKeyboard.setKey(RIGHTCONTROL);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key RightControl");
                    }
                    break;

                case sf::Keyboard::Key::LShift:
                    eventKeyboard.setKey(LEFTSHIFT);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key LeftShift");
                    }
                    break;

                case sf::Keyboard::Key::RShift:
                    eventKeyboard.setKey(RIGHTSHIFT);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key RightShift");
                    }
                    break;

                case sf::Keyboard::Key::F1:
                    eventKeyboard.setKey(F1);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F1");
                    }
                    break;

                case sf::Keyboard::Key::F2:
                    eventKeyboard.setKey(F2);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F2");
                    }
                    break;

                case sf::Keyboard::Key::F3:
                    eventKeyboard.setKey(F3);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F3");
                    }
                    break;

                case sf::Keyboard::Key::F4:
                    eventKeyboard.setKey(F4);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F4");
                    }
                    break;

                case sf::Keyboard::Key::F5:
                    eventKeyboard.setKey(F5);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F5");
                    }
                    break;

                case sf::Keyboard::Key::F6:
                    eventKeyboard.setKey(F6);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F6");
                    }
                    break;

                case sf::Keyboard::Key::F7:
                    eventKeyboard.setKey(F7);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F7");
                    }
                    break;

                case sf::Keyboard::Key::F8:
                    eventKeyboard.setKey(F8);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F8");
                    }
                    break;

                case sf::Keyboard::Key::F9:
                    eventKeyboard.setKey(F9);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F9");
                    }
                    break;

                case sf::Keyboard::Key::F10:
                    eventKeyboard.setKey(F10);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F10");
                    }
                    break;

                case sf::Keyboard::Key::F11:
                    eventKeyboard.setKey(F11);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F11");
                    }
                    break;

                case sf::Keyboard::Key::F12:
                    eventKeyboard.setKey(F12);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F12");
                    }
                    break;

                case sf::Keyboard::Key::A:
                    eventKeyboard.setKey(A);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key A");
                    }
                    break;

                case sf::Keyboard::Key::B:
                    eventKeyboard.setKey(B);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key B");
                    }
                    break;

                case sf::Keyboard::Key::C:
                    eventKeyboard.setKey(C);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key C");
                    }
                    break;

                case sf::Keyboard::Key::D:
                    eventKeyboard.setKey(D);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key D");
                    }
                    break;

                case sf::Keyboard::Key::E:
                    eventKeyboard.setKey(E);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key E");
                    }
                    break;

                case sf::Keyboard::Key::F:
                    eventKeyboard.setKey(F);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key F");
                    }
                    break;

                case sf::Keyboard::Key::G:
                    eventKeyboard.setKey(G);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key G");
                    }
                    break;

                case sf::Keyboard::Key::H:
                    eventKeyboard.setKey(H);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key H");
                    }
                    break;

                case sf::Keyboard::Key::I:
                    eventKeyboard.setKey(I);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key I");
                    }
                    break;

                case sf::Keyboard::Key::J:
                    eventKeyboard.setKey(J);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key J");
                    }
                    break;

                case sf::Keyboard::Key::K:
                    eventKeyboard.setKey(K);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key K");
                    }
                    break;

                case sf::Keyboard::Key::L:
                    eventKeyboard.setKey(L);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key L");
                    }
                    break;

                case sf::Keyboard::Key::M:
                    eventKeyboard.setKey(M);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key M");
                    }
                    break;

                case sf::Keyboard::Key::N:
                    eventKeyboard.setKey(N);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key N");
                    }
                    break;

                case sf::Keyboard::Key::O:
                    eventKeyboard.setKey(O);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key O");
                    }
                    break;

                case sf::Keyboard::Key::P:
                    eventKeyboard.setKey(P);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key P");
                    }
                    break;

                case sf::Keyboard::Key::Q:
                    eventKeyboard.setKey(Q);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Q");
                    }
                    break;

                case sf::Keyboard::Key::R:
                    eventKeyboard.setKey(R);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key R");
                    }
                    break;

                case sf::Keyboard::Key::S:
                    eventKeyboard.setKey(S);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key S");
                    }
                    break;

                case sf::Keyboard::Key::T:
                    eventKeyboard.setKey(T);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key T");
                    }
                    break;

                case sf::Keyboard::Key::U:
                    eventKeyboard.setKey(U);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key U");
                    }
                    break;

                case sf::Keyboard::Key::V:
                    eventKeyboard.setKey(V);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key V");
                    }
                    break;

                case sf::Keyboard::Key::W:
                    eventKeyboard.setKey(W);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key W");
                    }
                    break;

                case sf::Keyboard::Key::X:
                    eventKeyboard.setKey(X);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key X");
                    }
                    break;

                case sf::Keyboard::Key::Y:
                    eventKeyboard.setKey(Y);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Y");
                    }
                    break;

                case sf::Keyboard::Key::Z:
                    eventKeyboard.setKey(Z);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key Z");
                    }
                    break;

                case sf::Keyboard::Key::Num1:
                    eventKeyboard.setKey(NUM1);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 1");
                    }
                    break;

                case sf::Keyboard::Key::Num2:
                    eventKeyboard.setKey(NUM2);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 2");
                    }
                    break;

                case sf::Keyboard::Key::Num3:
                    eventKeyboard.setKey(NUM3);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 3");
                    }
                    break;

                case sf::Keyboard::Key::Num4:
                    eventKeyboard.setKey(NUM4);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 4");
                    }
                    break;

                case sf::Keyboard::Key::Num5:
                    eventKeyboard.setKey(NUM5);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 5");
                    }
                    break;

                case sf::Keyboard::Key::Num6:
                    eventKeyboard.setKey(NUM6);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 6");
                    }
                    break;

                case sf::Keyboard::Key::Num7:
                    eventKeyboard.setKey(NUM7);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 7");
                    }
                    break;

                case sf::Keyboard::Key::Num8:
                    eventKeyboard.setKey(NUM8);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 8");
                    }
                    break;

                case sf::Keyboard::Key::Num9:
                    eventKeyboard.setKey(NUM9);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 9");
                    }
                    break;

                case sf::Keyboard::Key::Num0:
                    eventKeyboard.setKey(NUM0);
                    if (output) {
                        LM.writeLog("InputManager: Pressed key 0");
                    }
                    break;
            }

            onEvent(&eventKeyboard);
        }

        // Key was released?
        if (p_event -> getIf<sf::Event::KeyReleased>())
        {
            // Setup as KeyReleased event.
            sf::Event::KeyReleased *p_kb_event = reinterpret_cast<sf::Event::KeyReleased *> (&e);

            // Get SFML keyboard code.
            sf::Keyboard::Key key;
            key = p_kb_event -> code;

            EventKeyboard eventKeyboard;
            eventKeyboard.setKeyboardAction(KEY_RELEASED);

            switch (key) {
                case sf::Keyboard::Key::Space:
                    eventKeyboard.setKey(SPACE);
                    if (output) {
                        LM.writeLog("InputManager: Released key Space");
                    }
                    break;

                case sf::Keyboard::Key::Enter:
                    eventKeyboard.setKey(RETURN);
                    if (output) {
                        LM.writeLog("InputManager: Released key Return");
                    }
                    break;

                case sf::Keyboard::Key::Escape:
                    eventKeyboard.setKey(ESCAPE);
                    if (output) {
                        LM.writeLog("InputManager: Released key Escape");
                    }
                    break;

                case sf::Keyboard::Key::Tab:
                    eventKeyboard.setKey(TAB);
                    if (output) {
                        LM.writeLog("InputManager: Released key Tab");
                    }
                    break;

                case sf::Keyboard::Key::Left:
                    eventKeyboard.setKey(LEFTARROW);
                    if (output) {
                        LM.writeLog("InputManager: Released key LeftArrow");
                    }
                    break;

                case sf::Keyboard::Key::Right:
                    eventKeyboard.setKey(RIGHTARROW);
                    if (output) {
                        LM.writeLog("InputManager: Released key RightArrow");
                    }
                    break;

                case sf::Keyboard::Key::Up:
                    eventKeyboard.setKey(UPARROW);
                    if (output) {
                        LM.writeLog("InputManager: Released key UpArrow");
                    }
                    break;

                case sf::Keyboard::Key::Down:
                    eventKeyboard.setKey(DOWNARROW);
                    if (output) {
                        LM.writeLog("InputManager: Released key DownArrow");
                    }
                    break;

                case sf::Keyboard::Key::Pause:
                    eventKeyboard.setKey(PAUSE);
                    if (output) {
                        LM.writeLog("InputManager: Released key Pause");
                    }
                    break;

                case sf::Keyboard::Key::Subtract:
                    eventKeyboard.setKey(MINUS);
                    if (output) {
                        LM.writeLog("InputManager: Released key Minus");
                    }
                    break;

                case sf::Keyboard::Key::Add:
                    eventKeyboard.setKey(PLUS);
                    if (output) {
                        LM.writeLog("InputManager: Released key Plus");
                    }
                    break;

                case sf::Keyboard::Key::Grave:
                    eventKeyboard.setKey(TILDE);
                    if (output) {
                        LM.writeLog("InputManager: Released key Tilde");
                    }
                    break;

                case sf::Keyboard::Key::Period:
                    eventKeyboard.setKey(PERIOD);
                    if (output) {
                        LM.writeLog("InputManager: Released key Period");
                    }
                    break;

                case sf::Keyboard::Key::Comma:
                    eventKeyboard.setKey(COMMA);
                    if (output) {
                        LM.writeLog("InputManager: Released key Comma");
                    }
                    break;

                case sf::Keyboard::Key::Slash:
                    eventKeyboard.setKey(SLASH);
                    if (output) {
                        LM.writeLog("InputManager: Released key Slash");
                    }
                    break;

                case sf::Keyboard::Key::LControl:
                    eventKeyboard.setKey(LEFTCONTROL);
                    if (output) {
                        LM.writeLog("InputManager: Released key LeftControl");
                    }
                    break;

                case sf::Keyboard::Key::RControl:
                    eventKeyboard.setKey(RIGHTCONTROL);
                    if (output) {
                        LM.writeLog("InputManager: Released key RightControl");
                    }
                    break;

                case sf::Keyboard::Key::LShift:
                    eventKeyboard.setKey(LEFTSHIFT);
                    if (output) {
                        LM.writeLog("InputManager: Released key LeftShift");
                    }
                    break;

                case sf::Keyboard::Key::RShift:
                    eventKeyboard.setKey(RIGHTSHIFT);
                    if (output) {
                        LM.writeLog("InputManager: Released key RightShift");
                    }
                    break;

                case sf::Keyboard::Key::F1:
                    eventKeyboard.setKey(F1);
                    if (output) {
                        LM.writeLog("InputManager: Released key F1");
                    }
                    break;

                case sf::Keyboard::Key::F2:
                    eventKeyboard.setKey(F2);
                    if (output) {
                        LM.writeLog("InputManager: Released key F2");
                    }
                    break;

                case sf::Keyboard::Key::F3:
                    eventKeyboard.setKey(F3);
                    if (output) {
                        LM.writeLog("InputManager: Released key F3");
                    }
                    break;

                case sf::Keyboard::Key::F4:
                    eventKeyboard.setKey(F4);
                    if (output) {
                        LM.writeLog("InputManager: Released key F4");
                    }
                    break;

                case sf::Keyboard::Key::F5:
                    eventKeyboard.setKey(F5);
                    if (output) {
                        LM.writeLog("InputManager: Released key F5");
                    }
                    break;

                case sf::Keyboard::Key::F6:
                    eventKeyboard.setKey(F6);
                    if (output) {
                        LM.writeLog("InputManager: Released key F6");
                    }
                    break;

                case sf::Keyboard::Key::F7:
                    eventKeyboard.setKey(F7);
                    if (output) {
                        LM.writeLog("InputManager: Released key F7");
                    }
                    break;

                case sf::Keyboard::Key::F8:
                    eventKeyboard.setKey(F8);
                    if (output) {
                        LM.writeLog("InputManager: Released key F8");
                    }
                    break;

                case sf::Keyboard::Key::F9:
                    eventKeyboard.setKey(F9);
                    if (output) {
                        LM.writeLog("InputManager: Released key F9");
                    }
                    break;

                case sf::Keyboard::Key::F10:
                    eventKeyboard.setKey(F10);
                    if (output) {
                        LM.writeLog("InputManager: Released key F10");
                    }
                    break;

                case sf::Keyboard::Key::F11:
                    eventKeyboard.setKey(F11);
                    if (output) {
                        LM.writeLog("InputManager: Released key F11");
                    }
                    break;

                case sf::Keyboard::Key::F12:
                    eventKeyboard.setKey(F12);
                    if (output) {
                        LM.writeLog("InputManager: Released key F12");
                    }
                    break;

                case sf::Keyboard::Key::A:
                    eventKeyboard.setKey(A);
                    if (output) {
                        LM.writeLog("InputManager: Released key A");
                    }
                    break;

                case sf::Keyboard::Key::B:
                    eventKeyboard.setKey(B);
                    if (output) {
                        LM.writeLog("InputManager: Released key B");
                    }
                    break;

                case sf::Keyboard::Key::C:
                    eventKeyboard.setKey(C);
                    if (output) {
                        LM.writeLog("InputManager: Released key C");
                    }
                    break;

                case sf::Keyboard::Key::D:
                    eventKeyboard.setKey(D);
                    if (output) {
                        LM.writeLog("InputManager: Released key D");
                    }
                    break;

                case sf::Keyboard::Key::E:
                    eventKeyboard.setKey(E);
                    if (output) {
                        LM.writeLog("InputManager: Released key E");
                    }
                    break;

                case sf::Keyboard::Key::F:
                    eventKeyboard.setKey(F);
                    if (output) {
                        LM.writeLog("InputManager: Released key F");
                    }
                    break;

                case sf::Keyboard::Key::G:
                    eventKeyboard.setKey(G);
                    if (output) {
                        LM.writeLog("InputManager: Released key G");
                    }
                    break;

                case sf::Keyboard::Key::H:
                    eventKeyboard.setKey(H);
                    if (output) {
                        LM.writeLog("InputManager: Released key H");
                    }
                    break;

                case sf::Keyboard::Key::I:
                    eventKeyboard.setKey(I);
                    if (output) {
                        LM.writeLog("InputManager: Released key I");
                    }
                    break;

                case sf::Keyboard::Key::J:
                    eventKeyboard.setKey(J);
                    if (output) {
                        LM.writeLog("InputManager: Released key J");
                    }
                    break;

                case sf::Keyboard::Key::K:
                    eventKeyboard.setKey(K);
                    if (output) {
                        LM.writeLog("InputManager: Released key K");
                    }
                    break;

                case sf::Keyboard::Key::L:
                    eventKeyboard.setKey(L);
                    if (output) {
                        LM.writeLog("InputManager: Released key L");
                    }
                    break;

                case sf::Keyboard::Key::M:
                    eventKeyboard.setKey(M);
                    if (output) {
                        LM.writeLog("InputManager: Released key M");
                    }
                    break;

                case sf::Keyboard::Key::N:
                    eventKeyboard.setKey(N);
                    if (output) {
                        LM.writeLog("InputManager: Released key N");
                    }
                    break;

                case sf::Keyboard::Key::O:
                    eventKeyboard.setKey(O);
                    if (output) {
                        LM.writeLog("InputManager: Released key O");
                    }
                    break;

                case sf::Keyboard::Key::P:
                    eventKeyboard.setKey(P);
                    if (output) {
                        LM.writeLog("InputManager: Released key P");
                    }
                    break;

                case sf::Keyboard::Key::Q:
                    eventKeyboard.setKey(Q);
                    if (output) {
                        LM.writeLog("InputManager: Released key Q");
                    }
                    break;

                case sf::Keyboard::Key::R:
                    eventKeyboard.setKey(R);
                    if (output) {
                        LM.writeLog("InputManager: Released key R");
                    }
                    break;

                case sf::Keyboard::Key::S:
                    eventKeyboard.setKey(S);
                    if (output) {
                        LM.writeLog("InputManager: Released key S");
                    }
                    break;

                case sf::Keyboard::Key::T:
                    eventKeyboard.setKey(T);
                    if (output) {
                        LM.writeLog("InputManager: Released key T");
                    }
                    break;

                case sf::Keyboard::Key::U:
                    eventKeyboard.setKey(U);
                    if (output) {
                        LM.writeLog("InputManager: Released key U");
                    }
                    break;

                case sf::Keyboard::Key::V:
                    eventKeyboard.setKey(V);
                    if (output) {
                        LM.writeLog("InputManager: Released key V");
                    }
                    break;

                case sf::Keyboard::Key::W:
                    eventKeyboard.setKey(W);
                    if (output) {
                        LM.writeLog("InputManager: Released key W");
                    }
                    break;

                case sf::Keyboard::Key::X:
                    eventKeyboard.setKey(X);
                    if (output) {
                        LM.writeLog("InputManager: Released key X");
                    }
                    break;

                case sf::Keyboard::Key::Y:
                    eventKeyboard.setKey(Y);
                    if (output) {
                        LM.writeLog("InputManager: Released key Y");
                    }
                    break;

                case sf::Keyboard::Key::Z:
                    eventKeyboard.setKey(Z);
                    if (output) {
                        LM.writeLog("InputManager: Released key Z");
                    }
                    break;

                case sf::Keyboard::Key::Num1:
                    eventKeyboard.setKey(NUM1);
                    if (output) {
                        LM.writeLog("InputManager: Released key 1");
                    }
                    break;

                case sf::Keyboard::Key::Num2:
                    eventKeyboard.setKey(NUM2);
                    if (output) {
                        LM.writeLog("InputManager: Released key 2");
                    }
                    break;

                case sf::Keyboard::Key::Num3:
                    eventKeyboard.setKey(NUM3);
                    if (output) {
                        LM.writeLog("InputManager: Released key 3");
                    }
                    break;

                case sf::Keyboard::Key::Num4:
                    eventKeyboard.setKey(NUM4);
                    if (output) {
                        LM.writeLog("InputManager: Released key 4");
                    }
                    break;

                case sf::Keyboard::Key::Num5:
                    eventKeyboard.setKey(NUM5);
                    if (output) {
                        LM.writeLog("InputManager: Released key 5");
                    }
                    break;

                case sf::Keyboard::Key::Num6:
                    eventKeyboard.setKey(NUM6);
                    if (output) {
                        LM.writeLog("InputManager: Released key 6");
                    }
                    break;

                case sf::Keyboard::Key::Num7:
                    eventKeyboard.setKey(NUM7);
                    if (output) {
                        LM.writeLog("InputManager: Released key 7");
                    }
                    break;

                case sf::Keyboard::Key::Num8:
                    eventKeyboard.setKey(NUM8);
                    if (output) {
                        LM.writeLog("InputManager: Released key 8");
                    }
                    break;

                case sf::Keyboard::Key::Num9:
                    eventKeyboard.setKey(NUM9);
                    if (output) {
                        LM.writeLog("InputManager: Released key 9");
                    }
                    break;

                case sf::Keyboard::Key::Num0:
                    eventKeyboard.setKey(NUM0);
                    if (output) {
                        LM.writeLog("InputManager: Released key 0");
                    }
                    break;
            }

            onEvent(&eventKeyboard);
        }
        
        // Mouse moved?
        if (p_event -> getIf<sf::Event::MouseMoved>())
        {
            // Setup as MouseMoved event.
            sf::Event::MouseMoved *p_mse_event = reinterpret_cast<sf::Event::MouseMoved *> (&e);

            // Get pixel location.
            sf::Vector2i pixel_pos = p_mse_event -> position;

            EventMouse eventMouse;
            eventMouse.setMouseAction(MOVED);
            eventMouse.setMousePosition(DM.pixelsToSpaces(Vector (pixel_pos.x, pixel_pos.y)));
            if (output)
            {
                LM.writeLog("InputManager: Moved mouse");
            }

            onEvent(&eventMouse);
        }

        // Mouse clicked?
        if (p_event -> getIf<sf::Event::MouseButtonPressed>())
        {
            // Setup as MouseButtonPressed event.
            sf::Event::MouseButtonPressed *p_mse_event = reinterpret_cast<sf::Event::MouseButtonPressed *> (&e);

            // Get pixel location.
            sf::Vector2i pixel_pos = p_mse_event -> position;

            EventMouse eventMouse;
            eventMouse.setMouseAction(CLICKED);
            eventMouse.setMousePosition(DM.pixelsToSpaces(Vector (pixel_pos.x, pixel_pos.y)));

            if (p_mse_event -> button == sf::Mouse::Button::Left)
            {
                eventMouse.setMouseButton(LEFT);
                if (output)
                {
                    LM.writeLog("InputManager: Pressed left mouse button");
                }
            }
            else if (p_mse_event -> button == sf::Mouse::Button::Right)
            {
                eventMouse.setMouseButton(RIGHT);
                if (output)
                {
                    LM.writeLog("InputManager: Pressed right mouse button");
                }
            }
            else if (p_mse_event -> button == sf::Mouse::Button::Middle)
            {
                eventMouse.setMouseButton(MIDDLE);
                if (output)
                {
                    LM.writeLog("InputManager: Pressed middle mouse button");
                }
            }

            onEvent(&eventMouse);
        }
    }
}