//
// Copyright 2020 Electronic Arts Inc.
//
// TiberianDawn.DLL and RedAlert.dll and corresponding source code is free
// software: you can redistribute it and/or modify it under the terms of
// the GNU General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.

// TiberianDawn.DLL and RedAlert.dll and corresponding source code is distributed
// in the hope that it will be useful, but with permitted additional restrictions
// under Section 7 of the GPL. See the GNU General Public License in LICENSE.TXT
// distributed with this program. You should have received a copy of the
// GNU General Public License along with permitted additional restrictions
// with this program. If not, see https://github.com/electronicarts/CnC_Remastered_Collection

#include "function.h"
#include "drop.h"
#include "framelimit.h"
#include <time.h>

#define CLOSE_DROPDOWNS() if (gdiactlikebtn.IsDropped) { gdiactlikebtn.Collapse(); display = REDRAW_BACKGROUND; } if (nodactlikebtn.IsDropped) { nodactlikebtn.Collapse(); display = REDRAW_BACKGROUND; }
#define NUM_OPTIONS 1
#define OPTIONS_HEIGHT ((NUM_OPTIONS * 6 * factor) + 4 * factor)

void Com_MochaOptions_Dialog(void)
{
    int factor = (SeenBuff.Get_Width() == 320) ? 1 : 2;
    /*........................................................................
    Dialog & button dimensions
    ........................................................................*/
    int d_dialog_w = 290 * factor;                      // dialog width
    int d_dialog_h = 190 * factor;                      // dialog height
    int d_dialog_x = ((320 * factor - d_dialog_w) / 2); // dialog x-coord
    int d_dialog_y = ((200 * factor - d_dialog_h) / 2); // dialog y-coord
    int d_dialog_cx = d_dialog_x + (d_dialog_w / 2);    // center x-coord

    int d_txt6_h = 6 * factor + 1; // ht of 6-pt text
    int d_margin1 = 5 * factor;    // margin width/height
    int d_margin2 = 2 * factor;    // margin width/height

    int d_ok_w = 45 * factor;
    int d_ok_h = 9 * factor;
    int d_ok_x = d_dialog_x + (d_dialog_w / 6) - (d_ok_w / 2);
    int d_ok_y = d_dialog_y + d_dialog_h - d_ok_h - d_margin1 - factor * 6;

    /*........................................................................
    Button Enumerations
    ........................................................................*/
    enum
    {
        BUTTON_GDIACTLIKE = 100,
        BUTTON_NODACTLIKE,
        BUTTON_OPTIONS,
        BUTTON_OK,
        BUTTON_LOAD,
    };

    /*........................................................................
    Redraw values: in order from "top" to "bottom" layer of the dialog
    ........................................................................*/
    typedef enum
    {
        REDRAW_NONE = 0,
        REDRAW_MESSAGE,
        REDRAW_BUTTONS,
        REDRAW_BACKGROUND,
        REDRAW_ALL = REDRAW_BACKGROUND
    } RedrawType;

    RedrawType display = REDRAW_ALL; // redraw level
    KeyNumType input;

    int optiontabs[] = {8}; // tabs for player list box
    int i;

    int start_x = d_dialog_x + (4 * factor);
    int start_y = d_dialog_y + (d_txt6_h * 3);

    void const* up_button;
    void const* down_button;

    if (InMainLoop || factor == 1) {
        up_button = Hires_Retrieve("BTN-UP.SHP");
        down_button = Hires_Retrieve("BTN-DN.SHP");
    } else {
        up_button = Hires_Retrieve("BTN-UP2.SHP");
        down_button = Hires_Retrieve("BTN-DN2.SHP");
    }

    GadgetClass* commands; // button list

    char gdiactliketext[64] = "";
    Fancy_Text_Print("", 0, 0, 0, 0, TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW);
    DropListClass gdiactlikebtn(BUTTON_GDIACTLIKE,
                                gdiactliketext,
                                sizeof(gdiactliketext),
                                TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW,
                                start_x + (40 * factor),
                                start_y,
                                80 * factor,
                                15 * factor,
                                up_button,
                                down_button);

    char nodactliketext[64] = "";
    Fancy_Text_Print("", 0, 0, 0, 0, TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW);
    DropListClass nodactlikebtn(BUTTON_NODACTLIKE,
                                nodactliketext,
                                sizeof(nodactliketext),
                                TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW,
                                start_x + (40 * factor),
                                start_y + (d_txt6_h * 2),
                                80 * factor,
                                15 * factor,
                                up_button,
                                down_button);

    CheckListClass optionlist(BUTTON_OPTIONS,
                              ScreenWidth / 2,
                              start_y,
                              (d_dialog_w - (8 * factor)) / 2,
                              OPTIONS_HEIGHT,
                              TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW,
                              up_button,
                              down_button);

    TextButtonClass okbtn(BUTTON_OK, TXT_OK, TPF_CENTER | TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW, d_ok_x, d_ok_y, d_ok_w, d_ok_h);

    // Build the button list
    commands = &optionlist;
    okbtn.Add_Tail(*commands);
    gdiactlikebtn.Add_Tail(*commands);
    nodactlikebtn.Add_Tail(*commands);

    gdiactlikebtn.Add_Item(Text_String(TXT_GDI));
    gdiactlikebtn.Add_Item("Hassan's Elite Guard");
    gdiactlikebtn.Set_Selected_Index(Options.ActLikeOverrideGDI);
    gdiactlikebtn.Set_Read_Only(true);

    nodactlikebtn.Add_Item("Rogue Nation");
    nodactlikebtn.Add_Item(Text_String(TXT_NOD));
    nodactlikebtn.Set_Selected_Index(Options.ActLikeOverrideNod);
    nodactlikebtn.Set_Read_Only(true);

    // Init button states
    optionlist.Set_Tabs(optiontabs);
    optionlist.Set_Read_Only(false);

    optionlist.Add_Item("Ignore Singleplayer Tech Level");

    optionlist.Check_Item(0, Options.IgnoreSingleplayerTechLevel);

    Load_Title_Screen(TitlePicture, &HidPage, Palette);
    Blit_Hid_Page_To_Seen_Buff();
    Set_Palette(Palette);

    while (Get_Mouse_State() > 0)
        Show_Mouse();

    while (true) {
        // If we have just received input focus again after running in the background then
        // we need to redraw.
        if (AllSurfaces.SurfacesRestored) {
            AllSurfaces.SurfacesRestored = false;
            display = REDRAW_ALL;
        }

        // Invoke game callback
        Call_Back();

        // Refresh display if needed
        if (display) {
            Hide_Mouse();
            // Redraw backgound & dialog box
            if (display >= REDRAW_BACKGROUND) {
                Dialog_Box(d_dialog_x, d_dialog_y, d_dialog_w, d_dialog_h);

                // init font variables

                Fancy_Text_Print(
                    TXT_NONE, 0, 0, TBLACK, TBLACK, TPF_CENTER | TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW);

                /*...............................................................
                Dialog & Field labels
                ...............................................................*/
                Draw_Caption(TXT_SETTINGS, d_dialog_x, d_dialog_y, d_dialog_w);

                Fancy_Text_Print("GDI Faction:",
                                 start_x,
                                 start_y,
                                 CC_GREEN,
                                 TBLACK,
                                 TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW);

                Fancy_Text_Print("Nod Faction:",
                                 start_x,
                                 start_y + (d_txt6_h * 2),
                                 CC_GREEN,
                                 TBLACK,
                                 TPF_6PT_GRAD | TPF_USE_GRAD_PAL | TPF_NOSHADOW);
            }

            // Redraw buttons
            if (display >= REDRAW_BUTTONS) {
                commands->Flag_List_To_Redraw();
            }

            Show_Mouse();
            display = REDRAW_NONE;
        }

        // Get user input
        bool gdidroplist_is_dropped = gdiactlikebtn.IsDropped;
        bool noddroplist_is_dropped = nodactlikebtn.IsDropped;
        input = commands->Input();

        // Redraw everything if the droplist collapsed
        if (gdidroplist_is_dropped && !gdiactlikebtn.IsDropped) {
            display = REDRAW_BACKGROUND;
        }
        if (noddroplist_is_dropped && !nodactlikebtn.IsDropped) {
            display = REDRAW_BACKGROUND;
        }

        if (input & KN_BUTTON) {
            CLOSE_DROPDOWNS();
        }

        // Process input
        switch (input) {
        case (BUTTON_GDIACTLIKE | KN_BUTTON):
            Options.ActLikeOverrideGDI = HousesType(gdiactlikebtn.Current_Index() + HOUSE_GOOD);
            display = REDRAW_BACKGROUND;
            CLOSE_DROPDOWNS();
            break;

        case (BUTTON_NODACTLIKE | KN_BUTTON):
            Options.ActLikeOverrideNod = HousesType(nodactlikebtn.Current_Index() + HOUSE_GOOD);
            display = REDRAW_BACKGROUND;
            CLOSE_DROPDOWNS();
            break;

        case (BUTTON_OPTIONS | KN_BUTTON):
            Options.IgnoreSingleplayerTechLevel = optionlist.Is_Checked(0);

            if (display < REDRAW_MESSAGE)
                display = REDRAW_MESSAGE;
            CLOSE_DROPDOWNS();
            break;

        case (BUTTON_OK | KN_BUTTON):
        case (KN_ESC):
            // Restore screen
            Hide_Mouse();
            Load_Title_Screen(TitlePicture, &HidPage, Palette);
            Blit_Hid_Page_To_Seen_Buff();
            Show_Mouse();

            // Save any changes made to our options
            Options.Save_Settings();
            return;

        }
        Frame_Limiter();
    }

}
