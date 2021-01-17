#ifndef FUNC_PLOTER_H
#define FUNC_PLOTER_H

#include <algorithm>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <fstream>
#include <string>

#include "TextGUI.h"
#include "ButtonGUI.h"
#include "command_id.h"
#include "exprtk.hpp"

class cFuncPloter : public olc::PixelGameEngine
{
public:
    cFuncPloter() { sAppName = "Function Ploter GUI"; }

private:
    // GUI Elements
    olc::Sprite *sprPlot = nullptr;
    uint8_t nTextScale = 2;
    uint8_t nPatchSize;
    olc::vi2d vPaddingFields;
    std::vector<olcTextGUI> vTextBoxes;
    std::vector<olcButtonGUI> vButtons;
    std::vector<std::string> vTextSelected;
    bool bCreateBox = false;

    // GUI handling
    void OnGUIUpdate(olc::vi2d vMousePos, float fElapsedTime);
    void InsertField(int field_id);
    int nCommand = 0;

    // Handle parsing
    void RunParser();
    void WriteSetupFile(std::vector<std::pair<std::string, double>> constants, 
                        std::vector<std::string> expressions, std::string variable, 
                        double x_min, double x_max, double y_min, double y_max, int points);

    // String handling
    void remove_chars(std::string& text, const std::string& chars);
    bool in_text(const std::string& text, const std::string& pattern);
    bool check_setup(const std::string& text, const std::string& setup_id);
    std::vector<std::string> split_string(const std::string& text, const std::string& delim = " ");

protected:  
    bool OnUserCreate() override;
    bool OnUserUpdate(float fElapsedTime) override;
};

#endif