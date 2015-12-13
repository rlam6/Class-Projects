
#ifndef KEYPRESSINTERACTIONREADER_HPP
#define KEYPRESSINTERACTIONREADER_HPP

#include "InteractionReader.hpp"
#include "KeypressReader.hpp"



class KeypressInteractionReader : public InteractionReader
{
public:
    explicit KeypressInteractionReader(KeypressReader& keypressReader)
        : keypressReader{keypressReader}
    {
    }


    virtual Interaction nextInteraction();


private:
    KeypressReader& keypressReader;
};



#endif // KEYPRESSINTERACTIONREADER_HPP

