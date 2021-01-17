#ifndef BUTTON_GUI_H
#define BUTTON_GUI_H

#include "olcPixelGameEngine.h"

class olcButtonGUI
{
public:
    olcButtonGUI(olc::vi2d offset, std::string text, int text_scale, 
                 olc::Pixel text_color, int id);
    void OnButtonUpdate(olc::PixelGameEngine& pge, olc::vi2d MousePos, int& command_id);
    void SetOffset(olc::vi2d offset) { vButtonOffset = offset; }
    olc::vi2d GetOffset() { return vButtonOffset; }
    int GetID() { return nButtonID; }

private:
    olc::Sprite* sprFrame = nullptr;
    olc::Pixel pButtonTextColor;
    olc::vi2d vButtonOffset;
    olc::vi2d vButtonSize;
    std::string sButtonText;
    bool bButtonActive = false;
    int nButtonTextScale;
    int nButtonID;
    int nPatchScaled;
    int nPatch;

    void HandleClick(int& command_id);
    void DrawSelf(olc::PixelGameEngine& pge, olc::vi2d MousePos);
    bool HoverOverButton(olc::vi2d MousePos);
};

#endif