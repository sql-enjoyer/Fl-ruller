#pragma once
#include <FL/fl_ask.H>
#include "Globals.hxx"
#include "Utils.hxx"

// Вызывается при выходе из приложения
extern void quit_callback(Fl_Widget *, void *);

// Вызывается при выборе файла
extern void open_file_callback(Fl_Widget *, void *);

// Переходим в режим расстановки точек на изображении
extern void btn_set_point_callback(Fl_Widget *, void *);

// Считаем масштаб
extern void btn_count_scale_callback(Fl_Widget *, void *);

// Считаем расстояния между заданными точками
extern void btn_count_length_callback(Fl_Widget *, void *);

// Включение/выключение подсказок
extern void check_tips_callback(Fl_Widget *, void *);
