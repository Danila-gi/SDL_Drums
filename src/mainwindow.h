#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <memory>

#include "rotationbutton.h"
#include "drumsmodel.h"
#include "drumsview.h"

/**
 * @class   MainWindow
 * @brief   Класс основного окна приложения
 */
class MainWindow{
public:
    /**
     * @brief   Конструктор класса
     * @param   screenWidth  Ширина окна
     * @param   screenHeight  Высота окна
     * @param   fps  Значение частоты кадров (кол-во кадров в секунду)
     */
    MainWindow(int screenWidth, int screenHeight, int fps);

    /**
     * @brief   Инициализация основных объектов для работы с окном:
     *          сам объект окна и интерфейс дляотрисовки графики (рендерер).
     * @return  Статус успешной инициализации объектов.
     */
    bool init();

    /**
     * @brief   Очистка созданных объектов и закрытие окна.
     */
    void close();

    /**
     * @brief   Запуск цикла ожидания событий от пользователя и обновление кадров. 
     */
    void run();

private:
    /**
     * @brief   Обновление графики каждого объекта окна. 
     */
    void updatePainting();

private:
    std::unique_ptr<RotationButton> mRotationButton; // объект кнопки запуска вращения
    std::unique_ptr<DrumsView> mDrumsView; // объект отображения барабанов
    std::shared_ptr<DrumsModel> mDrumsModel; // объект модели барабанов

    SDL_Window* mWindow {nullptr}; // объект окна
    SDL_Renderer* mRenderer {nullptr}; // объект рендерера
    int mScreenWidth {0}; // ширина окна
    int mScreenHeight {0}; // высота окна

    int mTargetFPS {60}; // желаемое fps приложения
    int mRealFPS {60}; // текущее fps приложения
};