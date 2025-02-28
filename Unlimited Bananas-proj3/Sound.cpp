#include "Sound.h"
#include "LogManager.h"

using namespace df;

Sound::Sound()
{
    m_p_sound = NULL;
    m_label = "";
}

Sound::~Sound()
{
    if (m_p_sound != NULL)
    {
        delete m_p_sound;
        m_p_sound = NULL;
    }
}

int Sound::loadSound(std::string filename)
{
    if (m_sound_buffer.loadFromFile(filename) == false)
    {
        LM.writeLog("Sound: Failed to load '%s'", filename.c_str());
        return -1;
    }

    m_p_sound = new sf::Sound(m_sound_buffer);

    LM.writeLog("Sound: Loaded '%s'", filename.c_str());

    return 0;
}

void Sound::setLabel(std::string new_label)
{
    m_label = new_label;
}

std::string Sound::getLabel() const
{
    return m_label;
}

void Sound::play(bool loop)
{
    m_p_sound -> play();
    
    if (loop == true)
    {
        m_p_sound -> setLooping(true);
    }
    else
    {
        m_p_sound -> setLooping(false);
    }
}

void Sound::stop()
{
    m_p_sound -> stop();
}

void Sound::pause()
{
    m_p_sound -> pause();
}

sf::Sound Sound::getSound() const
{
    return *m_p_sound;
}