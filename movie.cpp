#include "movie.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// Movie blank constructor (e.g. because the input is different)
Movie::Movie() {
    year = 0;
}

// Movie basic constructor
Movie::Movie(std::istream& s) {
    year = 0;
    std::string substr;
    std::getline(s, substr, ',');
    std::istringstream ss(substr);

    ss >> stock;
    s.ignore(1, ' ');
    std::getline(s, director, ',');
    s.ignore(1, ' ');
    std::getline(s, title, ',');
    std::getline(s, substr);
    ss.clear();
    ss.str(substr);
    ss >> year;
}
// Movie basic constructor (explicit parameters)
Movie::Movie(int stock, const std::string &director,
             const std::string &title, int year) : Item(stock) {
    this->director = director;
    this->title = title;
    this->year = year;
}

void Movie::print(std::ostream& out) const {
    out << this->get_typecode() << ", " << this->stock << ", " << this->director;
    out << ", " << this->title << ", " << this->year;
}


//
// Comedy Movie
//
std::string ComedyMovie::get_key() const {
    std::ostringstream ss("");
    ss << title;
    ss << std::setfill('0') << std::setw(4) << year;
    return ss.str();
}

ComedyMovie* ComedyMovie::create_item(std::istream& s) {
    return new ComedyMovie(s);
}

std::string ComedyMovie::data_to_key(std::istream& data_ss) {
    // std::istringstream data_ss(data);
    std::string title;
    std::getline(data_ss, title, ',');
    std::ostringstream key(title);
    int year;
    data_ss >> year;
    key << year;
    return key.str();
}

//
// Drama Movie
// 
std::string DramaMovie::get_key() const {
    return director + title;
}

DramaMovie* DramaMovie::create_item(std::istream& s) {
    return new DramaMovie(s);
}

std::string DramaMovie::data_to_key(std::istream& data_ss) {
    //    std::istringstream data_ss(data);
    std::string director;
    std::string title;
    std::getline(data_ss, director, ',');
    data_ss.ignore(1, ' ');
    std::getline(data_ss, title, ',');
    return director + title;
}

//
// Classic Movie
// 
std::string ClassicMovie::get_key() const {
    std::ostringstream ss("");
    // make sure these are padded
    ss << std::setfill('0') << std::setw(4) << year;
    ss << std::setw(2) << month;
    ss << major_actor;
    return ss.str();
}

void ClassicMovie::print(std::ostream& out) const {
    out << this->get_typecode() << ", " << this->stock << ", " << this->director;
    out << ", " << this->title << ", " << this->major_actor << " ";
    out << this->month << " " << this->year;
}

// may have bugs, watch out for comma-delimited...
// C, 10, Victor Fleming, The Wizard of Oz, Judy Garland 7 1939
ClassicMovie::ClassicMovie(std::istream& s) {
    // error handling?
    month = 0;
    std::string substr;
    std::getline(s, substr, ',');
    std::istringstream ss(substr);
    ss >> stock;
    s.ignore(1, ' ');
    std::getline(s, director, ',');
    s.ignore(1, ' ');    
    std::getline(s, title, ',');

    s.ignore(1, ' ');
    std::getline(s, substr);
    // https://stackoverflow.com/a/16509599
    // get substring until second space
    size_t pos = substr.find(' ', 0);
    pos = substr.find(' ', pos + 1);
    major_actor = substr.substr(0, pos);
    substr = substr.substr(pos + 1); 
    ss.clear();
    ss.str(substr);
    ss >> month;
    ss >> year;
}

ClassicMovie::ClassicMovie(int stock, const std::string &director,
                           const std::string &title,
                           const std::string &major_actor,
                           int month, int year)
        : Movie(stock, director, title, year) {
    this->major_actor = major_actor;
    this->month = month;
}

ClassicMovie* ClassicMovie::create_item(std::istream& s) {
    return new ClassicMovie(s);
}

std::string ClassicMovie::data_to_key(std::istream& data_ss) {
    //    std::istringstream data_ss(data);
    int month;
    int year;
    std::string major_actor;

    data_ss >> month;
    data_ss >> year;
    data_ss.ignore(1, ' ');
    std::getline(data_ss, major_actor, ',');
    
    std::ostringstream key("");
    key << std::setfill('0') << std::setw(4) << year;
    key << std::setw(2) << month;
    key << major_actor;
    return key.str();
}
