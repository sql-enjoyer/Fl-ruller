#include "Globals.hxx"
#include "GUI.hxx"
#include "Callbacks.hxx"
#include "Utils.hxx"
#include "DraggableImage.hxx"

int main()
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