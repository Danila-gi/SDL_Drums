#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>
#include <unordered_map>

#include "drumsmodel.h"

/**
 * @class   DrumsView
 * @brief   Класс отображения барабанов.
 *          Обновляет графику барабанов по текущему состоянию модели.
 */
class DrumsView{
public:
    /**
     * @brief   Конструктор класса
     * @param   slotSize  Размер квадрата, в котором будет расположен слот
     * @param   drumsCoordX  Координата X верхнего слота левого барабана
     * @param   drumsCoordX  Координата Y верхнего слота левого барабана
     */
    DrumsView(int slotSize, int drumsCoordX, int drumsCoordY);

    /**
     * @brief   Передача объекта модели барабанов
     * @param   drumsModel  Объект модели барабанов
     */
    void setModel(std::shared_ptr<DrumsModel> drumsModel);
    /**
     * @brief   Передача рендерера, на котором будет происходить отрисовка
     * @param   renderer  Указатель на рендерер, на котором будет происходить отрисовка
     */
    void setRenderer(SDL_Renderer* renderer);

    /**
     * @brief   Инициализация текстур слотов
     */
    void initTextures();

    /**
     * @brief   Очистка текстур слотов
     */
    void release();

    /**
     * @brief   Отрисовка барабанов по текущему состоянию модели
     */
    void paint();

private:
    /**
     * @brief   Загрузка стилей для барабанов
     */
    void loadStyles();

private:
    SDL_Color mSlotRectStyle; // цвет границ квадрата, в котором будет располагаться слот
    SDL_Color mSlotTextStyle; // цвет текста внутри слота
    std::shared_ptr<DrumsModel> mDrumsModel; // объект модели барабанов
    std::unordered_map<std::string, SDL_Texture*> mSlotsTextures; // неупорядоченная map для хранения 
                                                                  // соответствия: текст слота -> текстура

    SDL_Renderer* mRenderer; // текущий рендерер, на котором будет отрисовка

    int mDrumsCoordX {0}; // координата X верхнего слота левого барабана
    int mDrumsCoordY {0}; // координата Y верхнего слота левого барабана

    int mSlotSize {0}; // размер квадрата, в котором будет расположен слот
};