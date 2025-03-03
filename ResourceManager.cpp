#include <iostream>
#include <fstream>
#include <string>

#include "ResourceManager.h"
#include "LogManager.h"

using namespace df;

ResourceManager::ResourceManager()
{
    setType("ResourceManager");

    m_sprite_count = 0;
}

ResourceManager& ResourceManager::getInstance()
{
    static ResourceManager single;
    return single;
}

int ResourceManager::startUp()
{
    sound_count = 0;
    music_count = 0;

    Manager::startUp();
    return 0;
}

void ResourceManager::shutDown()
{
    for (int i=0; i<m_sprite_count; i++)
    {
        if (m_p_sprite[i] != NULL)
        {
            delete m_p_sprite[i];
        }
    }

    m_sprite_count = 0;

    Manager::shutDown();
}

int ResourceManager::loadSprite(std::string filename, std::string label)
{
    // Check if room in array.
    if (m_sprite_count == MAX_SPRITES)  // Sprite array full?
    {
        LM.writeLog("ResouceManager: Sprite array full.");
        return -1;
    }

    std::string line;
    std::ifstream file(filename);
    
    // Open file.
    if (file.is_open())
    {
        bool error = false;

        while (true)
        {
            LM.writeLog("ResourceManager: Loading '%s' from file '%s'.", label.c_str(), filename.c_str());
        
            // Read sprite Header.
            getline(file, line);    // Read line from file.
            if (atoi(line.c_str()) <= 0)    // Is line a positive integer?
            {
                LM.writeLog("ResouceManager: Error on line 1. Expected positive integer number of frames.");
                error = true;
                break;
            }
            int frames = atoi(line.c_str());

            getline(file, line);
            if (atoi(line.c_str()) <= 0)    // Is line a positive integer?
            {
                LM.writeLog("ResouceManager: Error on line 2. Expected positive integer width.");
                error = true;
                break;
            }
            int width = atoi(line.c_str());

            getline(file, line);
            if (atoi(line.c_str()) <= 0)    // Is line a positive integer?
            {
                LM.writeLog("ResouceManager: Error on line 3. Expected positive integer height.");
                error = true;
                break;
            }
            int height = atoi(line.c_str());

            getline(file, line);
            if (atoi(line.c_str()) <= 0)    // Is line a positive integer?
            {
                LM.writeLog("ResouceManager: Error on line 4. Expected positive integer slowdown.");
                error = true;
                break;
            }
            int slowdown = atoi(line.c_str());

            getline(file, line);
            Color color;
            if (line == "black")
            {
                color = BLACK;
            }
            else if (line == "red")
            {
                color = RED;
            }
            else if (line == "green")
            {
                color = GREEN;
            }
            else if (line == "yellow")
            {
                color = YELLOW;
            }
            else if (line == "blue")
            {
                color = BLUE;
            }
            else if (line == "magenta")
            {
                color = MAGENTA;
            }
            else if (line == "cyan")
            {
                color = CYAN;
            }
            else if (line == "white")
            {
                color = WHITE;
            }
            else
            {
                LM.writeLog("ResourceManager: Error on line 5. %s unknown color.", line);
                error = true;
                break;
            }
            
            // Make new Sprite.
            Sprite *sprite = new Sprite(frames);
            sprite -> setHeight(height);
            sprite -> setWidth(width);
            sprite -> setSlowdown(slowdown);
            sprite -> setColor(color);

            int line_number = 5;
            // Read and add frames to Sprite.
            for (int f=0; f<frames; f++)
            {
                std::string s;
                for (int h=0; h<height; h++)
                {
                    getline(file, line);
                    line_number++;

                    if (line == "")
                    {
                        LM.writeLog("ResourceManager: Error on line %d. Incorrect frame height.", line_number);
                        error = true;
                        break;
                    }

                    if (line.length() != width)
                    {
                        LM.writeLog("ResourceManager: Error on line %d. Incorrect frame width.", line_number);
                        error = true;
                        break;
                    }

                    s += line;
                    line = "";
                }

                if (error == true)
                {
                    break;
                }

                Frame frame(width, height, s);
                sprite -> addFrame(frame);
            }

            if (error == true)
            {
                break;
            }

            // Close file when done.
            file.close();

            // If no errors in any of above, add to resource manager.
            sprite -> setLabel(label);
            m_p_sprite[m_sprite_count] = sprite;
            m_sprite_count++;

            LM.writeLog("ResourceManager: Loaded sprite '%s'.", label.c_str());
            break;
        }

        if (error)
        {
            file.close();
            LM.writeLog("ResourceManager: Sprite '%s' not loaded.", label.c_str());
            return -1;
        }
    }
    else
    {
        // If here, unable to open file.
        LM.writeLog("ResourceManager: Unable to open file %s", filename.c_str());
        return -1;
    }

    return 0;
}

