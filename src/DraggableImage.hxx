#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Shared_Image.H>
#include <FL/fl_draw.H>
#include "Utils.hxx"
#include "Config.hxx"
#include "Point.hxx"

using namespace Config;

class DraggableImage : public Fl_Widget {
    Fl_Shared_Image* original_image;    // Оригинальное изображение
    Fl_Shared_Image* shared_image;      // Масштабированное изображение
    int drag_x, drag_y;                 // Координаты нажатий по изображению
    int initial_x, initial_y;           // Начальные координаты
    double image_scale;                 // Масштаб
    bool point_flag = false;            // Для чередования при
                                        // при расставлении точек
public:

    DraggableImage(int x, int y);

    void setImage(const char* filename);

    void setScale();

    int handle(int event);

    void draw() override {
        if (shared_image) 
            shared_image->draw(x(), y());

        fl_line_style(FL_SOLID, 5);
        fl_color(FL_RED);
        fl_line(::first.x, ::first.y, ::second.x, ::second.y);
        fl_line_style(0);
    }
};
