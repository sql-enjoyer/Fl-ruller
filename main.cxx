#include "fltk.h"
#include "Point.h"
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <cmath>

//==========================================================================

bool is_image_open = false;
bool draw_point = false;
bool print_tips = true;
double scale; 

//==========================================================================

const int APP_WIDTH = 1000;
const int APP_HEIGHT = 600;
const char *APP_TITLE = "Рулетка";

const int WIDGETS_HEIGHT = 30;

const int MENU_BAR_X = 0;
const int MENU_BAR_Y = 0;
const int MENU_BAR_HEIGHT = 25;
const int MENU_BAR_WIDTH = APP_WIDTH;

const int IMAGE_BOX_X = 10;
const int IMAGE_BOX_Y = MENU_BAR_HEIGHT + 10;
const int IMAGE_BOX_WIDTH = IMAGE_BOX_X + APP_WIDTH/1.5;
const int IMAGE_BOX_HEIGHT = APP_HEIGHT - IMAGE_BOX_Y - 10;

const int LABEL_IMAGE_HEIGHT_X = IMAGE_BOX_X+IMAGE_BOX_WIDTH+100;
const int LABEL_IMAGE_HEIGHT_Y = MENU_BAR_HEIGHT + 80;
const int LABEL_IMAGE_HEIGHT_WIDTH = 50;
const int LABEL_IMAGE_HEIGHT_HEIGHT = WIDGETS_HEIGHT;

const int LABEL_IMAGE_WIDTH_X = LABEL_IMAGE_HEIGHT_X+145;
const int LABEL_IMAGE_WIDTH_Y = LABEL_IMAGE_HEIGHT_Y;
const int LABEL_IMAGE_WIDTH_WIDTH = LABEL_IMAGE_HEIGHT_WIDTH;
const int LABEL_IMAGE_WIDTH_HEIGHT = WIDGETS_HEIGHT;

const int LABEL_IMAGE_LABEL_SIZE = 20;

const int LABEL_POINT_FIRST_X = LABEL_IMAGE_HEIGHT_X-55;
const int LABEL_POINT_FIRST_Y = LABEL_IMAGE_HEIGHT_Y + 70;
const int LABEL_POINT_FIRST_WIDTH = 100;
const int LABEL_POINT_FIRST_HEIGHT = WIDGETS_HEIGHT;

const int LABEL_POINT_SECOND_X = LABEL_POINT_FIRST_X+130;
const int LABEL_POINT_SECOND_Y = LABEL_POINT_FIRST_Y;
const int LABEL_POINT_SECOND_WIDTH = LABEL_POINT_FIRST_WIDTH;
const int LABEL_POINT_SECOND_HEIGHT = LABEL_POINT_FIRST_HEIGHT;

const int BTN_SET_POINT_X = LABEL_IMAGE_HEIGHT_X - 40;
const int BTN_SET_POINT_Y = LABEL_POINT_FIRST_Y + 40;
const int BTN_SET_POINT_WIDTH = 200;
const int BTN_SET_POINT_HEIGHT = WIDGETS_HEIGHT;

const int INPUT_COUNT_SCALE_X = BTN_SET_POINT_X+35;
const int INPUT_COUNT_SCALE_Y = BTN_SET_POINT_Y+50;
const int INPUT_COUNT_SCALE_WIDTH = 100;
const int INPUT_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

const int BTN_COUNT_SCALE_X = BTN_SET_POINT_X;
const int BTN_COUNT_SCALE_Y = INPUT_COUNT_SCALE_Y+40;
const int BTN_COUNT_SCALE_WIDTH = 200;
const int BTN_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

const int INPUT_SCALE_X = BTN_COUNT_SCALE_X+50;
const int INPUT_SCALE_Y = BTN_COUNT_SCALE_Y+50;
const int INPUT_SCALE_WIDTH = 100;
const int INPUT_SCALE_HEIGHT = WIDGETS_HEIGHT;

const int BTN_COUNT_LENGTH_X = BTN_SET_POINT_X;
const int BTN_COUNT_LENGTH_Y = INPUT_SCALE_Y+40;
const int BTN_COUNT_LENGTH_WIDTH = 200;
const int BTN_COUNT_LENGTH_HEIGHT = WIDGETS_HEIGHT;

