#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>
#include <unordered_map>
#include <memory>

/**
 * @class   FontsContainer
 * @brief   Синглтон класс, содержащий шрифты, который будут использоваться в приложении.
 */
class FontsContainer
{
public:
    /**
     * @brief   Получение указателя на объект класса
     * @return  Указатель на объект FontsContainer
     */
    static FontsContainer* instance();
    /**
     * @brief   Добавление нового шрифта
     * @param   id  ID шрифта
     * @param   filePath    Путь до файла со шрифтом
     * @param   ptsize  Размер текста
     */
    void addFont(const std::string& id, const std::string& filePath, int ptsize);
    ~FontsContainer();

    /**
     * @brief   Получение шрифта по id
     * @param   id  ID шрифта
     * @return  Указатель на объект шрифта TTF_Font, если шрифт не найден, то nullptr
     */
    TTF_Font* getFontById(const std::string& id) const noexcept;

private:
    static bool mIsInit;
    FontsContainer() = default;

    FontsContainer(const FontsContainer&) = delete;
    FontsContainer& operator=(const FontsContainer&) = delete;

    std::unordered_map<std::string, TTF_Font*> mMapFonts;
    static std::unique_ptr<FontsContainer> mInstancePtr;
};