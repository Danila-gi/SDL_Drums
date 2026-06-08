#include "fontscontainer.h"

#include <filesystem>
#include <iostream>

std::unique_ptr<FontsContainer> FontsContainer::mInstancePtr = nullptr;

bool FontsContainer::mIsInit = false;

void FontsContainer::addFont(const std::string& id, const std::string& filePath, int ptsize)
{
    mMapFonts.insert({id, TTF_OpenFont(filePath.c_str(), ptsize)});
}

FontsContainer::~FontsContainer()
{
    for (auto& pair : mMapFonts) {
        if (pair.second) {
            TTF_CloseFont(pair.second);
            pair.second = nullptr;
        }
    }
    mMapFonts.clear();
    
    if (mIsInit) {
        TTF_Quit();
    }
}

FontsContainer* FontsContainer::instance(){
    if (mInstancePtr == nullptr) {
        if (TTF_Init() < 0){
            std::cout << "Fonts couldn't be included!" << std::endl;
            return nullptr;
        }
        mIsInit = true;
        mInstancePtr = std::unique_ptr<FontsContainer>(new FontsContainer());
    }

    return mInstancePtr.get();
}

TTF_Font* FontsContainer::getFontById(const std::string& id) const noexcept
{
    auto it = mMapFonts.find(id);
    if (it != mMapFonts.end()) {
        return it->second;
    }
    return nullptr;
}
