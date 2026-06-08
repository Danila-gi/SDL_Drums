#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

/**
 * @enum    ButtonState
 * @brief   Возможные состояния кнопки
 */
enum ButtonState{
    NORMAL, // нормальное состояние, можно запустить вращение
    PRESSED // нажатое, идет вращение, не реагирует на нажатие
};

/**
 * @class   RotationButton
 * @brief   Класс описывает отрисовку и взаимодействие с кнопкой начала вращения
 */
class RotationButton{
public:
    /**
     * @brief   Конструктор класса
     * @param   x   Координата X кнопки
     * @param   y   Координата Y кнопки
     * @param   w   Ширина кнопки
     * @param   h   Высота кнопки
     * @param   timeChangeNormalStyle   Время (мс), через которое будет меняться цвет кнопки в нормальном состоянии
     */
    RotationButton(int x, int y, int w, int h, int timeChangeNormalStyle);

    /**
     * @brief   Задать кнопке новое состояние
     * @param   state   Новое состояние кнопки
     */
    void setState(ButtonState state);

    /**
     * @brief   Получение прямоугольника данной кнопки
     * @return  Константный указатель на объект прямоугольника SDL_Rect
     */
    const SDL_Rect* getRect() const;

    /**
     * @brief   Получение текущего состояния кнопки
     * @return  Текущее состояние кнопки ButtonState
     */
    ButtonState getState() const;

    /**
     * @brief   Отрисовка текущей графики кнопки
     * @param   renderer    Указатель на рендерер, на котором будет происходить отрисовка
     */
    void paint(SDL_Renderer* renderer);

    /**
     * @brief   Обновление состояния кнопки, при нормальном состоянии происходит смена стиля
     * @param   delay  Время (мс) задержки кадра в работе приложения
     */
    void updateButton(int delay);

    /**
     * @brief   Проверка, что переданные координаты будут внутри кнопки
     * @param   x   Координата X в окне приложения
     * @param   y   Координата Y в окне приложения
     * @return  Результат сравнение переданных координат и координат квадрата, true - если координаты внутри кнопки
     */
    bool isCoordsInsideRect(int x, int y) const;

    /**
     * @brief   Освобождение ресурсов кнопки: очистка поверхности, на которой находился шрифт с текстом
     */
    void release();

private:
    /**
     * @brief   Загрузка стилей для кнопки
     */
    void loadStyles();

    /**
     * @brief   Обновление текущего стиля кнопки на нормальное 
     */
    void updateToNormalState();

    /**
     * @brief   Обновление текущего стиля кнопки на нажатое 
     */
    void updateToPressedState();

private:
    ButtonState mButtonState {NORMAL}; // текущее состояние кнопки
    SDL_Rect mRect; // прямогольник кнопки
    SDL_Surface* mFontSurface {nullptr}; // поверхность, на которой написан текст определенного шрифта

    SDL_Color mCurrentStyle; // текущий стиль кнопки
    SDL_Color mPressedStyle; // стиль кнопки (ее цвет) принажатом состоянии
    std::vector<SDL_Color> mNormalStyles; // стили кнопки (ее возможные цвета) при нормальном состоянии
    int mTimeChangeNormalStyle {500}; // время (мс), через которое будет меняться цвет кнопки в нормальном состоянии
    int mCurrentTimeNormalPaintCycle {0}; // время (мс), которое прошло после обновления стиля в нормальном состоянии
    int mCurrentNormalStyleIndex {0}; // индекс стиля, который выбран в текущий момент
};