//
// Created by Maksym Maisak on 2019-02-15.
//

#ifndef SAXION_Y2Q2_RENDERING_TEXT_H
#define SAXION_Y2Q2_RENDERING_TEXT_H

#include <string>
#include <vector>
#include <SFMl/Graphics.hpp>
#include "Vertex.h"
#include "Material.h"
#include "ComponentsToLua.h"
#include "Resources.h"

namespace en {

    class Text {

        LUA_TYPE(Text);

    public:
        static Text& addFromLua(Actor& actor, LuaState& lua);
        static void initializeMetatable(LuaState& lua);

        const std::string& getString() const;
        void setString(const std::string& newString);

        const std::shared_ptr<Material>& getMaterial() const;
        void setMaterial(const std::shared_ptr<Material>& material);

        const std::shared_ptr<sf::Font>& getFont() const;
        void setFont(const std::shared_ptr<sf::Font>& font);

        const std::vector<Vertex>& getVertices() const;

    private:

        void ensureGeometryUpdate() const;

        std::string m_string;
        std::shared_ptr<sf::Font> m_font = Resources<sf::Font>::get(config::FONT_PATH + "arial.ttf");
        std::shared_ptr<Material> m_material;
        unsigned int m_characterSize = 30;

        mutable bool m_needsGeometryUpdate = false;
        mutable std::vector<Vertex> m_vertices;
    };
}

#endif //SAXION_Y2Q2_RENDERING_TEXT_H
