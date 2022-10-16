/* PDF 68 
Exercise

Simplify the constructors of the Widget class in the code below. Initialize the
class members.

Explanation #

The trick was to figure out the correct values for initializing the Widget
class’s attributes outside the constructors.

In line 5 of the Exercise code, we can see the default values of all the
attributes. Hence, we’ll assign these to them outside the constructor.

Another thing to notice is that frame and visible are always initialized
to false and true , respectively. We should simply omit them from the
constructors.

The attributes that can vary based on the arguments are weight and
height . Therefore, we’ve left them as they were in the parameterized
constructors.

*/
#include <iostream>
class Widget{
public:
    // write simplified version of constructor here
    Widget(): width(640), height(480), frame(false), visible(true) {}
    Widget(int w): width(w), height(getHeight(w)), frame(false), visible(true){}
    Widget(int w, int h): width(w), height(h), frame(false), visible(true){}
    void show()
    { 
        std::cout << std::boolalpha << width << "x" << height
        << ", frame: " << frame << ", visible: " << visible
        << std::endl;
    }
private:
    int getHeight(int w){ return w*3/4; }
    int width;
    int height;
    bool frame;
    bool visible;
};

int main()
{
    std::cout << std::endl;
    Widget wVGA;
    Widget wSVGA(800);
    Widget wHD(1280, 720);wVGA.show();
    wSVGA.show();
    wHD.show();
    std::cout << std::endl;
}