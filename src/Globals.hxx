#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Menu_Item.H>
#include "DraggableImage.hxx"

class DraggableImage;

extern bool is_image_open;
extern bool draw_point;     // Флаг на расстовление точек
extern bool print_tips;     // Флаг на демонстрацию подсказок

extern Fl_Double_Window*   ruller_window;
extern Fl_File_Chooser*    file_chooser;
extern Fl_Output*          label_image_height;
extern Fl_Output*          label_image_width;
extern Fl_Output*          label_point_first;
extern Fl_Output*          label_point_second;
extern Fl_Input*           input_scale;
extern Fl_Button*          btn_set_point;
extern Fl_Button*          btn_count_scale;
extern Fl_Button*          btn_count_length;
extern Fl_Input*           input_count_scale;
extern DraggableImage*     draggable_image;
extern Fl_Menu_Bar*        ruller_menu_bar;
extern Fl_Menu_Item        ruller_menu_item[];
