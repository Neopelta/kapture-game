#ifndef OBSTACLE_H
#define OBSTACLE_H



class obstacle {
    short unsigned int costToQuit;
public:
    obstacle();
    virtual ~obstacle() = default;
    short unsigned int operator*() const;
    obstacle &operator()(short unsigned int value);
};



#endif
