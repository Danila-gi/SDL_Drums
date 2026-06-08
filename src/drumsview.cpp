#include "drumsview.h"

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

void DrumsView::paint(SDL_Renderer* renderer)
{
    const auto fontsContainer = FontsContainer::instance();
    if (!fontsContainer){
        return;
    }
    const auto font = FontsContainer::instance()->getFontById("info_text");
    if (!mDrumsModel || !font || !renderer){
        return;
    }
    for (int i = 0; i < mDrumsModel->getDrumsSize().first; i++){
        for (int j = 0; j < mDrumsModel->getDrumsSize().second; j++){
            const auto slotFillColor = mDrumsModel->getFillColorFromSlot(i, j);
            if (slotFillColor.has_value()){
                SDL_SetRenderDrawColor(renderer, 
                    slotFillColor->r, slotFillColor->g, 
                    slotFillColor->b, slotFillColor->a
                );
            }
            else{
                SDL_SetRenderDrawColor(renderer, 
                    255, 255, 
                    255, 255
                );
            }
            SDL_Rect rectSlot = {
                .x = mDrumsCoordX + i * mSlotSize,
                .y = mDrumsCoordY + j * mSlotSize,
                .w = mSlotSize, 
                .h = mSlotSize
            };
            SDL_RenderFillRect(renderer, &rectSlot);
            SDL_SetRenderDrawColor(renderer, 
                mSlotRectStyle.r, mSlotRectStyle.g, 
                mSlotRectStyle.b, mSlotRectStyle.a
            );
            SDL_RenderDrawRect(renderer, &rectSlot);
            const auto slotText = mDrumsModel->getTextFromSlot(i, j);
            const char* slotTextChar;
            if (slotText.has_value()){
                slotTextChar = slotText->c_str();
            }
            else{
                slotTextChar = "X--";
            }
            const auto fontSurface = TTF_RenderText_Solid(font, slotTextChar, mSlotTextStyle);
            const auto fontTex = SDL_CreateTextureFromSurface(renderer, fontSurface);
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
            SDL_RenderCopy(renderer, fontTex, NULL, &fontRect);
        }
    }

}