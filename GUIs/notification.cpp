#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Output.H>
#include <iostream>

long windowWidth = 350;
long windowHeight = 250;

Fl_Output* outputBox;
Fl_Window* window;
int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cout << "Usage:\n" << argv[0] << " <message>" << std::endl;
	return 0;
    }
    window = new Fl_Window(windowWidth,windowHeight,"Notification");
    window->begin();
    outputBox = new Fl_Output(20,20,windowWidth-40,windowHeight-40);
    window->end();
    outputBox->value(argv[1]);
    window->show();
    return Fl::run();
}
