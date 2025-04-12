#include "Utils.hxx"


void set_changed(bool v) {
	is_image_open = v;
    update_title();
    update_label_image_size();
}

void update_title() {
    if (is_image_open) {
        char title[260];
        snprintf(title, sizeof(title), "%s - %s", APP_TITLE, file_chooser->value());
        ruller_window->copy_label(title);
    }
    else
        ruller_window->label(APP_TITLE); 
}

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

template<class T>
const char* num_to_cstr(T num) {
    static std::string str;
    str = std::to_string(num);
    return str.c_str();
}

template const char* num_to_cstr<int>(int);
template const char* num_to_cstr<double>(double);

bool is_number(const char* cstr) {
    std::string s = cstr;
    return !s.empty() && s.find_first_not_of(".0123456789") == std::string::npos;
}