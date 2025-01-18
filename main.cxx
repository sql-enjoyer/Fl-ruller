#include "Point.h"
#include "fltk.h"
#include <cmath>
#include <string>

//==========================================================================

bool is_image_open = false;
bool draw_point = false;    // Флаг на расстовление точек
bool print_tips = true;     // Флаг на демонстрацию подсказок
                            // при расставлении точек

//==========================================================================

// Главное окно
const int       APP_WIDTH = 1000;
const int       APP_HEIGHT = 600;
const char*     APP_TITLE = "Рулетка";

const int       WIDGETS_HEIGHT = 30;

// Меню
const int       MENU_BAR_X = 0;
const int       MENU_BAR_Y = 0;
const int       MENU_BAR_HEIGHT = 25;
const int       MENU_BAR_WIDTH = APP_WIDTH;

// Изображение
const int       DRAGGBLE_IMAGE_X = 10;
const int       DRAGGBLE_IMAGE_Y = MENU_BAR_HEIGHT + 10;
const int       DRAGGBLE_IMAGE_WIDTH = DRAGGBLE_IMAGE_X + APP_WIDTH/1.5;
const int       DRAGGBLE_IMAGE_HEIGHT = APP_HEIGHT - DRAGGBLE_IMAGE_Y - 10;
const double    DRAGGBLE_IMAGE_IMAGE_SCALE = 0.1;   // Изменение масштаба при
                                                    // приближенни колесиком

// Вывод высоты изображения
const int       LABEL_IMAGE_HEIGHT_X = DRAGGBLE_IMAGE_X+DRAGGBLE_IMAGE_WIDTH+100;
const int       LABEL_IMAGE_HEIGHT_Y = MENU_BAR_HEIGHT + 80;
const int       LABEL_IMAGE_HEIGHT_WIDTH = 50;
const int       LABEL_IMAGE_HEIGHT_HEIGHT = WIDGETS_HEIGHT;

// Вывод длины изображения
const int       LABEL_IMAGE_WIDTH_X = LABEL_IMAGE_HEIGHT_X+145;
const int       LABEL_IMAGE_WIDTH_Y = LABEL_IMAGE_HEIGHT_Y;
const int       LABEL_IMAGE_WIDTH_WIDTH = LABEL_IMAGE_HEIGHT_WIDTH;
const int       LABEL_IMAGE_WIDTH_HEIGHT = WIDGETS_HEIGHT;

const int       LABEL_IMAGE_LABEL_SIZE = 20;

// Вывод координат первой точки
const int       LABEL_POINT_FIRST_X = LABEL_IMAGE_HEIGHT_X-55;
const int       LABEL_POINT_FIRST_Y = LABEL_IMAGE_HEIGHT_Y + 70;
const int       LABEL_POINT_FIRST_WIDTH = 100;
const int       LABEL_POINT_FIRST_HEIGHT = WIDGETS_HEIGHT;

// Вывод координат второй точки
const int       LABEL_POINT_SECOND_X = LABEL_POINT_FIRST_X+130;
const int       LABEL_POINT_SECOND_Y = LABEL_POINT_FIRST_Y;
const int       LABEL_POINT_SECOND_WIDTH = LABEL_POINT_FIRST_WIDTH;
const int       LABEL_POINT_SECOND_HEIGHT = LABEL_POINT_FIRST_HEIGHT;

// Кнопка для активации расставления точек
const int       BTN_SET_POINT_X = LABEL_IMAGE_HEIGHT_X - 40;
const int       BTN_SET_POINT_Y = LABEL_POINT_FIRST_Y + 40;
const int       BTN_SET_POINT_WIDTH = 200;
const int       BTN_SET_POINT_HEIGHT = WIDGETS_HEIGHT;

// Введенная величина
const int       INPUT_COUNT_SCALE_X = BTN_SET_POINT_X+35;
const int       INPUT_COUNT_SCALE_Y = BTN_SET_POINT_Y+50;
const int       INPUT_COUNT_SCALE_WIDTH = 100;
const int       INPUT_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

// Кнопка расчета масштаба по заданным точкам
const int       BTN_COUNT_SCALE_X = BTN_SET_POINT_X;
const int       BTN_COUNT_SCALE_Y = INPUT_COUNT_SCALE_Y+40;
const int       BTN_COUNT_SCALE_WIDTH = 200;
const int       BTN_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

