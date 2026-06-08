#include "mainwindow.h"
#include <iostream>
#include <memory>

#include "fontscontainer.h"

int main(int argc, char* argv[]){
    const auto fontsContainer = FontsContainer::instance();
    fontsContainer->addFont("button", "fonts/main_font.ttf", 42);
    fontsContainer->addFont("info_text", "fonts/main_font.ttf", 20);

    MainWindow mainWindow(640, 480, 60);
    if (mainWindow.init()){
        mainWindow.run();
        mainWindow.close();
    }

    return 0;
}