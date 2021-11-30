#!/bin/bash
# compiles game

g++ -std=c++14 FrameGraphics.cpp GameOfLifeApp.cpp GraphicsGameClasses.cpp SimpleArrayGame.cpp `/Users/Sarah/wxWidgets-3.1.5/build-release/wx-config --cxxflags --libs` -o bin/GameOfLife

