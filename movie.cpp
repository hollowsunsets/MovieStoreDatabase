#include "movie.h"
#include <iomanip>
#include <iostream>
#include <string>

// Movie basic constructor
Movie::Movie(std::istream& s) {
    year = 0;
    std::string substr;
    std::istringstream ss;
    std::getline(s, substr, ',');
    ss.str(substr);
    ss >> stock;
    std::getline(s, director, ',');
    std::getline(s, title, ',');
    std::getline(s, substr);
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

//
// Comedy Movie
//
std::string ComedyMovie::get_key() const {
    std::ostringstream ss;
    ss << title;
    ss << std::setw(4) << year;
    return ss.str();
}

Item* ComedyMovie::create_item(std::istream& s) {
    return new ComedyMovie(s);
}

//
// Drama Movie
// 
std::string DramaMovie::get_key() const {
    return director + title;
}


Item* DramaMovie::create_item(std::istream& s) {
    return new DramaMovie(s);
}

//
// Classic Movie
// 
std::string ClassicMovie::get_key() const {
    std::ostringstream ss;
    ss << std::setw(4) << year;  // make sure these are padded
    ss << std::setw(2) << month;
    ss << title;
    return ss.str();
}

// may have bugs, watch out for comma-delimited...
// C, 10, Victor Fleming, The Wizard of Oz, Judy Garland 7 1939
ClassicMovie::ClassicMovie(std::istream& s) {
    // error handling?
    month = 0;
    std::string substr;
    std::istringstream ss;
    std::getline(s, substr, ',');
    ss.str(substr);
    ss >> stock;
    std::getline(s, director, ',');
    std::getline(s, title, ',');

    std::getline(s, substr);
    // https://stackoverflow.com/a/16509599
    // get substring until second space
    size_t pos = substr.find(' ', 0);
    pos = substr.find(' ', pos + 1);
    major_actor = substr.substr(0, pos);
    
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

Item* ClassicMovie::create_item(std::istream& s) {
    return new ClassicMovie(s);
}
