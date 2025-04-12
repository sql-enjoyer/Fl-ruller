#include "Callbacks.hxx"


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
