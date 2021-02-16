#include <Processor.hpp>

#include <thread>
#include <iostream>
#include <chrono>
#include <random>
#include <string>

Processor::Processor()
{

}

void
Processor::ProcessorManager( const std::string& log_type, Logger& Log )
{
    // Get the starting timepoint
    auto start = std::chrono::high_resolution_clock::now();

    Log.Log_STDOUT("Processor called...", __FUNCTION__);
    Log.Log("Processor called...", __FUNCTION__);
    Log.Log("Processor called...");
    if ( log_type ==  "fc")
    {
        SimulateA();
        // Logging
        Log.Log("Executed some data.", __FUNCTION__);
    }
    else if ( log_type == "out" )
    {
        SimulateB();
        // Logging
        Log.Log_STDOUT("Executed some data.", __FUNCTION__);
    }
    else
    {
        std::cerr << "log_type mismatch!! @ Processor::ProcessSomething" << std::endl;
    }

     // Get the ending timepoint
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate delta
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Build String
    const std::string waited_time
        ( "Took " + std::to_string( elapsed.count() ) + "ms to process." );

    // Log to STDOUT and "functional_log.log"
    Log.Log_STDOUT(waited_time, __FUNCTION__);
    Log.Log(waited_time, __FUNCTION__);
}

void
Processor::SimulateA()
{

    // Construct a random generator engine (Mersenne Twister 19937) from a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);

    // Define a real uniform distribuiton to feed the generator
    std::uniform_real_distribution<float> distribution(1,3);

    // Generate random number (1000-3000)
    float t = distribution(generator) * (float)1000;

    // Put the thread sleeping for the number of ms generated
    std::this_thread::sleep_for( std::chrono_literals::operator""ms(t) );
}

void
Processor::SimulateB(  )
{
    // Construct a random generator engine from a time-based seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::minstd_rand generator (seed);

    // Define a real uniform distribuiton to feed the generator
    std::uniform_real_distribution<float> distribution(1,3);

    // Generate random number
    float t = distribution(generator) * (float)1000;

    // Put the thread sleeping for the number of ms generated
    std::this_thread::sleep_for( std::chrono_literals::operator""ms(t) );
}
