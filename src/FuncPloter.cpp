#include "FuncPloter.h"

void cFuncPloter::remove_chars(std::string& text, const std::string& chars)
{
	for (unsigned int i = 0; i < chars.length(); i += 1)
	{
		text.erase(std::remove(text.begin(), text.end(), chars[i]), text.end());
	}
}

bool cFuncPloter::in_text(const std::string& text, const std::string& pattern)
{
	for (int i = 0; i <= (int)(text.length() - pattern.length()); i += 1)
	{
		if (pattern.length() <= (text.length() - i))
		{
			if (text.compare(i, pattern.length(), pattern) == 0)
			{
				return true;
			}
		}
	}
	return false;
}

bool cFuncPloter::check_setup(const std::string& text, const std::string& setup_id)
{
	if (in_text(text, setup_id + "=")  || in_text(text, setup_id + "= ") ||
		in_text(text, setup_id + " =") || in_text(text, setup_id + " = "))
	{
		return true;
	}

	return false;
}

std::vector<std::string> cFuncPloter::split_string(const std::string& text, const std::string& delim)
{
	std::vector<std::string> splitted_text;

    std::size_t current = 0;
	std::size_t previous = 0;
    
	current = text.find(delim);

	// Handle empty delim
	if (delim.length() == 0)
	{
		splitted_text.push_back(text);
		return splitted_text;
	}

	while (current != std::string::npos) 
	{
		if (text.substr(previous, current - previous).length() > 0)
		{
        	splitted_text.push_back(text.substr(previous, current - previous));
		}
        previous = current + delim.length();
        current = text.find(delim, previous);
    }
	
	if (text.substr(previous, current - previous).length() > 0)
	{
		splitted_text.push_back(text.substr(previous, current - previous));
	}
	
	return splitted_text;
}

void cFuncPloter::WriteSetupFile(std::vector<std::pair<std::string, double>> constants, std::vector<std::string> expressions, 
                                 std::string variable, double x_min, double x_max, double y_min, double y_max, int points)
{
    FILE *f_setup = fopen("setup.txt", "w");
    
    fprintf(f_setup, "# Functions\n");
    for (auto f : expressions) { fprintf(f_setup, "f = %s\n", f.c_str()); }
    fprintf(f_setup, "\n# Variable\nvar = %s\n", variable.c_str());
    fprintf(f_setup, "\n# Constants\n");
    for (auto c : constants) { fprintf(f_setup, "cte = %s = %f\n", c.first.c_str(), c.second); }
    fprintf(f_setup, "\n# Limits\n");
    fprintf(f_setup, "x_min = %f\n", x_min);
    fprintf(f_setup, "x_max = %f\n", x_max);
    fprintf(f_setup, "y_min = %f\n", y_min);
    fprintf(f_setup, "y_max = %f\n", y_max);
    fprintf(f_setup, "\n# Number of points to plot\n");
    fprintf(f_setup, "Npts = %d", points);

    fclose(f_setup);
}

