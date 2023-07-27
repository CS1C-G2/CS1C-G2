#ifndef TESTIMONIAL_H
#define TESTIMONIAL_H
using namespace std;
#include <string>
#include <QTextEdit>
#include <fstream>

class Testimonial {
public:
    Testimonial();
    Testimonial(string first, string last, string testimonial);

    void writeFile();

    void printTestimonials(QTextEdit *textArea);

    void setFirstName(string first);
    void setLastName(string last);
    void setTestimonial(string testimon);
    string getFirst();
    string getLast();
    string getTestimonial();

private:
    string firstName;
    string lastName;
    string testimonial;
};
#endif // TESTIMONIAL_H
