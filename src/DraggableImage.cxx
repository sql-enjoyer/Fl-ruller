#include "DraggableImage.hxx"

DraggableImage::DraggableImage(int x, int y) : Fl_Widget(x, y, 0, 0),
                               original_image(nullptr),
                               shared_image(nullptr),
                               initial_x(x),
                               initial_y(y),
                               drag_x(0),
                               drag_y(0) { fl_register_images(); }

void DraggableImage::setImage(const char* filename) {
    // if(original_image) {
    //     original_image->release();
    //     shared_image->release();
    // }

    image_scale = 1.0;
    original_image = Fl_Shared_Image::get(filename);
    shared_image = static_cast<Fl_Shared_Image*>(original_image->copy());

    size(shared_image->w(), shared_image->h());
    position(initial_x, initial_y);
}

void DraggableImage::setScale() {
    Fl_Image* temp = original_image->copy(
        static_cast<int>(original_image->w() * image_scale), 
        static_cast<int>(original_image->h() * image_scale)
    );

    // Здесь происходит утечка ресурсов, пока не понимаю как фиксить
    // Раскоменть код ниже что бы увидеть дамп памяти
    // if (shared_image)
    //     shared_image->release();

    shared_image = static_cast<Fl_Shared_Image*>(temp);
    size(shared_image->w(), shared_image->h());
}

int DraggableImage::handle(int event) {
    if(!shared_image)
        return Fl_Widget::handle(event);
         
    switch(event)
    {
        case FL_PUSH:
        {
            drag_x = Fl::event_x();
            drag_y = Fl::event_y();
            if (draw_point) {
                if (!point_flag) {
                    first.x = drag_x;
                    first.y = drag_y;
                    point_flag = true;

                    if(print_tips) 
                        fl_message("Координаты первой точки: (%d, %d)", first.x, first.y);
                } 
                else {
                    second.x = drag_x;
                    second.y = drag_y;
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
            int dx = Fl::event_x() - drag_x;
            int dy = Fl::event_y() - drag_y;
            position(x() + dx, y() + dy);
            drag_x = Fl::event_x();
            drag_y = Fl::event_y();
            Fl::redraw();
            return 1;
        }
		case FL_MOUSEWHEEL:
        {
		    image_scale += Fl::event_dy() < 0 ? DRAGGBLE_IMAGE_IMAGE_SCALE : -DRAGGBLE_IMAGE_IMAGE_SCALE;
		    setScale();
		    update_label_image_size();
            Fl::redraw();
		    return 1;
		}
    }
    return Fl_Widget::handle(event);
}

