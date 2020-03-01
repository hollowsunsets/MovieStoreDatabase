#ifndef MOVIE_H
#define MOVIE_H
public:
    Movie();
    Movie(std::string director, std::string title, int year, int stock);
    virtual bool operator==(const Movie& m) const;
    virtual bool operator<(const Movie &m) const;
    virtual bool operator>(const Movie &m) const;
private:
    std::string director;
    std::string title;
    int year;
    int stock;
#endif // MOVIE_H
