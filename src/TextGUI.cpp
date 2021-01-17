#include "TextGUI.h"

olcTextGUI::olcTextGUI(olc::vi2d box_offset, olc::vi2d box_size, int text_scale, olc::Pixel text_color, int id)
{
    nTextID    = id;
    nTextScale = text_scale;
    pTextColor = text_color;
    vBoxInnerPad = olc::vi2d{5, 5};
    vBoxOffset = box_offset;
    vBoxSize   = box_size + 2 * vBoxInnerPad;
    vCharSize  = text_scale * olc::vi2d{8, 8};
    sprMarkers = new olc::Sprite("./sprites/RetroMenuSprite.png");
    bBoxActive = true;
    nCursorPos = 0;
    nCursorDisplayMin = 0;
    nCursorDisplayMax = (vBoxSize.x - 2 * vBoxInnerPad.x) / (nTextScale * 8);
}

void olcTextGUI::HandleInputKey(olc::PixelGameEngine& pge)
{
    // Track text size for cursor location
    size_t nPreviousTextSize = sText.length();

    // Check for case activation
    bool upper_case_alphabet = (bCapsLockOn ? 
                               (pge.GetKey(olc::Key::SHIFT).bHeld ? false : true) : 
                               (pge.GetKey(olc::Key::SHIFT).bHeld ? true : false));

    /** Alphabet **/
         if (pge.GetKey(olc::Key::A).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "A" : "a"); }
    else if (pge.GetKey(olc::Key::B).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "B" : "b"); }
    else if (pge.GetKey(olc::Key::C).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "C" : "c"); }
    else if (pge.GetKey(olc::Key::D).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "D" : "d"); }
    else if (pge.GetKey(olc::Key::E).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "E" : "e"); }
    else if (pge.GetKey(olc::Key::F).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "F" : "f"); }
    else if (pge.GetKey(olc::Key::G).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "G" : "g"); }
    else if (pge.GetKey(olc::Key::H).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "H" : "h"); }
    else if (pge.GetKey(olc::Key::I).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "I" : "i"); }
    else if (pge.GetKey(olc::Key::J).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "J" : "j"); }
    else if (pge.GetKey(olc::Key::K).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "K" : "k"); }
    else if (pge.GetKey(olc::Key::L).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "L" : "l"); }
    else if (pge.GetKey(olc::Key::M).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "M" : "m"); }
    else if (pge.GetKey(olc::Key::N).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "N" : "n"); }
    else if (pge.GetKey(olc::Key::O).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "O" : "o"); }
    else if (pge.GetKey(olc::Key::P).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "P" : "p"); }
    else if (pge.GetKey(olc::Key::Q).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "Q" : "q"); }
    else if (pge.GetKey(olc::Key::R).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "R" : "r"); }
    else if (pge.GetKey(olc::Key::S).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "S" : "s"); }
    else if (pge.GetKey(olc::Key::T).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "T" : "t"); }
    else if (pge.GetKey(olc::Key::U).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "U" : "u"); }
    else if (pge.GetKey(olc::Key::V).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "V" : "v"); }
    else if (pge.GetKey(olc::Key::Y).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "Y" : "y"); }
    else if (pge.GetKey(olc::Key::X).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "X" : "x"); }
    else if (pge.GetKey(olc::Key::W).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "W" : "w"); }
    else if (pge.GetKey(olc::Key::Z).bPressed)     { sText.insert(nCursorPos, upper_case_alphabet ? "Z" : "z"); }
    /** Numerals and signs (central keyboard) **/
    else if (pge.GetKey(olc::OEM_1).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? ":"  : ";"); } // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_2).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "?"  : "/"); } // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_3).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? ""   : "");  } // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_4).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "{"  : "["); } // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_5).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "|"  : "\\");} // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_6).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "}"  : "]"); } // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_7).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "\"" : "\'");} // ABNT2 / Ubuntu 18
    else if (pge.GetKey(olc::OEM_8).bPressed)      { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "#"  : "");  } // ABNT2 / Ubuntu 18 (SHIFT + K3)
    else if (pge.GetKey(olc::Key::K1).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "!"  : "1"); }
    else if (pge.GetKey(olc::Key::K2).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "@"  : "2"); }
    else if (pge.GetKey(olc::Key::K3).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "#"  : "3"); }
    else if (pge.GetKey(olc::Key::K4).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "$"  : "4"); }
    else if (pge.GetKey(olc::Key::K5).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "%"  : "5"); }
    else if (pge.GetKey(olc::Key::K6).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "^"  : "6"); } // US standard
    else if (pge.GetKey(olc::Key::K7).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "&"  : "7"); }
    else if (pge.GetKey(olc::Key::K8).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "*"  : "8"); }
    else if (pge.GetKey(olc::Key::K9).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "("  : "9"); }
    else if (pge.GetKey(olc::Key::K0).bPressed)    { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? ")"  : "0"); } 
    else if (pge.GetKey(olc::Key::MINUS).bPressed) { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "_" : "-");  }
    else if (pge.GetKey(olc::Key::EQUALS).bPressed){ sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "+" : "=");  }
    else if (pge.GetKey(olc::Key::COMMA).bPressed) { sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? "<" : ",");  }
    else if (pge.GetKey(olc::Key::PERIOD).bPressed){ sText.insert(nCursorPos, pge.GetKey(olc::Key::SHIFT).bHeld ? ">" : ".");  }
    /** Numpad and extra commands **/
    else if (pge.GetKey(olc::Key::NP1).bPressed)        { sText.insert(nCursorPos, "1");  }
    else if (pge.GetKey(olc::Key::NP2).bPressed)        { sText.insert(nCursorPos, "2");  }
    else if (pge.GetKey(olc::Key::NP3).bPressed)        { sText.insert(nCursorPos, "3");  }
    else if (pge.GetKey(olc::Key::NP4).bPressed)        { sText.insert(nCursorPos, "4");  }
    else if (pge.GetKey(olc::Key::NP5).bPressed)        { sText.insert(nCursorPos, "5");  }
    else if (pge.GetKey(olc::Key::NP6).bPressed)        { sText.insert(nCursorPos, "6");  }
    else if (pge.GetKey(olc::Key::NP7).bPressed)        { sText.insert(nCursorPos, "7");  }
    else if (pge.GetKey(olc::Key::NP8).bPressed)        { sText.insert(nCursorPos, "8");  }
    else if (pge.GetKey(olc::Key::NP9).bPressed)        { sText.insert(nCursorPos, "9");  }
    else if (pge.GetKey(olc::Key::NP0).bPressed)        { sText.insert(nCursorPos, "0");  }
    else if (pge.GetKey(olc::Key::NP_DIV).bPressed)     { sText.insert(nCursorPos, "/");  }
    else if (pge.GetKey(olc::Key::NP_MUL).bPressed)     { sText.insert(nCursorPos, "*");  }
    else if (pge.GetKey(olc::Key::NP_ADD).bPressed)     { sText.insert(nCursorPos, "+");  }
    else if (pge.GetKey(olc::Key::NP_SUB).bPressed)     { sText.insert(nCursorPos, "-");  }
    else if (pge.GetKey(olc::Key::NP_DECIMAL).bPressed) { sText.insert(nCursorPos, ".");  }
    else if (pge.GetKey(olc::Key::SPACE).bPressed)      { sText.insert(nCursorPos, " ");  }
    // else if (pge.GetKey(olc::Key::TAB).bPressed)        { sText.insert(nCursorPos, "\t"); }
    else if (pge.GetKey(olc::Key::DEL).bPressed)        { OnDelete();                     }
    else if (pge.GetKey(olc::Key::BACK).bPressed)       { OnBackspace();                  }
    /** Move cursor **/
    else if ( pge.GetKey(olc::Key::UP).bPressed)                                        { CursorOnUp();    }
    else if ( pge.GetKey(olc::Key::PGUP).bPressed)                                      { CursorOnUp();    }
    else if ( pge.GetKey(olc::Key::DOWN).bPressed)                                      { CursorOnDown();  }
    else if ( pge.GetKey(olc::Key::PGDN).bPressed)                                      { CursorOnDown();  }
    else if (!pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::LEFT).bPressed)  { CursorOnLeft();  }
    else if (!pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::RIGHT).bPressed) { CursorOnRight(); }
    else if ( pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::LEFT).bPressed)  { CursorSprintLeft(); }
    else if ( pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::RIGHT).bPressed) { CursorSprintRight(); }
    else if (!pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::END).bPressed)   { nCursorPos = std::min(nCursorDisplayMax, sText.length()); }
    else if (!pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::HOME).bPressed)  { nCursorPos = std::min(nCursorDisplayMin, sText.length()); }
    else if ( pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::END).bPressed)   
    { 
        nCursorPos = sText.length();
        int DisplaySize = nCursorDisplayMax - nCursorDisplayMin;
        nCursorDisplayMin = nCursorPos - DisplaySize;
        nCursorDisplayMax = nCursorPos;
    }
    else if ( pge.GetKey(olc::Key::CTRL).bHeld && pge.GetKey(olc::Key::HOME).bPressed)  
    { 
        nCursorPos = 0;
        int DisplaySize = nCursorDisplayMax - nCursorDisplayMin;
        nCursorDisplayMin = nCursorPos;
        nCursorDisplayMax = nCursorPos + DisplaySize;
    }

    // Update cursor if char is modified
    if (nPreviousTextSize != sText.length())
    {
        if (nCursorPos == nPreviousTextSize)
        {
            nCursorPos = sText.length();
        }
        else if (nPreviousTextSize < sText.length())
        {
           nCursorPos += 1;
        }

        if (nCursorPos < nCursorDisplayMin)
        {
            nCursorDisplayMin -= 1;
            nCursorDisplayMax -= 1;
        }
        else if (nCursorPos > nCursorDisplayMax)
        {
            nCursorDisplayMin += 1;
            nCursorDisplayMax += 1;
        }
    }
}

