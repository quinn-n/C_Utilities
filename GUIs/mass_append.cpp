#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Return_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>
#include <thread>
#include <fstream>
#include <unistd.h>

using namespace std;

Fl_Window* window;
Fl_Multiline_Input* textInput;
Fl_Input* numInput;
Fl_Input* filepath;
Fl_Return_Button* startButton;
Fl_Output* statusOut;
thread appendThread;
thread runningThread;
bool done;

//keep updating the Running text to keep the dots moving. should be run in a seperate thread.
void runningText() {
    int dots = 0;
    string dotsCache;
    string runningString = "Running";
    string completedString;
    while(!done) {
        completedString = "";
        dotsCache = "";
        //find number of dots
        if (dots >= 4) {
            dots = 0;
        }
        for(int i=0;i<dots;i++) {
            dotsCache += ".";
        }
        //compile finished string
        completedString = runningString+dotsCache;
        char* completedChars = new char[completedString.length()];
        strcpy(completedChars,completedString.c_str());
        //update text
        statusOut->value(completedChars);
        Fl::flush();
        dots++;
        usleep(500000);
    }
}

void append(char* fp, char* text, unsigned int times) {
    fstream fi;
    fi.open(fp,fstream::app);
    for(unsigned int i = 0;i<times;i++) {
        fi << text;
    }
    fi.close();
    done = true;
    //usleep takes microseconds
    //usleep(500000);
    statusOut->value("Done!");
    Fl::flush();
}

void cb_start(Fl_Widget* widget, void*) {
    const char* fp = filepath->value();
    const char* text = textInput->value();
    const char* timesChar = numInput->value();
    unsigned int times = atoi(timesChar);
    appendThread = thread(append,(char*) fp,(char*) text,times);
    done = false;
    runningThread = thread(runningText);
    appendThread.join();
    runningThread.join();
}

int main(int argc, char* argv[]) {
    window = new Fl_Window(440,300,"mass_append");
    window->begin();
    textInput = new Fl_Multiline_Input(150,30,160,75,"Text to Append");
    numInput = new Fl_Input(150,135,160,25,"Times to Append");
    filepath = new Fl_Input(150,190,160,25,"Filepath");
    startButton = new Fl_Return_Button(340,30,70,240,"Start");//consider changing width & height of buttons to 75.
    statusOut = new Fl_Output(150,245,160,25,"Status");
    window->end();
    startButton->callback(cb_start);
    window->show();
    return Fl::run();
}