int ResourceManager::unloadSprite(std::string label)
{
    for (int i=0; i<m_sprite_count; i++)
    {
        if (label == m_p_sprite[i] -> getLabel())
        {
            delete m_p_sprite[i];

            // Scoot over remaining sprites.
            for (int j=i; j<m_sprite_count-1; j++)
            {
                m_p_sprite[j] = m_p_sprite[j+1];
            }

            m_sprite_count--;

            LM.writeLog("ResourceManager: Unloaded sprite '%s'.", label.c_str());

            return 0;
        }
    }

    LM.writeLog("ResourceManager: Could not unload sprite, '%s' not found.", label.c_str());
    return -1;  // Sprite not found.
}

Sprite* ResourceManager::getSprite(std::string label) const
{
    for (int i=0; i<m_sprite_count; i++)
    {
        if (label == m_p_sprite[i] -> getLabel())
        {
            return m_p_sprite[i];
        }
    }

    LM.writeLog("ResourceManager: Sprite '%s' not found.", label.c_str());
    return NULL;    // Sprite not found.
}

int ResourceManager::loadSound(std::string filename, std::string label)
{
    if (sound_count == MAX_SOUNDS)
    {
        LM.writeLog("ResourceManager: Sound array full.");
        return -1;
    }

    if (sound[sound_count].loadSound(filename) == -1)
    {
        LM.writeLog("ResourceManager: Unable to load from file '%s'", filename.c_str());
        return -1;
    }

    sound[sound_count].setLabel(label);
    sound_count++;

    LM.writeLog("ResourceManager: Loaded sound '%s'.", label.c_str());

    return 0;
}

int ResourceManager::unloadSound(std::string label)
{
    for (int i=0; i<sound_count; i++)
    {
        if (label == sound[i].getLabel())
        {
            // Scoot over remaining sounds.
            for (int j=i; j<sound_count-1; j++)
            {
                sound[j] = sound[j+1];
            }

            sound_count--;

            LM.writeLog("ResourceManager: Unloaded sound '%s'.", label.c_str());

            return 0;
        }
    }

    LM.writeLog("ResourceManager: Could not unload sound, '%s' not found.", label.c_str());
    return -1;  // Sound not found.
}

Sound* ResourceManager::getSound(std::string label)
{
    for (int i=0; i<sound_count; i++)
    {
        if (label == sound[i].getLabel())
        {
            return &sound[i];
        }
    }

    LM.writeLog("ResourceManager: Sound '%s' not found.", label.c_str());
    return NULL;    // Sound not found.
}

int ResourceManager::loadMusic(std::string filename, std::string label)
{
    if (music_count == MAX_MUSICS)
    {
        LM.writeLog("ResourceManager: Music array full.");
        return -1;
    }

    if (music[music_count].loadMusic(filename) == -1)
    {
        LM.writeLog("ResouceManager: Unable to load from file '%s'", filename.c_str());
        return -1;
    }

    music[music_count].setLabel(label);
    music_count++;

    LM.writeLog("ResourceManager: Loaded music '%s'.", label.c_str());

    return 0;
}

int ResourceManager::unloadMusic(std::string label)
{
    for (int i=0; i<music_count; i++)
    {
        if (label == music[i].getLabel())
        {
            music[i].setLabel("");

            music_count--;

            LM.writeLog("ResourceManager: Unloaded music '%s'.", label.c_str());

            return 0;
        }
    }

    LM.writeLog("ResourceManager: Could not unload music, '%s' not found.", label.c_str());
    return -1;  // Music not found.
}

Music* ResourceManager::getMusic(std::string label)
{
    for (int i=0; i<music_count; i++)
    {
        if (label == music[i].getLabel())
        {
            return &music[i];
        }
    }

    LM.writeLog("ResourceManager: Music '%s' not found.", label.c_str());
    return NULL;    // Music not found.
}