#include "Music.h"
#include "LogManager.h"

using namespace df;

Music::Music()
{
    m_label = "";
}

int Music::loadMusic(std::string filename)
{
    if (m_music.openFromFile(filename) == false)
    {
        LM.writeLog("Music: Failed to load '%s'", filename.c_str());
        return -1;
    }

    LM.writeLog("Music: Loaded '%s'", filename.c_str());

    return 0;
}

void Music::setLabel(std::string new_label)
{
    m_label = new_label;
}

std::string Music::getLabel() const
{
    return m_label;
}

void Music::play(bool loop)
{
    m_music.play();

    if (loop == true)
    {
        m_music.setLooping(true);
    }
    else
    {
        m_music.setLooping(false);
    }
}

void Music::stop()
{
    m_music.stop();
}

void Music::pause()
{
    m_music.pause();
}

sf::Music* Music::getMusic()
{
    return &m_music;
}
