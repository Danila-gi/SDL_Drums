#include "rotationbutton.h"

#include "fontscontainer.h"

RotationButton::RotationButton(int x, int y, int w, int h, int timeChangeNormalStyle): mTimeChangeNormalStyle(timeChangeNormalStyle)
{
    mRect = {.x = x, .y = y, .w = w, .h = h};

    loadStyles();
    setState(NORMAL);
}

void RotationButton::loadStyles()
{
    mPressedStyle = {.r = 100, .g = 100, .b = 100, .a = 200};

    mNormalStyles.push_back({.r = 50, .g = 145, .b = 50, .a = 255});
    mNormalStyles.push_back({.r = 145, .g = 50, .b = 50, .a = 255});
    mNormalStyles.push_back({.r = 50, .g = 50, .b = 145, .a = 255});

    const auto fontsContainer = FontsContainer::instance();
    if (fontsContainer){
        if (const auto font = fontsContainer->getFontById("button")){
            mFontSurface = TTF_RenderText_Solid(font, "Start", {0, 0, 0, 255});
        }
    }
}

void RotationButton::setState(ButtonState state)
{
    mButtonState = state;

    switch (mButtonState)
    {
    case NORMAL:{
        mCurrentNormalStyleIndex = 0;
        mCurrentTimeNormalPaintCycle = 0;
        updateToNormalState();
        break;
    }
    case PRESSED:{
        updateToPressedState();
        break;
    }
    default:
        break;
    }
}

void RotationButton::setRenderer(SDL_Renderer* renderer)
{
    mRenderer = renderer;
}

void RotationButton::initTextures()
{
    mFontTexture = SDL_CreateTextureFromSurface(mRenderer, mFontSurface);
}

const SDL_Rect* RotationButton::getRect() const
{
    return &mRect;
}

ButtonState RotationButton::getState() const
{
    return mButtonState;
}

bool RotationButton::isCoordsInsideRect(int x, int y) const
{
    return x >= getRect()->x && x <= getRect()->x + getRect()->w && y >= getRect()->y && y <= getRect()->y + getRect()->h;
}

void RotationButton::updateButton(int delay)
{
    if (mButtonState == NORMAL){
        mCurrentTimeNormalPaintCycle += delay;
        if (mCurrentTimeNormalPaintCycle > mTimeChangeNormalStyle){
            if (mCurrentNormalStyleIndex >= mNormalStyles.size() - 1){
                mCurrentNormalStyleIndex = 0;
            }
            else{
                mCurrentNormalStyleIndex++;
            }
            mCurrentTimeNormalPaintCycle = 0;
            updateToNormalState();
        }
    }
}

void RotationButton::paint()
{
    if (!mRenderer || !mFontSurface){
        return;
    }
    SDL_SetRenderDrawColor(mRenderer, 
        mCurrentStyle.r, mCurrentStyle.g, 
        mCurrentStyle.b, mCurrentStyle.a
    );
    SDL_RenderFillRect(mRenderer, getRect());

    int fontW, fontH;
    SDL_QueryTexture(mFontTexture, NULL, NULL, &fontW, &fontH);
    int buttonCenterX = getRect()->x + getRect()->w / 2;
    int buttonCenterY = getRect()->y + getRect()->h / 2;
    
    SDL_Rect fontRect = {
        .x = buttonCenterX - fontW / 2,
        .y = buttonCenterY - fontH / 2,
        .w = fontW, 
        .h = fontH
    };
    SDL_RenderCopy(mRenderer, mFontTexture, NULL, &fontRect);
}

void RotationButton::updateToPressedState()
{
    mCurrentStyle = mPressedStyle;
}

void RotationButton::updateToNormalState()
{
    if (mCurrentNormalStyleIndex < 0 || mCurrentNormalStyleIndex >= mNormalStyles.size()){
        return;
    }
    mCurrentStyle = mNormalStyles[mCurrentNormalStyleIndex];
}

void RotationButton::release()
{
    if (mFontSurface) {
        SDL_FreeSurface(mFontSurface);
        mFontSurface = nullptr;
    }
    if (mFontTexture){
        SDL_DestroyTexture(mFontTexture);
        mFontTexture = nullptr;
    }
}