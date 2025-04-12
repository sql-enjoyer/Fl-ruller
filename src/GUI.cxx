#include "GUI.hxx"
#include "Globals.hxx"
#include "Config.hxx"
#include "Callbacks.hxx"
#include "Utils.hxx"

using namespace Config;

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