#include <iostream>
#include <iomanip>
#include "movie.h"

// Movie basic constructor
Movie::Movie(std::istream& s) : Item() {
    // int _stock = 0;
    s >> stock;
    // add_stock(_stock);
    s >> director;
    s >> year;
    s >> title;
}
// Movie basic constructor (explicit parameters)
Movie::Movie(int stock, const std::string &director,
             int year, const std::string &title) : Item(stock) {
    this->director = director;
    this->year = year;
    this->title = title;
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

//
// Drama Movie
// 
std::string DramaMovie::get_key() const {
    return director + title;
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
