#pragma once
#include <string>
#include <cmath>
#include "Globals.hxx"


// Вносим изменения после
extern void set_changed(bool v);

// Обновление заголовка приложения
extern void update_title();

// Обновление вывода размера текущего изображения
extern void update_label_image_size();

// Обновление вывода координат точек
extern void update_lable_point();

template<class T>
const char* num_to_cstr(T num);

extern template const char* num_to_cstr<int>(int);
extern template const char* num_to_cstr<double>(double);

// Проверка строки на число
extern bool is_number(const char* cstr);