// Текущий масштаб
const int       INPUT_SCALE_X = BTN_COUNT_SCALE_X+50;
const int       INPUT_SCALE_Y = BTN_COUNT_SCALE_Y+50;
const int       INPUT_SCALE_WIDTH = 100;
const int       INPUT_SCALE_HEIGHT = WIDGETS_HEIGHT;

// Расчет расстояния между заданными точками по масштабу
const int       BTN_COUNT_LENGTH_X = BTN_SET_POINT_X;
const int       BTN_COUNT_LENGTH_Y = INPUT_SCALE_Y+40;
const int       BTN_COUNT_LENGTH_WIDTH = 200;
const int       BTN_COUNT_LENGTH_HEIGHT = WIDGETS_HEIGHT;

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

template<class T>
extern const char* num_to_cstr(T num);
extern const bool is_number(const char* cstr);

//==========================================================================

Fl_Double_Window*   ruller_window;
Fl_File_Chooser*    file_chooser;
Fl_Output*          label_image_height;
Fl_Output*          label_image_width;
Fl_Output*          label_point_first;
Fl_Output*          label_point_second;
Fl_Input*           input_scale;
Fl_Button*          btn_set_point;
Fl_Button*          btn_count_scale;
Fl_Button*          btn_count_length;
Fl_Input*           input_count_scale;

Fl_Menu_Bar*        ruller_menu_bar;
Fl_Menu_Item        ruller_menu_item[] = 
{
    {"Открыть изображение...", FL_COMMAND + 'o', open_file_callback},
    {"Подсказки", FL_ALT + 't', check_tips_callback, nullptr, FL_MENU_TOGGLE | FL_MENU_VALUE},
    {"Выйти", FL_COMMAND + 'q', quit_callback},
    { 0 }
};

Point first;
Point second;

class DraggableImage : public Fl_Widget {
    Fl_Shared_Image* original_image;    // Оригинальное изображение
    Fl_Shared_Image* shared_image;      // Масштабированное изображение
    int drag_x, drag_y;                 // Координаты нажатий по изображению
    int initial_x, initial_y;           // Начальные координаты
    double image_scale;                    // Масштаб
    bool point_flag = false;            // Для чередования при
                                        // при расставлении точек
public:

    DraggableImage(int x, int y) : Fl_Widget(x, y, 0, 0),
                                   original_image(nullptr),
                                   shared_image(nullptr),
                                   initial_x(x),
                                   initial_y(y),
                                   drag_x(0),
                                   drag_y(0) { fl_register_images(); }
    // Устанавливаем изображения
    void setImage(const char* filename) {
        if(original_image) {
            original_image->release();
            shared_image->release();
        }

        image_scale = 1.0;
        original_image = Fl_Shared_Image::get(filename);
        shared_image = static_cast<Fl_Shared_Image*>(original_image->copy());

        size(shared_image->w(), shared_image->h());
        position(initial_x, initial_y);
    }

    // Устанавливаем изображение нужного масштаба
    void setScale() {
        // Временное изображение нужного размера
        Fl_Image* temp = original_image->copy(
            static_cast<int>(original_image->w() * image_scale), 
            static_cast<int>(original_image->h() * image_scale)
        );

        // if (shared_image)
        //     shared_image->release();

        shared_image = static_cast<Fl_Shared_Image*>(temp);
        size(shared_image->w(), shared_image->h());
    }

