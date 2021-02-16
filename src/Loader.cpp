#include <Loader.hpp>

#include <future>
#include <unordered_map>
#include <string>
#include <chrono>
#include <iostream>

Loader::Loader()
{

}

void
Loader::Manager()
{
    // Print user instructions
    PrintMenu();
    // Unordered map containing all possible options
    std::unordered_map<std::string, unsigned int> options = {
            {"fc", 0},
            {"out", 1},
            {"rdt", 2},
            {"rfc", 3},
            {"hlp", 4}
        };

    // Create future value for the async call of the processor
    std::future<void> fut_process;

    // Main loop
    while(1)
    {
        // Get user input
        std::string input;
        std::cin >> input;

        // Search for input in options map
        auto search = options.find (input);

        // If not found logs into the “date_log.log” file and STDOUT
        if ( search == options.end() )
        {
            Log.Log("Unknown Command.");
            Log.Log_STDOUT("Unknown Command.", __FUNCTION__);

            continue;
        }

        // If future is not ready yet skip loop iteration, else continues execution
        if ( fut_process.valid() &&
            ( fut_process.wait_for(std::chrono::seconds(0)) != std::future_status::ready ) &&
             ( search->second < 2 ) )
        {
            Log.Log_STDOUT("Processor class is busy.", __FUNCTION__);
            continue;
        }

        // Else it evaluates the selected option within the switch
        else
        {
            switch (search->second)
            {
                case 0:
                    fut_process = std::async( std::launch::async, &Processor::ProcessorManager, &process, search->first, std::ref(Log) );
                    break;
                case 1:
                    fut_process = std::async( std::launch::async, &Processor::ProcessorManager, &process, search->first, std::ref(Log) );
                    break;
                case 2:
                    Log.CountTotalLines("date_log.log");
                    break;
                case 3:
                    Log.Read("functional_log.log");
                    break;
                case 4:
                    PrintMenu();
                    break;
                default:
                    throw std::runtime_error("Unexpected Behaviour! @ Loader::Manager");
                    break;
            }
        }
    }
}

void
Loader::PrintMenu() const
{
    // User instructions
    std::cout << "-\"fc\": Process data. (Log to \"functional_log.log\")" << std::endl;
    std::cout << "-\"out\": Process data. (Log to STDOUT)" << std::endl;
    std::cout << "-\"rdt\": Count \"date_log.log\" entries." << std::endl;
    std::cout << "-\"rfc\": Read \"functional_log.log EVEN entries." << std::endl;
    std::cout << "-\"hlp\": Print this Menu." << std::endl;
    std::cout << "\nCTRL+C to exit...\n" << std::endl;
}
