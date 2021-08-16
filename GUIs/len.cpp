#include <string.h>
#include <FL/Fl_Window.H>
#include <FL/Fl.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Return_Button.H>
#include "../lib.cpp"
Fl_Input* input;
Fl_Output* output;
void cb_getlen(Fl_Widget* widget, void*) {
    const char* str = input->value();
    int length = strlen(str);
    std::string strLen = itos(length);
    const char* charLen = strLen.c_str();
    output->value(charLen);
}
int main() {
    Fl_Window window(350,220,"Length");
    window.begin();
    Fl_Return_Button button(50,130,270,60);
    input = new Fl_Input(90,30,230,25,"string");
    output = new Fl_Output(90,80,230,25,"length");
    window.end();
    button.callback(cb_getlen);
    window.show();
    return Fl::run();
}
