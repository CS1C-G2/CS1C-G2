#include "testimonial.h"

Testimonial::Testimonial() {
    firstName = "John";
    lastName = "Doe";
    testimonial = "";
}
Testimonial::Testimonial(string first, string last, string testimonial) :
    firstName{first}, lastName{last}, testimonial{testimonial} { }

void Testimonial::writeFile() {
    ofstream oFile;
    ifstream iFile;

    oFile.open("testimonials.txt", ios::app);
    oFile << firstName << endl
          << lastName << endl << testimonial
          << endl;
    oFile.close();
}

void Testimonial::printTestimonials(QTextEdit *textArea) {
    ifstream iFile;
    string first;
    string last;
    string testimonial;
    vector<Testimonial> testimonials;

    iFile.open("testimonials.txt");
    while(getline(iFile, first) && getline(iFile, last) && getline(iFile, testimonial)) {

        testimonials.push_back(Testimonial(first, last, testimonial));

    }

    iFile.close();
    for ( auto &testimonial: testimonials) {
        QString testimonialText = QString::fromStdString(
            testimonial.getFirst() + " " +
            testimonial.getLast() + "\n" +
            testimonial.getTestimonial() + "\n\n"
            );

        textArea->append(testimonialText);
    }
}

void Testimonial::setFirstName(string first) {
    firstName = first;
}
void Testimonial::setLastName(string last) {
    lastName = last;
}
void Testimonial::setTestimonial(string testimon) {
    testimonial = testimon;
}
string Testimonial::getFirst() {
    return firstName;
}
string Testimonial::getLast() {
    return lastName;
}
string Testimonial::getTestimonial() {
    return testimonial;
}
