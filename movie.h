#ifndef MOVIE_H
#define MOVIE_H

#include "item.h"

// Movies are a type of Item carried by a Store
// the Movie class defines an abstract movie
// with required fields but no groupcode
class Movie : protected Item {
 public:
  // constructor using input line format
  Movie(std::istream& s);

  // constructor using explicit parameters
  Movie(int stock, const std::string &director,
        int year, const std::string &title);

    
  // implemented suitably in Item
  // virtual bool operator<(const Item &m) const;
  // virtual bool operator>(const Item &m) const;
  // virtual bool operator==(const Item &m) const;

 protected:
  std::string director;
  std::string title;
  int year;  
};

class ComedyMovie : protected Movie {
 public:
  // Comedy Movies are sorted by Title, then Year

  std::string get_key() const;
    
  // taken care of with get_key 
  // virtual bool operator<(const Item&);
  // virtual bool operator>(const Item&);
  // virtual bool operator==(const Item&);

 protected:
  const static char typecode = 'F';
};

class DramaMovie : protected Movie {
 public:
  // Drama Movies are sorted by Director, then Title
  // return sorting key
  std::string get_key() const;

  // virtual bool operator<(const Item&);
  // virtual bool operator>(const Item&);
  // virtual bool operator==(const Item&);

 protected:
  const static char typecode = 'D';
};

// the ClassicMovie derived class
// has additional fields
class ClassicMovie : protected Movie {
 public:
  // constructor using input line format
  ClassicMovie(const std::string& s);

  // constructor using explicit parameters
  ClassicMovie(int stock, const std::string &director,
               const std::string &title, const std::string &major_actor,
               int month, int year);

  // Classic Movies are sorted by Release Date, then Major Actor
  // return sorting key
  std::string get_key() const;


  // virtual bool operator<(const Item&);
  // virtual bool operator>(const Item&);
  // virtual bool operator==(const Item&);
  
 protected:
  const static char typecode = 'C';

  std::string major_actor;
  int month;
};

#endif // MOVIE_H