void cFuncPloter::RunParser()
{
    // Parsing variables
    int nPoints;
	double x_min;
	double x_max;
	double y_min;
	double y_max;
    std::string sVariable;
	std::vector<std::string> vExpressions;
	std::vector<std::pair<std::string, double>> vConstants;

    // Delete any previous file
    system("rm output**.dat");

    // Check for any empty box
    for (auto &text : vTextBoxes)
    {
        if ((text.GetText() == "" || text.GetText().find_first_not_of(" \t") == std::string::npos) && 
            text.GetID() != FUNCTION_CONSTANT) 
        { 
            text.bBoxActive = true;
            return; 
        }
    }

    // Handle strings from fields
    for (auto &text : vTextBoxes)
    {
        switch (text.GetID())
        {
            case FUNCTION_EXPRESSION:
                vExpressions.push_back(text.GetText()); break;
            case FUNCTION_VARIABLE:
                sVariable = text.GetText();
                remove_chars(sVariable, " "); break;
            case FUNCTION_X_MIN:
                x_min = stof(text.GetText()); break;
            case FUNCTION_X_MAX:
                x_max = stof(text.GetText()); break;
            case FUNCTION_Y_MIN:
                y_min = stof(text.GetText()); break;
            case FUNCTION_Y_MAX:
                y_max = stof(text.GetText()); break;
            case FUNCTION_N_PTS:
                nPoints = stoi(text.GetText()); break;
            case FUNCTION_CONSTANT:
            {
                if (!text.GetText().empty())
                {
                    std::string cte_name = split_string(text.GetText(), "=")[0]; 
                    double cte_value = stof(split_string(text.GetText(), "=")[1]);
                    remove_chars(cte_name, " ");
                    vConstants.push_back(std::make_pair(cte_name, cte_value));
                }
                break;
            }
        }
    }

	// Handle parsing and computation for each function
	int id = 0;
	for (auto function : vExpressions)
	{
	    // auto start = std::chrono::steady_clock::now();

	    double x;
	    exprtk::parser<double> parser;
	    exprtk::expression<double> expression;
	    exprtk::symbol_table<double> symbol_table;

	    // Set constants and parse function
	    symbol_table.add_variable(sVariable, x);
	    for (auto c : vConstants) { symbol_table.add_constant(c.first, c.second); }
	    symbol_table.add_constants();
    
	    expression.register_symbol_table(symbol_table);
	    parser.compile(function, expression);

	    // Ouput file setup
	    char fname[100];
        sprintf(fname, "output_%d.dat", id);
        FILE *fout = fopen(fname, "w");
	    fprintf(fout, "# function => %s\n", function.c_str());
	    for (auto c : vConstants) { fprintf(fout, "# cte = %s = %f\n", c.first.c_str(), c.second); }
        fprintf(fout, "# x_min = %f\n", x_min);
	    fprintf(fout, "# x_max = %f\n", x_max);
	    fprintf(fout, "# y_min = %f\n", y_min);
	    fprintf(fout, "# y_max = %f\n", y_max);
	    fprintf(fout, "# [x]   [f(x)]\n");
    
	    // Computation
        const double dx = fabs(x_max - x_min) / (double) nPoints;
	    for (x = x_min; x <= x_max; x += dx)
	    {
	    	double y = expression.value();
	    	fprintf(fout, "%f   %f\n", x, y);
	    }

	    fclose(fout);
	    id += 1;

        // auto end = std::chrono::steady_clock::now();
        // std::cout << "Elapsed time (f(x) = " << function << "): " 
	    // 	      << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "sec "
	    // 	      << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() % 1000 << "millisec "
	    // 	      << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() % 1000 << "microsec\n" << std::endl;
	}

    // Write setup file (for python plot)
    WriteSetupFile(vConstants, vExpressions, sVariable, x_min, x_max, y_min, y_max, nPoints);
}

void cFuncPloter::OnGUIUpdate(olc::vi2d vMousePos, float fElapsedTime)
{
    // Draw boxes and Handle input
    for (auto &text : vTextBoxes)
    {
        // Update CapsLock state
        if (GetKey(olc::CAPS_LOCK).bPressed)
        {
            text.bCapsLockOn = !text.bCapsLockOn;
        }

        // Draw and Handle events
        text.OnTextUpdate((*this), vMousePos, fElapsedTime);

        // Draw box tag
        std::string sTagText;
        switch (text.GetID())
        {
        case FUNCTION_EXPRESSION:
            sTagText = "f(x) = "; break;
        case FUNCTION_VARIABLE:
            sTagText = "var = "; break;
        case FUNCTION_CONSTANT:
            sTagText = "cte = "; break;
        case FUNCTION_X_MIN:
            sTagText = "x_min = "; break;
        case FUNCTION_X_MAX:
            sTagText = "x_max = "; break;
        case FUNCTION_Y_MIN:
            sTagText = "y_min = "; break;
        case FUNCTION_Y_MAX:
            sTagText = "y_max = "; break;
        case FUNCTION_N_PTS:
            sTagText = "Npts"; break;
        default:
            sTagText = ""; break;
        }

        // Draw tag in front of box
        olc::vi2d vTagOffset = text.GetOffset() - olc::vi2d{nTextScale * GetTextSize(sTagText).x, 0};
        DrawString(vTagOffset, sTagText, olc::WHITE, nTextScale);
    }

    // Draw buttons
    for (auto &button : vButtons)
    {
        // Draw and Handle events
        button.OnButtonUpdate((*this), vMousePos, nCommand);
    }
}

