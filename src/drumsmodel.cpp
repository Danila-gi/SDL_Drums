#include "drumsmodel.h"

DrumsModel::DrumsModel(int drumsCount, int drumLength)
    : mDrumsCount {drumsCount}
    , mDrumLength {drumLength}
{
    mDrums.reserve(drumsCount);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 255);
    for (int i = 0; i < drumsCount; i++){
        DrumState drumState;
        drumState.slots.reserve(drumLength);
        for (int j = 0; j < drumLength; j++){
            const auto slotText = "X" + std::to_string(j) + std::to_string(i);
            SDL_Color slotFillColor = {
                .r = static_cast<Uint8>(distrib(gen)),
                .g = static_cast<Uint8>(distrib(gen)),
                .b = static_cast<Uint8>(distrib(gen)),
                .a = 255
            };
            SlotState slot {.text = slotText, .fillColor = slotFillColor};
            drumState.slots.push_back(slot);
        }
        drumState.isRotating = false;
        mDrums.push_back(drumState);
    }
}

void DrumsModel::startRotation(int timeStopRotate, int deltaBetweenStopDrums)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(200, 500);

    for (int i = 0; i < mDrumsCount; i++){
        mDrums[i].isRotating = true;
        mDrums[i].timeSlotsMove = distrib(gen);
        mDrums[i].slotsMoveCount = 0;
        mDrums[i].timeStopRotate = timeStopRotate + i * deltaBetweenStopDrums;
    }
    mIsStartRotate = true;
    mCurrentTimeRotateCycle = 0;
}

bool DrumsModel::isStartRotate() const
{
    return mIsStartRotate;
}

std::pair<int, int> DrumsModel::getDrumsSize() const
{
    return {mDrumsCount, mDrumLength};
}

std::expected<DrumsModel::SlotState, bool> DrumsModel::getSlotState(int indexDrum, int indexSlot) const
{
    if (indexDrum < 0 || indexDrum >= mDrumsCount
        || indexSlot < 0 || indexSlot >= mDrumLength){
            return std::unexpected<bool>(false);
    }
    if (mDrums.empty() || mDrums[indexDrum].slots.empty()){
        return std::unexpected<bool>(false);
    }
    return mDrums[indexDrum].slots[indexSlot];
}

std::expected<std::string, bool> DrumsModel::getTextFromSlot(int indexDrum, int indexSlot) const
{
    const auto slotState = getSlotState(indexDrum, indexSlot);
    if (slotState.has_value()){
        return slotState->text;
    }
    return std::unexpected<bool>(false);
}

std::expected<SDL_Color, bool> DrumsModel::getFillColorFromSlot(int indexDrum, int indexSlot) const
{
    const auto slotState = getSlotState(indexDrum, indexSlot);
    if (slotState.has_value()){
        return slotState->fillColor;
    }
    return std::unexpected<bool>(false);
}

void DrumsModel::updateState(int delay)
{
    mCurrentTimeRotateCycle += delay;
    bool isAllStopRotate = true;
    for (int i = 0; i < mDrumsCount; i++){
        if (!mDrums[i].isRotating){
            continue;
        }
        if (mCurrentTimeRotateCycle >= mDrums[i].timeStopRotate){
            mDrums[i].isRotating = false;
            continue;
        }
        isAllStopRotate = false;
        if (mCurrentTimeRotateCycle >= mDrums[i].timeSlotsMove * mDrums[i].slotsMoveCount){
            std::vector<SlotState> newSlots;
            newSlots.reserve(mDrumLength);

            newSlots.push_back(mDrums[i].slots.back());
            for (int j = 0; j < mDrumLength - 1; j++){
                newSlots.push_back(mDrums[i].slots[j]);
            }
            mDrums[i].slots = newSlots;
            mDrums[i].slotsMoveCount++;
        }
    }
    if (isAllStopRotate){
        mIsStartRotate = false;
    }
}