void olcTextGUI::OnBackspace()
{
    if (!sText.empty()) 
    { 
        if (nCursorPos > 0 && nCursorPos <= sText.length())
        {
            sText.erase(nCursorPos - 1, 1);
            nCursorPos -= 1;
            if (nCursorPos < 0) { nCursorPos = 0; }
        }
    }
}

void olcTextGUI::OnDelete()
{
    if (!sText.empty()) 
    { 
        if (nCursorPos < sText.length())
        {
            sText = sText.erase(nCursorPos, 1);
        }
    }
}

void olcTextGUI::CursorOnUp()
{
    size_t PrevBreak = sText.substr(0, nCursorPos).rfind('\n', nCursorPos);
    if (PrevBreak < nCursorPos)
    {
        nCursorPos = PrevBreak;
    }
}

void olcTextGUI::CursorOnDown()
{
    size_t NextBreak = sText.find('\n', nCursorPos);
    if (NextBreak >= nCursorPos && NextBreak < sText.length())
    {
        size_t NextNextBreak = sText.find('\n', NextBreak + 1);
        if (NextNextBreak < sText.length())
        {
            nCursorPos = NextNextBreak;
        }
        else
        {
            nCursorPos = sText.length();
        }
    }
}

void olcTextGUI::CursorOnLeft()
{
    nCursorPos -= (nCursorPos == 0) ? 0 : 1;

    if (nCursorPos < nCursorDisplayMin)
    {
        nCursorDisplayMin -= 1;
        nCursorDisplayMax -= 1;
    }
}

