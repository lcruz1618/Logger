#pragma once

#include "Processor.hpp"
#include "Logger.hpp"

class Loader
{
public:
    /**
    *    @brief Default Constructor for the Loader class.
    */
    Loader();

    /**
    *    @brief Start listening to user inputs.
    */
    void Manager();

private:

    /**
    *    @brief Print user instructions
    */
    void PrintMenu() const;

    Processor process;

    Logger Log;
};