void cFuncPloter::InsertField(int field_id)
{
    // Get last FIELD index
    int nFieldndx;
    int nButtonndx;
    for (int i = vTextBoxes.size(); i >= 0; i -= 1)
    {
        if (vTextBoxes[i].GetID() == field_id) { nFieldndx = i; break; }
    }
    for (int i = vButtons.size(); i >= 0; i -= 1)
    {
        if (field_id == FUNCTION_EXPRESSION && 
            vButtons[i].GetID() == BUTTON_ADD_FUNCTION)
        {
            nButtonndx = i;
            break;
        }
        if (field_id == FUNCTION_CONSTANT && 
            vButtons[i].GetID() == BUTTON_ADD_CONSTANT)
        {
            nButtonndx = i;
            break;
        }
    }
    
    // Set new field offset
    olc::vi2d vDisplacement = olc::vi2d{0, vTextBoxes[nFieldndx].GetSize().y} + 
                              olc::vi2d{vPaddingFields.x / 2, vPaddingFields.y / 2};
    olc::vi2d vNewFieldOffset = vTextBoxes[nFieldndx].GetOffset() + vDisplacement;
    olc::vi2d vNewFieldSize = nPatchSize * olc::vi2d{25, 1}; // same size for FUNCTION and CONSTANT
    olc::vi2d vUpdateButtonOffset = vButtons[nButtonndx].GetOffset() + vDisplacement;
    
    olcTextGUI NewFunctionField(vNewFieldOffset, vNewFieldSize, nTextScale, olc::WHITE, field_id);
    vTextBoxes.insert(vTextBoxes.begin() + nFieldndx + 1, NewFunctionField);
    vButtons[nButtonndx].SetOffset(vUpdateButtonOffset);
    
    // Reset offset for fields below
    for (int i = nFieldndx + 2; i < (int)vTextBoxes.size(); i += 1)
    {
        olc::vi2d NewOffset = vTextBoxes[i].GetOffset() + vDisplacement;
        vTextBoxes[i].SetOffset(NewOffset);
    }
    for (int i = nButtonndx + 1; i < (int)vButtons.size(); i += 1)
    {
        olc::vi2d NewOffset = vButtons[i].GetOffset() + vDisplacement;
        vButtons[i].SetOffset(NewOffset);
    }
}

