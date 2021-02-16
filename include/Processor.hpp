#pragma once

#include "Logger.hpp"

class Processor
{
public:
    /**
    *    @brief Default constructor for the Processor class.
    */
    Processor();

    /**
    *    @brief Interface function, calls Simulate function depending on log_type parameter
    *    @param log_type If "fc" calls SimulateA if "out" calls SimulateB
    *    @return Bool that is true if available, false if busy
    */
    void ProcessorManager( const std::string& log_type, Logger& Log );


private:
    /**
    *    @brief Simulate data processing by putting the thread to sleep (1-3s) and log to "functional_log.log
    *    @details Uses 32-bit Mersenne Twister Engine by Matsumoto and Nishimura, 1998
    *    @param log_type If "fc": functional logging; if "out": STDOUT logging
    *
    */
    void SimulateA();

    /**
    *    @brief Simulate data processing by putting the thread to sleep (1-3s) and log to STDOUT
    *    @details Uses Linear Congruential Engine by Park, Miller, and Stockmeyer, 1993
    *    @param log_type If "fc": functional logging; if "out": STDOUT logging
    */
    void SimulateB();
};