void olcTextGUI::CursorOnRight()
{
    nCursorPos += 1;
    if (nCursorPos > sText.size())
    {
        nCursorPos = sText.size();
    }
    if (nCursorPos > nCursorDisplayMax)
    {
        nCursorDisplayMin += 1;
        nCursorDisplayMax += 1;
    }
}

void olcTextGUI::CursorSprintLeft()
{
    if (nCursorPos == 0) { return; }

    std::vector<size_t> MarkerPos;
    MarkerPos.push_back((sText.rfind('-',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('-',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(',',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(',',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('.',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('.',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(';',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(';',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(':',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(':',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('<',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('<',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('>',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('>',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('(',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('(',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(')',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(')',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('[',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('[',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(']',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(']',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('{',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('{',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind('}',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind('}',  nCursorPos-1) : 0);
    MarkerPos.push_back((sText.rfind(' ',  nCursorPos-1) <= nCursorPos-1) ? sText.rfind(' ',  nCursorPos-1) : 0); 
    MarkerPos.push_back((sText.rfind('\n', nCursorPos-1) <= nCursorPos-1) ? sText.rfind('\n', nCursorPos-1) : 0);

    nCursorPos = *std::max_element(std::begin(MarkerPos), std::end(MarkerPos));

    if (nCursorPos < nCursorDisplayMin)
    {
        int DisplaySize = nCursorDisplayMax - nCursorDisplayMin;
        nCursorDisplayMin = nCursorPos;
        nCursorDisplayMax = nCursorPos + DisplaySize;
    }
}

void olcTextGUI::CursorSprintRight()
{
    if (nCursorPos == sText.length()) { return; }

    std::vector<size_t> MarkerPos;
    MarkerPos.push_back(sText.find('-', nCursorPos));
    MarkerPos.push_back(sText.find(',', nCursorPos));
    MarkerPos.push_back(sText.find('.', nCursorPos));
    MarkerPos.push_back(sText.find(';', nCursorPos));
    MarkerPos.push_back(sText.find(':', nCursorPos));
    MarkerPos.push_back(sText.find('<', nCursorPos));
    MarkerPos.push_back(sText.find('>', nCursorPos));
    MarkerPos.push_back(sText.find('(', nCursorPos));
    MarkerPos.push_back(sText.find(')', nCursorPos));
    MarkerPos.push_back(sText.find('[', nCursorPos));
    MarkerPos.push_back(sText.find(']', nCursorPos));
    MarkerPos.push_back(sText.find('{', nCursorPos));
    MarkerPos.push_back(sText.find('}', nCursorPos));
    MarkerPos.push_back(sText.find(' ', nCursorPos)); 
    MarkerPos.push_back(sText.find('\n', nCursorPos));

    nCursorPos = std::max(nCursorPos + 1, *std::min_element(std::begin(MarkerPos), std::end(MarkerPos)));
    if (nCursorPos >= sText.length()) { nCursorPos = sText.length(); }

    if (nCursorPos > nCursorDisplayMax)
    {
        int DisplaySize = nCursorDisplayMax - nCursorDisplayMin;
        nCursorDisplayMin = nCursorPos - DisplaySize;
        nCursorDisplayMax = nCursorPos;
    }
}

void olcTextGUI::CursorOnClick(olc::vi2d cMousePos)
{
    olc::vi2d PosInBox = cMousePos - vBoxOffset - vBoxInnerPad;
    int CoordX = (int)(0.4 + (float)PosInBox.x / (float)vCharSize.x);
    int CoordY = PosInBox.y / vCharSize.y;

    int line = 0;
    size_t counter = 0;
    size_t line_length = 0;
    while (line <= CoordY)
    {   
        if (line == CoordY)
        {
            line_length = sText.find('\n', counter) - counter;
            counter += std::min((size_t)CoordX, line_length);
            break;
        }
        else
        {
            line_length = sText.find('\n', counter) - counter;
            counter += line_length + 1;
            line += 1; 
        }
    }

    nCursorPos = nCursorDisplayMin + std::clamp(counter, (size_t)0, sText.length());
}

bool olcTextGUI::HoverOverBox(olc::vi2d cMousePos)
{
    return (cMousePos.x > vBoxOffset.x && cMousePos.x < (vBoxOffset.x + vBoxSize.x) &&
            cMousePos.y > vBoxOffset.y && cMousePos.y < (vBoxOffset.y + vBoxSize.y)) ? 
            true : false;
}

olc::vi2d olcTextGUI::GetCursorPos()
{
    olc::vi2d Pos;
    for (int i = 0; i < (int)nCursorPos; i += 1)
    {
        char c = sText[i];
        if (c == '\n')
        { 
            Pos.x = 0;
            Pos.y += vCharSize.y;
        }
        else
        {
            Pos.x += vCharSize.x;
        }
    }
    
    Pos.x = std::min((size_t)Pos.x - vCharSize.x * nCursorDisplayMin, vCharSize.x * (nCursorDisplayMax - nCursorDisplayMin));
    
    return Pos;
}

void olcTextGUI::DrawSelf(olc::PixelGameEngine& pge)
{
    // Draw Box
    pge.FillRect(vBoxOffset, vBoxSize, olc::BLUE);
    pge.DrawRect(vBoxOffset, vBoxSize, bBoxActive ? pTextColor : olc::BLUE);
    
    // Draw Text
    pge.DrawString(vBoxOffset + vBoxInnerPad, sText.substr(nCursorDisplayMin, std::min(nCursorDisplayMax - nCursorDisplayMin, sText.length())), 
                   pTextColor, nTextScale);
    
    // Draw Cursor
    if (bBoxActive && !bHold)
    {
        olc::vi2d CursorPos = vBoxOffset + vBoxInnerPad + GetCursorPos();
        pge.FillRect(CursorPos, {3, vCharSize.y}, olc::RED);
    }

    // Draw display cursor indicators
    olc::Pixel::Mode CurrentPixelMode = pge.GetPixelMode();
    pge.SetPixelMode(olc::Pixel::ALPHA);
    int SpriteScale = 2;
    if (nCursorDisplayMin > 0)
    {
        olc::vi2d MarkerPos = vBoxOffset + olc::vi2d{-8 * SpriteScale - 2, (int)(0.8 * vCharSize.y)};
        pge.DrawPartialSprite(MarkerPos, sprMarkers, 8 * olc::vi2d{3, 1}, {8, 8}, SpriteScale, 1);
    }
    if (nCursorDisplayMax < sText.length())
    {
        olc::vi2d MarkerPos = vBoxOffset + olc::vi2d{vBoxSize.x + 2, (int)(0.8 * vCharSize.y)};
        pge.DrawPartialSprite(MarkerPos, sprMarkers, 8 * olc::vi2d{3, 1}, {8, 8}, SpriteScale, 0);
    }
    pge.SetPixelMode(CurrentPixelMode);

    // Future Features:
    //      -> text box can be made from the same frame as the RetroStyleMenu
    //      -> the hand cursor can indicate the activated box
}

void olcTextGUI::OnTextUpdate(olc::PixelGameEngine& pge, olc::vi2d MousePos, float fElapsedTime)
{
    // Handle click selection
    if (HoverOverBox(MousePos) && pge.GetMouse(0).bPressed)
    {
        bBoxActive = true;
        CursorOnClick(MousePos);
    }
    else if (!HoverOverBox(MousePos) && pge.GetMouse(0).bPressed && bBoxActive)
    {
        bBoxActive = false;
    }

    // Handle key & mouse input
    if (bBoxActive) 
    { 
        HandleInputKey(pge);
        
        // Cursor selection
        if (pge.GetMouse(0).bPressed) { CursorOnClick(MousePos); }

        // Flick cursor
        tTimeHolder += fElapsedTime;
        if (tTimeHolder > tHoldAmount)
        {
            tTimeHolder = fmod(tTimeHolder, tHoldAmount);
            bHold = !bHold;
        }
    }

    // Draw text box
    DrawSelf(pge);
}