const int DRAGGBLE_IMAGE_X = 0;
const int DRAGGBLE_IMAGE_Y = 0;

//==========================================================================

extern void build_ruller_window();
extern void build_ruller_menu_bar();
extern void build_file_chooser();
extern void build_label_image_size();
extern void build_btn_set_point();
extern void build_label_point();
extern void build_input_count_scale();
extern void build_input_scale();
extern void build_btn_count_length();
extern void build_draggble_image();

extern void quit_callback(Fl_Widget *, void *);
extern void open_file_callback(Fl_Widget *, void *);
extern void btn_set_point_callback(Fl_Widget *, void *);
extern void btn_count_scale_callback(Fl_Widget *, void *);
extern void btn_count_length_callback(Fl_Widget *, void *);
extern void check_tips_callback(Fl_Widget *, void *);

extern void set_changed(bool v);
extern void update_title();
extern void update_label_image_size();
extern void update_lable_point();

//==========================================================================

Point first;
Point second;

class DraggableImage : public Fl_Widget {
    Fl_JPEG_Image* original_image;
    int drag_x, drag_y;
    double scale = 1;
    bool p = false;

public:
    Fl_Shared_Image *shared_image;

    DraggableImage(int X, int Y) : Fl_Widget(IMAGE_BOX_X, IMAGE_BOX_Y, 0, 0){}

	void setScale() {

	    shared_image = Fl_Shared_Image::get(original_image);

	    Fl_Image *temp;
	    temp = shared_image->copy(static_cast<int>(shared_image->w() * scale), static_cast<int>(shared_image->h() * scale));

	    shared_image = (Fl_Shared_Image *)temp;

	    size(shared_image->w(), shared_image->h());
	}

	void setImage(const char* filename) {
	    original_image = new Fl_JPEG_Image(filename);
	    shared_image = Fl_Shared_Image::get(original_image);

	    if (shared_image->w() > IMAGE_BOX_WIDTH || shared_image->h() > IMAGE_BOX_HEIGHT) {
	        Fl_Image* temp;
	        float aspect_ratio = static_cast<float>(shared_image->w()) / shared_image->h();
	        
	        if (shared_image->w() > shared_image->h()) {
	            temp = shared_image->copy(IMAGE_BOX_WIDTH, static_cast<int>(IMAGE_BOX_WIDTH / aspect_ratio));
	        } else {
	            temp = shared_image->copy(static_cast<int>(IMAGE_BOX_HEIGHT * aspect_ratio), IMAGE_BOX_HEIGHT);
	        }
	        shared_image = (Fl_Shared_Image *)temp;
	    }

	    size(shared_image->w(), shared_image->h());
	    position(IMAGE_BOX_X, IMAGE_BOX_Y);
	}

    int handle(int event) {
        switch(event) {
            case FL_PUSH:{
                if (draw_point) {
                    int x = Fl::event_x();
                    int y = Fl::event_y();
                    if (!p) {
                        first.x = x;
                        first.y = y;
                        p = true;
                        if(print_tips) fl_message("Координаты первой точки: (%d, %d)", first.x, first.y);
                    } else {
                        second.x = x;
                        second.y = y;
                        p = false;
                        draw_point = false;
                        if(print_tips) fl_message("Координаты второй точки: (%d, %d)", second.x, second.y);
                        update_lable_point();
                        Fl::redraw();
                    }
                    break;
                }
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                return 1;
            }
            case FL_DRAG:{
                int dx = Fl::event_x() - drag_x;
                int dy = Fl::event_y() - drag_y;
                position(x() + dx, y() + dy);
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                Fl::redraw();
                return 1;
            }
			case FL_MOUSEWHEEL: {
			    scale *= Fl::event_dy() < 0 ? 1.1 : 0.9;
			    setScale();
			    Fl::redraw();
			    update_label_image_size();
			    return 1;
			}
        }
        return Fl_Widget::handle(event);
    }

    void draw() override {
        if (shared_image) 
            shared_image->draw(x(), y());

        fl_line_style(FL_SOLID, 5);
        fl_color(FL_RED);
        fl_line(first.x, first.y, second.x, second.y);
        fl_line_style(0);
    }
};

