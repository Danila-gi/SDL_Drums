#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include <string>
#include <random>
#include <expected>

/**
 * @enum    DrumsError
 * @brief   Возможные ошибки при работе с барабанами
 */
enum DrumsError{
    InvalidSlotIndex, // некорретный индекс слота
};

/**
 * @class   DrumsModel
 * @brief   Класс модели барабанов.
 *          Содержит внутренне состояние каждого слота, отвечает за начало и окончание вращения,
 *          за перемещение слотов внутри одного барабана через определенное время.
 */
class DrumsModel{
public:

    /**
     * @struct  SlotState
     * @brief   Структура состояния слота барабана
     */
    struct SlotState{
        std::string text; // текст слота
        SDL_Color fillColor; // фоновый цвет слота
    };

    /**
     * @struct  DrumState
     * @brief   Структура состояния барабана
     */
    struct DrumState{
        std::vector<SlotState> slots; // массив слотов барабана
        int timeSlotsMove {0}; // время (мс), через которое должны сместиться слоты
        int slotsMoveCount {0}; // количество перемещений слотов
        bool isRotating {false}; // статус вращения барабана
        int timeStopRotate {0}; // время (мс), через которое должно закончиться вращение
    };

    /**
     * @brief   Конструктор класса
     * @param   drumsCount  Количество барабанов
     * @param   drumLength  Размер барабана, количество слотов в барабане
     */
    DrumsModel(int drumsCount, int drumLength);

    /**
     * @brief   Начало вращения. Скорость, с которой будет идти вращение, задается каждому барабану случайно.
     * @param   timeStopRotate  Время (мс), через которое должен остановиться первый барабан
     * @param   deltaBetweenStopDrums  Время (мс) между остановкой каждого барабана
     * @param   minTimeSlotsMove  Минимальное время (мс), через которое должны сместиться слоты
     * @param   maxTimeSlotsMove  Максимальное время (мс), через которое должны сместиться слоты
     */
    void startRotation(int timeStopRotate, int deltaBetweenStopDrums, int minTimeSlotsMove, int maxTimeSlotsMove);

    /**
     * @brief   Обновление состояния модели
     * @param   delay  Время (мс) задержки кадра в работе приложения
     */
    void updateState(int delay);

    /**
     * @brief   Получение статуса состояния барабанов (вращаются или нет)
     * @return  true - вращаются, false - не вращаются
     */
    bool isStartRotate() const;

    /**
     * @brief   Получение состояния определенного слота
     * @return  Если данные верные, то вернется объект SlotState, иначе ошибка DrumsError.
     */
    std::expected<SlotState, DrumsError> getSlotState(int indexDrum, int indexSlot) const;

    /**
     * @brief   Получение размеров системы барабанов 
     * @return  Пара чисел: количество барабанов, размер барабана (количество слотов)
     */
    std::pair<int, int> getDrumsSize() const;

private:
    bool mIsStartRotate {false}; // флаг статуса вращения барабана
    int mCurrentTimeRotateCycle {0}; // Время (мс), сколько прошло с начала вращения
    int mDrumsCount {0}; // количество барабанов
    int mDrumLength {0}; // размер барабана (количество слотов)
    std::vector<DrumState> mDrums; // массив барабанов в системе
};