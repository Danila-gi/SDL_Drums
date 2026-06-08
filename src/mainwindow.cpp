#include "mainwindow.h"
#include "fontscontainer.h"

#include <iostream>

MainWindow::MainWindow(int screenWidth, int screenHeight, int fps)
    : mScreenWidth{screenWidth}
    , mScreenHeight{screenHeight}
    , mTargetFPS{fps}
{
    mRealFPS = mTargetFPS;
    mRotationButton = std::make_unique<RotationButton>(screenWidth * 0.4, screenHeight * 0.8, screenWidth * 0.16, screenHeight * 0.12, 1500);
    mDrumsView = std::make_unique<DrumsView>(screenWidth * 0.08, screenWidth * 0.31, 30);
    mDrumsModel = std::make_shared<DrumsModel>(5, 3);

    mDrumsView->setModel(mDrumsModel);
}

bool MainWindow::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL couldn't initialize!" << std::endl;
        return false;
    }

    mWindow = SDL_CreateWindow("SDL Drums", 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        mScreenWidth, mScreenHeight, SDL_WINDOW_SHOWN
    );
    if (!mWindow){
        std::cout << "Window couldn't be created!" << std::endl;
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!mRenderer){
        std::cout << "Renderer couldn't be created!" << std::endl;
        return false;
    }

    mDrumsView->setRenderer(mRenderer);
    mDrumsView->initTextures();

    mRotationButton->setRenderer(mRenderer);
    mRotationButton->initTextures();

    return true;
}

void MainWindow::run()
{
    SDL_Event event;
    bool quit = false;
    auto lastTime = SDL_GetTicks();
    int frameCount = 0;
    while (!quit){
        auto timeFrameStart = SDL_GetTicks();
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                quit = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN){
                if (event.button.button == SDL_BUTTON_LEFT){
                    int mouseX = event.button.x;
                    int mouseY = event.button.y;
                    if (mRotationButton->getState() != PRESSED && mRotationButton->isCoordsInsideRect(mouseX, mouseY)){
                        mRotationButton->setState(PRESSED);
                        if (mDrumsModel){
                            mDrumsModel->startRotation(5000, 500, 50, 700);
                        }
                    }
                }
            }
        }
        if (mDrumsModel && !mDrumsModel->isStartRotate()){
            mRotationButton->setState(NORMAL);
        }
        updatePainting();
        frameCount++;
        auto currentTime = SDL_GetTicks();
        int frameRealTime = currentTime - timeFrameStart;
        if (currentTime - lastTime >= 1000) {
            mRealFPS = frameCount;
            frameCount = 0;
            lastTime = currentTime;
        }
        if (mTargetFPS <= 0){
            continue;
        }
        int currentDelay = 1000 / mTargetFPS - frameRealTime;
        if (currentDelay > 0) {
            SDL_Delay(currentDelay);
        }
    }
}

void MainWindow::updatePainting(){
    if (!mRenderer){
        return;
    }
    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
    SDL_RenderClear(mRenderer);

    if (mRotationButton && mRealFPS > 0){
        mRotationButton->updateButton(1000 / mRealFPS);
        mRotationButton->paint();
    }

    if (mDrumsModel && mDrumsView && mRealFPS > 0){
        mDrumsModel->updateState(1000 / mRealFPS);
        mDrumsView->paint();
    }

    const auto fontsContainer = FontsContainer::instance();
    if (fontsContainer){
        if (const auto font = fontsContainer->getFontById("info_text")){
            const auto fpsInfoText = "Current FPS: " + std::to_string(mRealFPS);
            const auto fontFpsSurface = TTF_RenderText_Solid(font, fpsInfoText.c_str(), {0, 0, 0, 255});
            const auto fontFpsTex = SDL_CreateTextureFromSurface(mRenderer, fontFpsSurface);
            int fontW, fontH;
            SDL_QueryTexture(fontFpsTex, NULL, NULL, &fontW, &fontH);
            
            SDL_Rect fontRect = {
                .x = static_cast<int>(mScreenWidth * 0.1),
                .y = static_cast<int>(mScreenHeight * 0.8),
                .w = fontW, 
                .h = fontH
            };
            SDL_FreeSurface(fontFpsSurface);
            SDL_RenderCopy(mRenderer, fontFpsTex, NULL, &fontRect);
            SDL_DestroyTexture(fontFpsTex);
        }
    }

    SDL_RenderPresent(mRenderer);
}

void MainWindow::close()
{
    if (mRotationButton){
        mRotationButton->release();
    }
    if (mDrumsView){
        mDrumsView->release();
    }
    if (mRenderer){
        SDL_DestroyRenderer(mRenderer);
        mRenderer = nullptr;
    }
    if (mWindow){
        SDL_DestroyWindow(mWindow);
        mWindow = nullptr;
    }
    SDL_Quit();
}