Fl_Window *ruller_window;
Fl_Menu_Bar *ruller_menu_bar;
Fl_File_Chooser *file_chooser;
DraggableImage *draggable_image;
Fl_Output *label_image_height;
Fl_Output *label_image_width;
Fl_Output *label_point_first;
Fl_Output *label_point_second;
Fl_Input *input_scale;
Fl_Button *btn_set_point;
Fl_Button *btn_count_scale;
Fl_Button *btn_count_length;
Fl_Input *input_count_scale;

Fl_Menu_Item ruller_menu_item[] = {
	{"Открыть изображение...", FL_COMMAND + 'o', open_file_callback},
	{"Подсказки", FL_ALT + 't', check_tips_callback, nullptr, FL_MENU_TOGGLE | FL_MENU_VALUE},
	{"Выйти", FL_COMMAND + 'q', quit_callback},
	{ 0 }
};

//==========================================================================

void build_ruller_window() {
	ruller_window = new Fl_Window(APP_WIDTH, APP_HEIGHT, APP_TITLE);
	ruller_window->callback(quit_callback);
}

void build_ruller_menu_bar(){
	ruller_menu_bar = new Fl_Menu_Bar(MENU_BAR_X, MENU_BAR_Y, MENU_BAR_WIDTH, MENU_BAR_HEIGHT);
	ruller_menu_bar->copy(ruller_menu_item);
}

void build_file_chooser(){
	file_chooser = new Fl_File_Chooser(".", "*.{jpg,jpeg}", Fl_File_Chooser::SINGLE, "Выберите изображение");
}

void build_label_image_size(){
	label_image_height = new Fl_Output(LABEL_IMAGE_HEIGHT_X, LABEL_IMAGE_HEIGHT_Y, LABEL_IMAGE_HEIGHT_WIDTH, LABEL_IMAGE_HEIGHT_HEIGHT, "Высота:");
	label_image_width = new Fl_Output(LABEL_IMAGE_WIDTH_X, LABEL_IMAGE_WIDTH_Y, LABEL_IMAGE_WIDTH_WIDTH, LABEL_IMAGE_WIDTH_HEIGHT, "Длина:");

	label_image_height->labelsize(LABEL_IMAGE_LABEL_SIZE);
	label_image_width->labelsize(LABEL_IMAGE_LABEL_SIZE);

	label_image_height->textsize(LABEL_IMAGE_LABEL_SIZE);
	label_image_width->textsize(LABEL_IMAGE_LABEL_SIZE);

	label_image_height->labelfont(FL_BOLD);
	label_image_width->labelfont(FL_BOLD);

	update_label_image_size();
}

void build_label_point(){
	label_point_first = new Fl_Output(LABEL_POINT_FIRST_X, LABEL_POINT_FIRST_Y, LABEL_POINT_FIRST_WIDTH, LABEL_POINT_FIRST_HEIGHT, "1:");
	label_point_second = new Fl_Output(LABEL_POINT_SECOND_X, LABEL_POINT_SECOND_Y, LABEL_POINT_SECOND_WIDTH, LABEL_POINT_SECOND_HEIGHT, "2:");
} 

void build_btn_set_point(){
	btn_set_point = new Fl_Button(BTN_SET_POINT_X, BTN_SET_POINT_Y, BTN_SET_POINT_WIDTH, BTN_SET_POINT_HEIGHT, "Установить точки");
	btn_set_point->callback(btn_set_point_callback);
}

void build_input_count_scale(){
	input_count_scale = new Fl_Input(INPUT_COUNT_SCALE_X, INPUT_COUNT_SCALE_Y, INPUT_COUNT_SCALE_WIDTH, INPUT_COUNT_SCALE_HEIGHT, "Величина:");
}

void build_btn_count_scale(){
	btn_count_scale = new Fl_Button(BTN_COUNT_SCALE_X, BTN_COUNT_SCALE_Y, BTN_COUNT_SCALE_WIDTH, BTN_COUNT_SCALE_HEIGHT, "Вычислить масштаб");
	btn_count_scale->callback(btn_count_scale_callback);
}

