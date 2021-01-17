#include "ButtonGUI.h"

olcButtonGUI::olcButtonGUI(olc::vi2d offset, std::string text, int text_scale, olc::Pixel text_color, int id)
{
    nPatch        = 8; // 8-bit sprite cell
    nPatchScaled  = nPatch * text_scale; 
    nButtonID     = id;
    sButtonText   = text;
    bButtonActive = true;
    vButtonOffset = offset;
    vButtonSize.x = text_scale * text.length() * 8 + 2 * nPatchScaled; // 8-bit font
    vButtonSize.y = text_scale * 8 + 2 * nPatchScaled;                 // 8-bit font
    pButtonTextColor = text_color;
    nButtonTextScale = text_scale;
    sprFrame = new olc::Sprite("./sprites/RetroMenuSprite.png");
}

bool olcButtonGUI::HoverOverButton(olc::vi2d MousePos)
{
    return (MousePos.x > vButtonOffset.x && MousePos.x < (vButtonOffset.x + vButtonSize.x) &&
            MousePos.y > vButtonOffset.y && MousePos.y < (vButtonOffset.y + vButtonSize.y)) ? 
            true : false;
}

void olcButtonGUI::DrawSelf(olc::PixelGameEngine& pge, olc::vi2d MousePos)
{
    // Draw Frame
    olc::Pixel::Mode currentPixelMode = pge.GetPixelMode();
    pge.SetPixelMode(olc::Pixel::ALPHA);

    // Draw Panel & Border
    olc::vi2d vPatchPos = {0, 0};
    olc::vi2d vSizeInPatches = {2 + (int)sButtonText.length(), 1 + 2}; // single line (2 border patches)
    for (vPatchPos.x = 0; vPatchPos.x < vSizeInPatches.x; vPatchPos.x += 1)
    {
        for (vPatchPos.y = 0; vPatchPos.y < vSizeInPatches.y; vPatchPos.y += 1)
        {
            // Determine position in screen space
            olc::vi2d vScreenLocation = vPatchPos * nPatchScaled + vButtonOffset;

            // Calculate which patch is needed
            olc::vi2d vSourcePatch = {0, 0};
            if (vPatchPos.x > 0) { vSourcePatch.x = 1; }
            if (vPatchPos.y > 0) { vSourcePatch.y = 1; }
            if (vPatchPos.x == (vSizeInPatches.x - 1)) { vSourcePatch.x = 2; }
            if (vPatchPos.y == (vSizeInPatches.y - 1)) { vSourcePatch.y = 2; }

            // Draw Actual Patch
            pge.DrawPartialSprite(vScreenLocation, sprFrame, nPatch * vSourcePatch, {nPatch, nPatch}, nButtonTextScale);
        }
    }

    // Actual screen location in pixels
    vPatchPos = {1, 1};
    olc::vi2d vTextScreenLocation = vPatchPos * nPatchScaled + vButtonOffset;
    bool highlight = false;
    if (HoverOverButton(MousePos) && bButtonActive) { highlight = true; }
    pge.DrawString(vTextScreenLocation, sButtonText, bButtonActive ? (highlight ? olc::YELLOW : pButtonTextColor) : olc::DARK_GREY, nButtonTextScale);
    
    pge.SetPixelMode(currentPixelMode);
}

void olcButtonGUI::HandleClick(int& command_id)
{
    command_id = nButtonID;
}

void olcButtonGUI::OnButtonUpdate(olc::PixelGameEngine& pge, olc::vi2d MousePos, int& command_id)
{
    // Handle mouse command
    if (HoverOverButton(MousePos) && pge.GetMouse(0).bPressed)
    {
        HandleClick(command_id);
    }

    // Draw mighty button
    DrawSelf(pge, MousePos);
}