bool cFuncPloter::OnUserCreate()
{
    // Set GUI elements fields
    nTextScale = 2;
    nPatchSize = nTextScale * 8; // 8-bit
    vPaddingFields = olc::vi2d{0, 20}; // Spacing between fields

    // Fields positions
    // Functions
    olc::vi2d vFunctionFieldOffset  = olc::vi2d{150, 50};
    olc::vi2d vFunctionFieldSize    = nPatchSize * olc::vi2d{25, 1}; // 25 char line box
    olc::vi2d vFunctionButtonOffset = vFunctionFieldOffset + olc::vi2d{vFunctionFieldSize.x + nPatchSize, -nPatchSize / 2};
    // Variable
    olc::vi2d vVariableFieldOffset = vFunctionFieldOffset + olc::vi2d{0, vFunctionFieldSize.y} + vPaddingFields;
    olc::vi2d vVariableFieldSize   = nPatchSize * olc::vi2d{6, 1};
    // Constants
    olc::vi2d vConstantsFieldOffset  = vVariableFieldOffset + olc::vi2d{0, vVariableFieldSize.y} + vPaddingFields;
    olc::vi2d vConstantsFieldSize    = nPatchSize * olc::vi2d{25, 1};
    olc::vi2d vConstantsButtonOffset = vConstantsFieldOffset + olc::vi2d{vConstantsFieldSize.x + 15, -nPatchSize / 2};
    // Plot limits
    olc::vi2d vLimFieldSize    = nPatchSize * olc::vi2d{8, 1};
    olc::vi2d vXminFieldOffset = vConstantsFieldOffset + olc::vi2d{0, vConstantsFieldSize.y} + vPaddingFields;
    olc::vi2d vXmaxFieldOffset = vXminFieldOffset + olc::vi2d{0, vLimFieldSize.y} + vPaddingFields;
    olc::vi2d vYminFieldOffset = vXmaxFieldOffset + olc::vi2d{0, vLimFieldSize.y} + vPaddingFields;
    olc::vi2d vYmaxFieldOffset = vYminFieldOffset + olc::vi2d{0, vLimFieldSize.y} + vPaddingFields;
    // Number of X points within interval
    olc::vi2d vPtsFieldSize   = nPatchSize * olc::vi2d{8, 1};
    olc::vi2d vPtsFieldOffset = vYmaxFieldOffset + olc::vi2d{0, vLimFieldSize.y} + vPaddingFields;
    // Run button
    olc::vi2d vRunButtonOffset = vPtsFieldOffset + olc::vi2d{0, vPtsFieldSize.y} + vPaddingFields;

    olcTextGUI FunctionField(vFunctionFieldOffset,   vFunctionFieldSize,  nTextScale, olc::WHITE, FUNCTION_EXPRESSION);
    olcTextGUI VariableField(vVariableFieldOffset,   vVariableFieldSize,  nTextScale, olc::WHITE, FUNCTION_VARIABLE);
    olcTextGUI ConstantsField(vConstantsFieldOffset, vConstantsFieldSize, nTextScale, olc::WHITE, FUNCTION_CONSTANT);
    olcTextGUI XminField(vXminFieldOffset, vLimFieldSize, nTextScale, olc::WHITE, FUNCTION_X_MIN);
    olcTextGUI XmaxField(vXmaxFieldOffset, vLimFieldSize, nTextScale, olc::WHITE, FUNCTION_X_MAX);
    olcTextGUI YminField(vYminFieldOffset, vLimFieldSize, nTextScale, olc::WHITE, FUNCTION_Y_MIN);
    olcTextGUI YmaxField(vYmaxFieldOffset, vLimFieldSize, nTextScale, olc::WHITE, FUNCTION_Y_MAX);    
    olcTextGUI PtsField(vPtsFieldOffset,   vPtsFieldSize, nTextScale, olc::WHITE, FUNCTION_N_PTS);
    olcButtonGUI FunctionFieldButton(vFunctionButtonOffset, "+", nTextScale, olc::WHITE, BUTTON_ADD_FUNCTION);
    olcButtonGUI ConstantsFieldButton(vConstantsButtonOffset, "+", nTextScale, olc::WHITE, BUTTON_ADD_CONSTANT);
    olcButtonGUI RunButton(vRunButtonOffset, "Run", nTextScale, olc::WHITE, RUN_PARSER);    
    
    vTextBoxes.push_back(FunctionField);
    vTextBoxes.push_back(VariableField);
    vTextBoxes.push_back(ConstantsField);
    vTextBoxes.push_back(XminField);
    vTextBoxes.push_back(XmaxField);
    vTextBoxes.push_back(YminField);
    vTextBoxes.push_back(YmaxField);
    vTextBoxes.push_back(PtsField);
    vButtons.push_back(FunctionFieldButton);    
    vButtons.push_back(ConstantsFieldButton);
    vButtons.push_back(RunButton);
    
    // Active only topmost box 
    for (unsigned int i = 1; i < vTextBoxes.size(); i += 1)
    {
        vTextBoxes[i].bBoxActive = false;
    }

    return true;
}

bool cFuncPloter::OnUserUpdate(float fElapsedTime)
{
    Clear(olc::VERY_DARK_GREY);
    olc::vi2d vMousePos = {GetMouseX(), GetMouseY()};

    // Handle commands
    if (nCommand == BUTTON_ADD_FUNCTION) { InsertField(FUNCTION_EXPRESSION); nCommand = 0; } 
    if (nCommand == BUTTON_ADD_CONSTANT) { InsertField(FUNCTION_CONSTANT);   nCommand = 0; }
    if (nCommand == RUN_PARSER)          
    { 
        RunParser(); 
        nCommand = 0;
        system("python3.6 python/plot.py -file setup.txt");
        sprPlot = new olc::Sprite("functions.png");
    }

    // Display Info
    olc::vi2d TextSizeNote = GetTextSize("ABNT2 keyboard format");
    DrawString(olc::vi2d{ScreenWidth() - 5, ScreenHeight() - 5} - 2 * TextSizeNote, "ABNT2 keyboard format", olc::YELLOW, 2);

    // Roll through cells
    if (GetKey(olc::Key::TAB).bPressed)
    {
        for (unsigned int i = 0; i < vTextBoxes.size(); i += 1)
        {
            if (vTextBoxes[i].bBoxActive)
            {
                vTextBoxes[i].bBoxActive = false;
                if (i != (vTextBoxes.size() - 1))
                {
                    vTextBoxes[i+1].bBoxActive = true;
                    break;
                }
                else
                {
                    vTextBoxes[0].bBoxActive = true;
                }
            }
        }
    }

    // Draw and handle GUI interaction
    OnGUIUpdate(vMousePos, fElapsedTime);

    // Draw plot
    if (sprPlot != nullptr) { DrawSprite({ScreenWidth() / 2, 50}, sprPlot, 1); }

    return true;
}