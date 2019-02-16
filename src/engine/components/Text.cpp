//
// Created by Maksym Maisak on 2019-02-15.
//

#include "Text.h"

using namespace en;

void addGlyphQuad(std::vector<Vertex>& vertices, const glm::vec2& position, const sf::Glyph& glyph, const glm::vec2& atlasSize) {

    const float padding = 0.5f;

    const float left   =  glyph.bounds.left - padding;
    const float bottom = -glyph.bounds.top - glyph.bounds.height - padding;
    const float right  =  glyph.bounds.left + glyph.bounds.width + padding;
    const float top    = -glyph.bounds.top + padding;

    float u1 = static_cast<float>(glyph.textureRect.left) - padding;
    float v1 = static_cast<float>(glyph.textureRect.top  + glyph.textureRect.height) + padding;
    float u2 = static_cast<float>(glyph.textureRect.left + glyph.textureRect.width)  + padding;
    float v2 = static_cast<float>(glyph.textureRect.top ) - padding;
    const glm::vec2 multiplier = 1.f / atlasSize;
    u1 *= multiplier.x;
    u2 *= multiplier.x;
    v1 *= multiplier.y;
    v2 *= multiplier.y;

    vertices.push_back({{position.x + left , position.y + bottom, 0.f}, {u1, v1}});
    vertices.push_back({{position.x + right, position.y + top   , 0.f}, {u2, v2}});
    vertices.push_back({{position.x + left , position.y + top   , 0.f}, {u1, v2}});

    vertices.push_back({{position.x + left , position.y + bottom, 0.f}, {u1, v1}});
    vertices.push_back({{position.x + right, position.y + bottom, 0.f}, {u2, v1}});
    vertices.push_back({{position.x + right, position.y + top   , 0.f}, {u2, v2}});
}

const std::string& Text::getString() const {
    return m_string;
}

void Text::setString(const std::string& newString) {
    m_needsGeometryUpdate = true;
    m_string = newString;
}

const std::shared_ptr<Material>& Text::getMaterial() const {
    return m_material;
}

const std::vector<Vertex>& Text::getVertices() const {
    ensureGeometryUpdate();
    return m_vertices;
}

void Text::ensureGeometryUpdate() const {

    if (!m_needsGeometryUpdate)
        return;

    m_needsGeometryUpdate = false;
    m_vertices.clear();
    if (!m_font || !m_material)
        return;

    m_material->setUniformValue("fontAtlas", m_font);
    m_material->setUniformValue("textColor", glm::vec3(1));

    auto temp = m_font->getTexture(m_characterSize).getSize();
    glm::vec2 atlasSize = {temp.x, temp.y};

    glm::vec2 position = {0, m_characterSize};

    sf::Uint32 previousChar = 0;
    for (char c : m_string) {

        auto currentChar = (sf::Uint32)c;

        position.x += m_font->getKerning(previousChar, currentChar, m_characterSize);
        const sf::Glyph& glyph = m_font->getGlyph(currentChar, m_characterSize, false);
        addGlyphQuad(m_vertices, position, glyph, atlasSize);
        position.x += glyph.advance;

        previousChar = currentChar;
    }
}

namespace {

    std::shared_ptr<Material> readMaterial(LuaState& lua) {

        lua_getfield(lua, -1, "material");
        auto p = lua::PopperOnDestruct(lua);

        if (lua.is<std::shared_ptr<Material>>())
            return lua.to<std::shared_ptr<Material>>();

        return std::make_shared<Material>(lua);
    }
};

Text& Text::addFromLua(Actor& actor, LuaState& lua) {

    auto& text = actor.add<Text>();
    text.m_material = readMaterial(lua);
    return text;
}

void Text::initializeMetatable(LuaState& lua) {

    lua::addProperty(lua, "string", lua::property(
        [](ComponentReference<Text>& ref) {return ref->getString();},
        [](ComponentReference<Text>& ref, const std::string& value) {ref->setString(value);}
    ));

    lua::addProperty(lua, "font", lua::writeonlyProperty(
        [](ComponentReference<Text>& ref, const std::string& filepath) {ref->setFont(Resources<sf::Font>::get(filepath));}
    ));
}

void Text::setMaterial(const std::shared_ptr<Material>& material) {

    m_material = material;
    m_needsGeometryUpdate = true;
}

const std::shared_ptr<sf::Font>& Text::getFont() const {

    return m_font;
}

void Text::setFont(const std::shared_ptr<sf::Font>& font) {

    m_font = font;
    m_needsGeometryUpdate = true;
}