    int handle(int event) {
        switch(event)
        {
            case FL_PUSH:
            {
                // Сохраняем следующие координаты при перемещении
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                // Смотрим на флаг
                if (draw_point) {
                    // Выбираем какую точку ставить
                    if (!point_flag) {
                        // Сохраняем координаты точек
                        first.x = drag_x;
                        first.y = drag_y;
                        //Поднимаем флаг на следующую точку
                        point_flag = true;

                        if(print_tips) 
                            fl_message("Координаты первой точки: (%d, %d)", first.x, first.y);
                    } 
                    else {
                        // Сохраняем координаты точек
                        second.x = drag_x;
                        second.y = drag_y;
                        // Опускаем флаги
                        point_flag = false;
                        draw_point = false;

                        if(print_tips)
                            fl_message("Координаты второй точки: (%d, %d)", second.x, second.y);
                        update_lable_point();
                        Fl::redraw();
                    }
                }
                return 1;
            }
            case FL_DRAG:
            {
                // Находим разницу при перемещении
                int dx = Fl::event_x() - drag_x;
                int dy = Fl::event_y() - drag_y;
                // Перемещение на разницу
                position(x() + dx, y() + dy);
                // Сохраняем следующие координаты при перемещении
                drag_x = Fl::event_x();
                drag_y = Fl::event_y();
                Fl::redraw();
                return 1;
            }
			case FL_MOUSEWHEEL:
            {
                // Изменяем значение текущего масштаба 
			    image_scale += Fl::event_dy() < 0 ? DRAGGBLE_IMAGE_IMAGE_SCALE : -DRAGGBLE_IMAGE_IMAGE_SCALE;
			    setScale();
			    update_label_image_size();
                Fl::redraw();
			    return 1;
			}
        }
        return Fl_Widget::handle(event);
    }

    void draw() override {
        if (shared_image) 
            shared_image->draw(x(), y());

        // Проводим линию между заданными точками
        fl_line_style(FL_SOLID, 5);
        fl_color(FL_RED);
        fl_line(first.x, first.y, second.x, second.y);
        fl_line_style(0);
    }
};

DraggableImage *draggable_image;

//==========================================================================

void build_ruller_window() {
	ruller_window = new Fl_Double_Window(APP_WIDTH, APP_HEIGHT, APP_TITLE);
	ruller_window->callback(quit_callback);
}

void build_ruller_menu_bar() {
	ruller_menu_bar = new Fl_Menu_Bar(MENU_BAR_X, MENU_BAR_Y, MENU_BAR_WIDTH, MENU_BAR_HEIGHT);
	ruller_menu_bar->copy(ruller_menu_item);
}

void build_file_chooser() {
	file_chooser = new Fl_File_Chooser(".", "*.{bmp,gif,jpg,jpeg,png,xbm,xpm}", Fl_File_Chooser::SINGLE, "Выберите изображение");
}

void build_label_image_size() {
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

void build_label_point() {
	label_point_first = new Fl_Output(LABEL_POINT_FIRST_X, LABEL_POINT_FIRST_Y, LABEL_POINT_FIRST_WIDTH, LABEL_POINT_FIRST_HEIGHT, "1:");
	label_point_second = new Fl_Output(LABEL_POINT_SECOND_X, LABEL_POINT_SECOND_Y, LABEL_POINT_SECOND_WIDTH, LABEL_POINT_SECOND_HEIGHT, "2:");
} 

void build_btn_set_point() {
	btn_set_point = new Fl_Button(BTN_SET_POINT_X, BTN_SET_POINT_Y, BTN_SET_POINT_WIDTH, BTN_SET_POINT_HEIGHT, "Установить точки");
	btn_set_point->callback(btn_set_point_callback);
}

void build_input_count_scale() {
	input_count_scale = new Fl_Input(INPUT_COUNT_SCALE_X, INPUT_COUNT_SCALE_Y, INPUT_COUNT_SCALE_WIDTH, INPUT_COUNT_SCALE_HEIGHT, "Величина:");
}

void build_btn_count_scale() {
	btn_count_scale = new Fl_Button(BTN_COUNT_SCALE_X, BTN_COUNT_SCALE_Y, BTN_COUNT_SCALE_WIDTH, BTN_COUNT_SCALE_HEIGHT, "Вычислить масштаб");
	btn_count_scale->callback(btn_count_scale_callback);
}

void build_input_scale() {
	input_scale = new Fl_Input(INPUT_SCALE_X, INPUT_SCALE_Y, INPUT_SCALE_WIDTH, INPUT_SCALE_HEIGHT, "Масштаб:");
}

void build_btn_count_length() {
	btn_count_length = new Fl_Button(BTN_COUNT_LENGTH_X, BTN_COUNT_LENGTH_Y, BTN_COUNT_LENGTH_WIDTH, BTN_COUNT_LENGTH_HEIGHT, "Вычислить длину");
	btn_count_length->callback(btn_count_length_callback);
}

void build_draggble_image() {
	draggable_image = new DraggableImage(DRAGGBLE_IMAGE_X, DRAGGBLE_IMAGE_Y);
}

//==========================================================================

// Вызывается при выходе из приложения
void quit_callback(Fl_Widget *, void *) {
    if(is_image_open) {
        int ans = fl_choice("Вы действительно хотите выйти?", "Нет", "Да", NULL);
        if (ans == 1)
            exit(0);
    }
    else 
        exit(0);
}

// Вызывается при выборе файла
void open_file_callback(Fl_Widget *, void *) {
    // Ждем пока пользователь выберет файл
    file_chooser->show();
    while (file_chooser->shown())
        Fl::wait();
    // Выходим, если не выбран файл
    if(!file_chooser->count())
        return;

    const char* file_path = file_chooser->value();
    draggable_image->setImage(file_path);
    set_changed(true);
    Fl::redraw();
}

// Переходим в режим расстановки точек на изображении
void btn_set_point_callback(Fl_Widget *, void *) {
	if(!is_image_open) {
		fl_alert("Ошибка: выберете изображение!");
		return;
	}
    if(print_tips) fl_message("Установите точки на изображении.");
    draw_point = true;
}

// Считаем масштаб
void btn_count_scale_callback(Fl_Widget *, void *) {
    const char* cstr_scale = input_count_scale->value();

    if (is_number(cstr_scale)) {
        // Считаем кол-во пикселей между точками по теореме Пифагора
        double distance = 
            sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2));

        if (distance == 0) {
            fl_alert("Ошибка: точки совпадают!");
            return;
        }
		
        // Находим масштаб
        double scale = 
            (static_cast<double>(std::stod(cstr_scale)) / distance);

        fl_message(num_to_cstr(scale));
        input_scale->value(num_to_cstr(scale));
    } 
    else
        fl_alert("Ошибка: некорректный ввод величины!");
}

