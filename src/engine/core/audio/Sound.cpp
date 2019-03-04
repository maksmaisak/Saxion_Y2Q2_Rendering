//
// Created by Maksym Maisak on 2019-03-01.
//

#include "Sound.h"
#include <cassert>
#include "Resources.h"
#include "LuaState.h"
#include "LuaStack.h"
#include "MetatableHelper.h"

using namespace en;

Sound::Sound(const std::shared_ptr<sf::SoundBuffer>& buffer) : m_buffer(buffer) , m_sound(*buffer) {
    assert(buffer);
}

Sound::Sound(const std::string& filepath) : Sound(Resources<sf::SoundBuffer>::get(filepath)) {}

sf::Sound& Sound::getUnderlyingSound() {
    return m_sound;
}

void Sound::initializeMetatable(LuaState& lua) {

    lua.setField("play" , [](const std::shared_ptr<Sound>& sound) {sound->getUnderlyingSound().play(); });
    lua.setField("pause", [](const std::shared_ptr<Sound>& sound) {sound->getUnderlyingSound().pause();});
    lua.setField("stop" , [](const std::shared_ptr<Sound>& sound) {sound->getUnderlyingSound().stop(); });

    lua.setField("volume", lua::property(
        [](const std::shared_ptr<Sound>& sound) {return sound->getUnderlyingSound().getVolume();},
        [](const std::shared_ptr<Sound>& sound, float volume) {sound->getUnderlyingSound().setVolume(volume);}
    ));

    lua.setField("pitch", lua::property(
        [](const std::shared_ptr<Sound>& sound) {return sound->getUnderlyingSound().getPitch();},
        [](const std::shared_ptr<Sound>& sound, float pitch) {sound->getUnderlyingSound().setPitch(pitch);}
    ));

    lua.setField("playingOffset", lua::property(
        [](const std::shared_ptr<Sound>& sound) {return sound->getUnderlyingSound().getPlayingOffset().asSeconds();},
        [](const std::shared_ptr<Sound>& sound, float offset) {sound->getUnderlyingSound().setPlayingOffset(sf::seconds(offset));}
    ));

    lua.setField("loop", lua::property(
        [](const std::shared_ptr<Sound>& sound) {return sound->getUnderlyingSound().getLoop();},
        [](const std::shared_ptr<Sound>& sound, bool loop) {sound->getUnderlyingSound().setLoop(loop);}
    ));

    lua.setField("status", lua::readonlyProperty(
        [](const std::shared_ptr<Sound>& sound) {
            sf::Sound::Status status = sound->getUnderlyingSound().getStatus();
            switch (status) {
                case sf::Sound::Status::Playing:
                    return "Playing";
                case sf::Sound::Status::Paused:
                    return "Paused";
                case sf::Sound::Status::Stopped:
                    return "Stopped";
                default:
                    return "INVALID_SOUND_STATUS";
            }
        }
    ));

    lua::addProperty(lua, "duration", lua::readonlyProperty([](const std::shared_ptr<Sound>& sound) {
        return sound->getUnderlyingSound().getBuffer()->getDuration().asSeconds();
    }));
}

namespace en {

    template<>
    struct ResourceLoader<sf::SoundBuffer> {

        inline static std::shared_ptr<sf::SoundBuffer> load(const std::string& filepath) {

            auto buffer = std::make_shared<sf::SoundBuffer>();
            if (!buffer->loadFromFile(filepath)) {
                std::cerr << "Couldn't load sound from: " << filepath << std::endl;
                return nullptr;
            }

            return buffer;
        }
    };
}