void build_input_scale(){
	input_scale = new Fl_Input(INPUT_SCALE_X, INPUT_SCALE_Y, INPUT_SCALE_WIDTH, INPUT_SCALE_HEIGHT, "Масштаб:");
}

void build_btn_count_length(){
	btn_count_length = new Fl_Button(BTN_COUNT_LENGTH_X, BTN_COUNT_LENGTH_Y, BTN_COUNT_LENGTH_WIDTH, BTN_COUNT_LENGTH_HEIGHT, "Вычислить длину");
	btn_count_length->callback(btn_count_length_callback);
}

void build_draggble_image(){
	draggable_image = new DraggableImage(DRAGGBLE_IMAGE_X, DRAGGBLE_IMAGE_Y);
}

//==========================================================================

void quit_callback(Fl_Widget *, void *) {
	int ans = fl_choice("Вы действительно хотите выйти?", "Нет", "Да", NULL);
	if (ans == 1)
		exit(0);
}

void open_file_callback(Fl_Widget*, void*) {
    file_chooser->show();
    while (file_chooser->shown())
        Fl::wait();

    const char* file_path = file_chooser->value();
    if(!file_chooser->count())
    	return;
    draggable_image->setImage(file_path);
    Fl::redraw();
    set_changed(true);
}

void btn_set_point_callback(Fl_Widget *, void *){
	if(!draggable_image->shared_image){
		fl_alert("ошибка: установить изображение!");
		return;
	}
    if(print_tips) fl_message("Установите координаты для точек.");
    draw_point = true;
}

void btn_count_scale_callback(Fl_Widget *, void *) {
    std::stringstream ss(input_count_scale->value());
    int num;
    
    if (ss >> num) {
        double distance = sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));
        if (distance == 0) {
            fl_alert("Ошибка: точки совпадают, деление на ноль!");
            return;
        }

        std::stringstream resultStream;
        resultStream << static_cast<double>(num) / distance;

        fl_message(resultStream.str().c_str());
        input_scale->value(resultStream.str().c_str());
    } else {
        fl_alert("Ошибка: некорректный ввод величины.");
    }
}

void btn_count_length_callback(Fl_Widget *, void *){
    std::stringstream resultStream;
    resultStream << "Результат: ";
    resultStream << sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2))*atof(input_scale->value());

    fl_message(resultStream.str().c_str());
}

void check_tips_callback(Fl_Widget *, void *){
	print_tips = !print_tips;
}

//==========================================================================

void set_changed(bool v){
	if (v != is_image_open) {
		is_image_open = v;
		update_title();
		update_label_image_size();
	}
}

void update_title() {
    if (is_image_open) {
        char title[260];
        snprintf(title, sizeof(title), "%s - %s", APP_TITLE, file_chooser->value());
        ruller_window->copy_label(title);
    } else {
        ruller_window->label(APP_TITLE); 
    }
}

void update_label_image_size(){
    auto update_label = [](Fl_Output* label, int value) {
        std::ostringstream oss;
        oss << value;
        label->value(oss.str().c_str());
    };
    if(is_image_open){
        update_label(label_image_height, draggable_image->shared_image->h());
        update_label(label_image_width, draggable_image->shared_image->w());
    }else{
    	label_image_height->value("");
    	label_image_width->value("");
    }
}

void update_lable_point(){
    auto update_label = [](Fl_Output* label, int i, int j) {
        std::ostringstream oss;
        oss << i << ' ' << j;
        label->value(oss.str().c_str());
    };
    if(is_image_open){
    	update_label(label_point_first, first.x, first.y);
    	update_label(label_point_second, second.x, second.y);	
    }else{
    	label_point_first->value("");
    	label_point_second->value("");
    }
}

//==========================================================================

int main(int argc, char const *argv[])
{
	build_ruller_window();
	build_draggble_image();
	build_label_image_size();
	build_label_point();
	build_btn_set_point();
	build_input_count_scale();
	build_btn_count_scale();
	build_input_scale();
	build_btn_count_length();
	build_ruller_menu_bar();
	build_file_chooser();

	ruller_window->end();
	ruller_window->show();
	return Fl::run();
}