// Считаем расстояния между заданными точками
void btn_count_length_callback(Fl_Widget *, void *) {
    if(!is_number(input_scale->value())) {
        fl_alert("Ошибка: масштаб может состоять только из цифр!");
        return;
    }

    double scale = std::stod(input_scale->value());
    if(scale == 0.0) {
        fl_alert("Ошибка: масштаб равен нулю!");
        return;
    }

    // Находим кол-во пикселей между точками по теореме Пифагора)
    // не забываем про
    double distance =
        sqrt(pow(second.x - first.x, 2) + pow(second.y - first.y, 2))*scale;

    // Учитываем масштаб при выводе значения
    fl_message("Результат: %f", distance);
}

// Включение/выключение подсказок
void check_tips_callback(Fl_Widget *, void *) {
	print_tips = !print_tips;
}

//==========================================================================

// Вносим изменения после
void set_changed(bool v) {
	is_image_open = v;
    update_title();
    update_label_image_size();
}

// Обновление заголовка приложения
void update_title() {
    if (is_image_open) {
        char title[260];
        snprintf(title, sizeof(title), "%s - %s", APP_TITLE, file_chooser->value());
        ruller_window->copy_label(title);
    }
    else
        ruller_window->label(APP_TITLE); 
}

// Обновление вывода размера текущего изображения
void update_label_image_size() {
    if(is_image_open) {
        label_image_height->value(num_to_cstr(draggable_image->h()));
        label_image_width->value(num_to_cstr(draggable_image->w()));
    }
    else {
    	label_image_height->value("0");
    	label_image_width->value("0");
    }
}

// Обновление вывода координат точек
void update_lable_point() {
    if(is_image_open) {
        std::string labelText; // Строка для форматирования вывода размеров изображения

        labelText = std::to_string(first.x) + ' ' + std::to_string(first.y);
        label_point_first->value(labelText.c_str());

    	labelText = std::to_string(second.x) + ' ' + std::to_string(second.y);
    	label_point_second->value(labelText.c_str());
    }
    else {
    	label_point_first->value("");
    	label_point_second->value("");
    }
}

// Перевод числа в с-строку
template<class T>
const char* num_to_cstr(T num) {
    static std::string str;
    str = std::to_string(num);
    return str.c_str();
}

// Проверка строки на число
const bool is_number(const char* cstr) {
    std::string s = cstr;
    return !s.empty() && s.find_first_not_of(".0123456789") == std::string::npos;
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