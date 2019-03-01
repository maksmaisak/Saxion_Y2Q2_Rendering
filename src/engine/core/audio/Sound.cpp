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
    lua.setField("stop" , [](const std::shared_ptr<Sound>& sound) {sound->getUnderlyingSound().stop(); });
    lua.setField("pause", [](const std::shared_ptr<Sound>& sound) {sound->getUnderlyingSound().pause();});

    lua.setField("setVolume", [](const std::shared_ptr<Sound>& sound, float volume) {sound->getUnderlyingSound().setVolume(volume);});
    lua.setField("setPitch" , [](const std::shared_ptr<Sound>& sound, float pitch ) {sound->getUnderlyingSound().setPitch(pitch);});

    lua.setField("setPlayingOffset", [](const std::shared_ptr<Sound>& sound, float offset) {
        sound->getUnderlyingSound().setPlayingOffset(sf::seconds(offset));
    });

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
