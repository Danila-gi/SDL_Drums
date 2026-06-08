#include "drumsview.h"

#include <iostream>
#include "fontscontainer.h"

DrumsView::DrumsView(int slotSize, int drumsCoordX, int drumsCoordY)
    : mSlotSize {slotSize}
    , mDrumsCoordX {drumsCoordX}
    , mDrumsCoordY {drumsCoordY}
{
    loadStyles();
}

void DrumsView::loadStyles()
{
    mSlotTextStyle = {.r = 0, .g = 0, .b = 0, .a = 255};
    mSlotRectStyle = {.r = 0, .g = 0, .b = 0, .a = 255};
}

void DrumsView::setModel(std::shared_ptr<DrumsModel> drumsModel)
{
    mDrumsModel = drumsModel;
}

void DrumsView::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

void DrumsView::initTextures()
{
    if (!mDrumsModel || !mRenderer){
        return;
    }
    const auto fontsContainer = FontsContainer::instance();
    if (!fontsContainer){
        return;
    }
    const auto font = FontsContainer::instance()->getFontById("info_text");
    if (!font){
        return;
    }
    for (int i = 0; i < mDrumsModel->getDrumsSize().first; i++){
        for (int j = 0; j < mDrumsModel->getDrumsSize().second; j++){
            const auto slotState = mDrumsModel->getSlotState(i, j);
            if (!slotState.has_value()){
                continue;
            }
            auto fontSurface = TTF_RenderText_Solid(font, slotState->text.c_str(), mSlotTextStyle);
            auto fontTex = SDL_CreateTextureFromSurface(mRenderer, fontSurface);
            mSlotsTextures.insert({slotState->text, fontTex});
        }
    }
}

void DrumsView::paint()
{
    const auto fontsContainer = FontsContainer::instance();
    if (!fontsContainer){
        return;
    }
    const auto font = FontsContainer::instance()->getFontById("info_text");
    if (!mDrumsModel || !font || !mRenderer){
        return;
    }
    for (int i = 0; i < mDrumsModel->getDrumsSize().first; i++){
        for (int j = 0; j < mDrumsModel->getDrumsSize().second; j++){
            const auto slotState = mDrumsModel->getSlotState(i, j);
            if (!slotState.has_value()){
                continue;
            }
            if (mSlotsTextures.find(slotState->text) == mSlotsTextures.end()){
                continue;
            }
            const auto slotFillColor = slotState->fillColor;
            
            SDL_SetRenderDrawColor(mRenderer, 
                slotFillColor.r, slotFillColor.g, 
                slotFillColor.b, slotFillColor.a
            );
            
            SDL_Rect rectSlot = {
                .x = mDrumsCoordX + i * mSlotSize,
                .y = mDrumsCoordY + j * mSlotSize,
                .w = mSlotSize, 
                .h = mSlotSize
            };
            SDL_RenderFillRect(mRenderer, &rectSlot);
            SDL_SetRenderDrawColor(mRenderer, 
                mSlotRectStyle.r, mSlotRectStyle.g, 
                mSlotRectStyle.b, mSlotRectStyle.a
            );
            SDL_RenderDrawRect(mRenderer, &rectSlot);
            auto fontTex = mSlotsTextures[slotState->text];
            int fontW, fontH;
            SDL_QueryTexture(fontTex, NULL, NULL, &fontW, &fontH);
            int slotCenterX = rectSlot.x + rectSlot.w / 2;
            int slotCenterY = rectSlot.y + rectSlot.h / 2;
            
            SDL_Rect fontRect = {
                .x = slotCenterX - fontW / 2,
                .y = slotCenterY - fontH / 2,
                .w = fontW, 
                .h = fontH
            };
            SDL_RenderCopy(mRenderer, fontTex, NULL, &fontRect);
        }
    }

}

void DrumsView::release()
{
    for (auto& text: mSlotsTextures){
        if (text.second){
            SDL_DestroyTexture(text.second);
        }
    }
    mSlotsTextures.clear();
}