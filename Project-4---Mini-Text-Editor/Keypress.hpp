
// DO NOT MODIFY THIS FILE
// THIS FILE BELONGS TO THE ICS INSTRUCTOR - ALEX THORNTON

#ifndef KEYPRESS_HPP
#define KEYPRESS_HPP



class Keypress
{
public:
    static Keypress ctrl(char code) { return Keypress{code, true}; }
    static Keypress normal(char code) { return Keypress{code, false}; }

public:
    char code() const { return code_; }
    bool ctrl() const { return ctrl_; }

private:
    Keypress(char code, bool ctrl)
        : code_{code}, ctrl_{ctrl}
    {
    }

private:
    char code_;
    bool ctrl_;
};



#endif // KEYPRESS_HPP

