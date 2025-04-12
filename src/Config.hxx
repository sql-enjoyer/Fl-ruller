#pragma once

namespace Config {
    // Главное окно
    inline constexpr int       APP_WIDTH = 1000;
    inline constexpr int       APP_HEIGHT = 600;
    inline constexpr const char* APP_TITLE = "Рулетка";
    inline constexpr int       WIDGETS_HEIGHT = 30;

    // Меню
    inline constexpr int       MENU_BAR_X = 0;
    inline constexpr int       MENU_BAR_Y = 0;
    inline constexpr int       MENU_BAR_HEIGHT = 25;
    inline constexpr int       MENU_BAR_WIDTH = APP_WIDTH;

    // Изображение
    inline constexpr int       DRAGGBLE_IMAGE_X = 10;
    inline constexpr int       DRAGGBLE_IMAGE_Y = MENU_BAR_HEIGHT + 10;
    inline constexpr int       DRAGGBLE_IMAGE_WIDTH = DRAGGBLE_IMAGE_X + APP_WIDTH/1.5;
    inline constexpr int       DRAGGBLE_IMAGE_HEIGHT = APP_HEIGHT - DRAGGBLE_IMAGE_Y - 10;
    inline constexpr double    DRAGGBLE_IMAGE_IMAGE_SCALE = 0.1;   // Изменение масштаба при приближении колесиком

    // Вывод высоты изображения
    inline constexpr int       LABEL_IMAGE_HEIGHT_X = DRAGGBLE_IMAGE_X+DRAGGBLE_IMAGE_WIDTH+100;
    inline constexpr int       LABEL_IMAGE_HEIGHT_Y = MENU_BAR_HEIGHT + 80;
    inline constexpr int       LABEL_IMAGE_HEIGHT_WIDTH = 50;
    inline constexpr int       LABEL_IMAGE_HEIGHT_HEIGHT = WIDGETS_HEIGHT;

    // Вывод длины изображения
    inline constexpr int       LABEL_IMAGE_WIDTH_X = LABEL_IMAGE_HEIGHT_X+145;
    inline constexpr int       LABEL_IMAGE_WIDTH_Y = LABEL_IMAGE_HEIGHT_Y;
    inline constexpr int       LABEL_IMAGE_WIDTH_WIDTH = LABEL_IMAGE_HEIGHT_WIDTH;
    inline constexpr int       LABEL_IMAGE_WIDTH_HEIGHT = WIDGETS_HEIGHT;

    inline constexpr int       LABEL_IMAGE_LABEL_SIZE = 20;

    // Вывод координат первой точки
    inline constexpr int       LABEL_POINT_FIRST_X = LABEL_IMAGE_HEIGHT_X-55;
    inline constexpr int       LABEL_POINT_FIRST_Y = LABEL_IMAGE_HEIGHT_Y + 70;
    inline constexpr int       LABEL_POINT_FIRST_WIDTH = 100;
    inline constexpr int       LABEL_POINT_FIRST_HEIGHT = WIDGETS_HEIGHT;

    // Вывод координат второй точки
    inline constexpr int       LABEL_POINT_SECOND_X = LABEL_POINT_FIRST_X+130;
    inline constexpr int       LABEL_POINT_SECOND_Y = LABEL_POINT_FIRST_Y;
    inline constexpr int       LABEL_POINT_SECOND_WIDTH = LABEL_POINT_FIRST_WIDTH;
    inline constexpr int       LABEL_POINT_SECOND_HEIGHT = LABEL_POINT_FIRST_HEIGHT;

    // Кнопка для активации расставления точек
    inline constexpr int       BTN_SET_POINT_X = LABEL_IMAGE_HEIGHT_X - 40;
    inline constexpr int       BTN_SET_POINT_Y = LABEL_POINT_FIRST_Y + 40;
    inline constexpr int       BTN_SET_POINT_WIDTH = 200;
    inline constexpr int       BTN_SET_POINT_HEIGHT = WIDGETS_HEIGHT;

    // Введенная величина
    inline constexpr int       INPUT_COUNT_SCALE_X = BTN_SET_POINT_X+35;
    inline constexpr int       INPUT_COUNT_SCALE_Y = BTN_SET_POINT_Y+50;
    inline constexpr int       INPUT_COUNT_SCALE_WIDTH = 100;
    inline constexpr int       INPUT_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

    // Кнопка расчета масштаба по заданным точкам
    inline constexpr int       BTN_COUNT_SCALE_X = BTN_SET_POINT_X;
    inline constexpr int       BTN_COUNT_SCALE_Y = INPUT_COUNT_SCALE_Y+40;
    inline constexpr int       BTN_COUNT_SCALE_WIDTH = 200;
    inline constexpr int       BTN_COUNT_SCALE_HEIGHT = WIDGETS_HEIGHT;

    // Текущий масштаб
    inline constexpr int       INPUT_SCALE_X = BTN_COUNT_SCALE_X+50;
    inline constexpr int       INPUT_SCALE_Y = BTN_COUNT_SCALE_Y+50;
    inline constexpr int       INPUT_SCALE_WIDTH = 100;
    inline constexpr int       INPUT_SCALE_HEIGHT = WIDGETS_HEIGHT;

    // Расчет расстояния между заданными точками по масштабу
    inline constexpr int       BTN_COUNT_LENGTH_X = BTN_SET_POINT_X;
    inline constexpr int       BTN_COUNT_LENGTH_Y = INPUT_SCALE_Y+40;
    inline constexpr int       BTN_COUNT_LENGTH_WIDTH = 200;
    inline constexpr int       BTN_COUNT_LENGTH_HEIGHT = WIDGETS_HEIGHT;
}