#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"

// Movies are a type of Item carried by a Store
// the Movie class defines an abstract movie
// with required fields but no groupcode
class Movie : public Item {
  public:
    Movie();
   
    // constructor using input line format
    Movie(std::istream& s);

    // constructor using explicit parameters
    Movie(int stock, const std::string &director,
          const std::string &title, int year);

    virtual void print(std::ostream& out) const;
    
    virtual char get_typecode() const = 0;
        
    // implemented suitably in Item
    // virtual bool operator<(const Item &m) const;
    // virtual bool operator>(const Item &m) const;
    // virtual bool operator==(const Item &m) const;

  protected:
    std::string director;
    std::string title;
    int year;  
};

class ComedyMovie : public Movie {
  public:
    ComedyMovie(std::istream& s) : Movie(s){};
    
    char get_typecode() const { return 'F'; }
    
    // Comedy Movies are sorted by Title, then Year
    std::string get_key() const;

    static ComedyMovie* create_item(std::istream& s);
    static std::string data_to_key(std::istream& data_ss);

  protected:
};

class DramaMovie : public Movie {
  public:
    DramaMovie(std::istream& s) : Movie(s){};

    char get_typecode() const { return 'D'; }
    // Drama Movies are sorted by Director, then Title
    // return sorting key
    std::string get_key() const;

    static DramaMovie* create_item(std::istream& s);
    static std::string data_to_key(std::istream& data_ss);

  protected:
};

// the ClassicMovie derived class
// has additional fields
class ClassicMovie : public Movie {
  public:
    // constructor using input line format
    ClassicMovie(std::istream& s);

    // constructor using explicit parameters
    ClassicMovie(int stock, const std::string &director,
                 const std::string &title, const std::string &major_actor,
                 int month, int year);

    void print(std::ostream& out) const;
    
    char get_typecode() const { return 'C'; }

    // Classic Movies are sorted by Release Date, then Major Actor
    // return sorting key
    std::string get_key() const;

    static ClassicMovie* create_item(std::istream& s);
    static std::string data_to_key(std::istream& data_ss);
    
  protected:
    std::string major_actor;
    int month;
};

#endif // MOVIE_H
