#include "Globals.hxx"
#include "Callbacks.hxx"

bool is_image_open = false;
bool draw_point = false;
bool print_tips = false;

Fl_Double_Window* ruller_window = nullptr;
Fl_File_Chooser* file_chooser = nullptr;
Fl_Output* label_image_height = nullptr;
Fl_Output* label_image_width = nullptr;
Fl_Output* label_point_first = nullptr;
Fl_Output* label_point_second = nullptr;
Fl_Input* input_scale = nullptr;
Fl_Button* btn_set_point = nullptr;
Fl_Button* btn_count_scale = nullptr;
Fl_Button* btn_count_length = nullptr;
Fl_Input* input_count_scale = nullptr;
Fl_Menu_Bar* ruller_menu_bar = nullptr;
DraggableImage* draggable_image = nullptr;

Fl_Menu_Item ruller_menu_item[] = 
{
    {"Открыть изображение...", FL_COMMAND + 'o', open_file_callback},
    {"Подсказки", FL_ALT + 't', check_tips_callback, nullptr, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"Выйти", FL_COMMAND + 'q', quit_callback},
    { 0 }
};
