#ifndef TEXT_GUI_H
#define TEXT_GUI_H

#include <algorithm>
#include <chrono>
#include "olcPixelGameEngine.h"

class olcTextGUI
{
public:
    olcTextGUI(olc::vi2d box_offset, olc::vi2d box_size, int text_scale, 
               olc::Pixel text_color, int id);
    
    // Frame Function
    void OnTextUpdate(olc::PixelGameEngine& pge, olc::vi2d MousePos, float fElapsedTime);
    bool bBoxActive  = false;
    bool bCapsLockOn = false; // !Doesn't get initial CAPS state on Constructor!
    void SetOffset(olc::vi2d offset) { vBoxOffset = offset; }
    std::string GetText() { return sText; }
    olc::vi2d GetOffset() { return vBoxOffset; }
    olc::vi2d GetSize()   { return vBoxSize; }
    int GetID()           { return nTextID; }

private:
    std::string sText;
    olc::vi2d vBoxOffset;
    olc::vi2d vBoxInnerPad;
    olc::vi2d vBoxSize;
    olc::vi2d vCharSize;
    olc::Pixel pTextColor;
    olc::Sprite* sprMarkers = nullptr;
    size_t nCursorPos = 0;
    size_t nCursorDisplayMin;
    size_t nCursorDisplayMax;
    int nTextScale;
    int nTextID;

    // Cursor blinking
    double tHoldAmount = 0.25;
    double tTimeHolder = 0.0;
    bool bHold = false;

    // Drawing and Input functions
    bool HoverOverBox(olc::vi2d cMousePos);
    void HandleInputKey(olc::PixelGameEngine& pge);
    void CursorOnClick(olc::vi2d cMousePos);
    void DrawSelf(olc::PixelGameEngine& pge);

    // Cursor handling
    void OnDelete();
    void OnBackspace();
    void CursorOnUp();
    void CursorOnDown();
    void CursorOnLeft();
    void CursorOnRight();
    void CursorSprintLeft();
    void CursorSprintRight();
    olc::vi2d GetCursorPos();
};

#endif