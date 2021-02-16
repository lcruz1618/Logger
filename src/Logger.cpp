#include <Logger.hpp>

#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <mutex>

Logger::Logger() : m_functionallog_line_nr(1)
{
    // Clear file content
    std::ofstream log_file ("functional_log.log", std::ios::trunc);
    log_file.close();

    // Clear file content
    log_file.open ("date_log.log", std::ios::trunc);
    log_file.close();
}

Logger::~Logger()
{

}

void
Logger::Log( const std::string& input_string )
{
    std::mutex dateMutex;
    // Open output file & add it to the log's list
    std::ofstream log_file ( "date_log.log", std::ios::app );
    // m_filename_vec.push_back("date_log.log.temp");

    // Create prefix string
    std::string s_prefix ( "[" + Get_Time(true) + "] " );

    // Check if file was open successfully
    if ( log_file.is_open() )
    {
        // Lock Mutex
        std::lock_guard<std::mutex> lock(dateMutex);

        // Write the input_string & close file
        log_file << s_prefix << input_string << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file \"date_log.log\"." << std::endl;
    }
}

void
Logger::Log( const std::string& input_string,
                        const std::string& function_name )
{
    // Mutex to make the logging atomically
    std::mutex funcMutex;

    // Create and build string of the writing line (prefix + input string)
    std::string s_line ( "[" + std::to_string(m_functionallog_line_nr) + "]" );
    s_line += "[" + function_name + "] " + input_string;

    // Open output file
    std::ofstream log_file( "functional_log.log", std::ios::app );
//    m_filename_vec.push_back("functional_log.temp");

    // Check if file was open successfully
    if (log_file.is_open())
    {
        // Lock Mutex
        std::lock_guard<std::mutex> lock(funcMutex);

        // Write the input_string & close file
        log_file << s_line << std::endl;

        // Increment Line number
        m_functionallog_line_nr++;
    }
    else
    {
        std::cerr << "Unable to open file \"functional_log.log\"." << std::endl;
    }
}

void
Logger::Log_STDOUT( const std::string& input_string,
                   const std::string& function_name ) const
{
    // Create and build string of the writing line (prefix + input string)
    std::string s_line ( "[" + Get_Time(false) + "]" );
    s_line += "[" + function_name + "] " + input_string;

    // Print the string
    std::cout << s_line << std::endl;
}

void
Logger::Read(const std::string& log_filename) const
{
    // Open file
    std::ifstream log_file(log_filename);

    // Check if file was open
    if (log_file.is_open())
    {
        // If sucessfully open, iterates the file and print all even lines
        std::string line;
        for ( int i = 1; std::getline(log_file, line); ++i )
        {
            if ( i % 2 == 0)
            {
                std::cout << line << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Unable to open file \"" << log_filename << "\"." << std::endl;
    }
}

void
Logger::CountTotalLines(const std::string& log_filename) const
{
    std::ifstream log_file(log_filename);

    // Check if file was open
    if (log_file.is_open())
    {
        // If sucessfully open, count the number of lines ("\n" char)
        const int line_total = std::count( std::istreambuf_iterator<char>(log_file),
                    std::istreambuf_iterator<char>(), '\n' );

        // Print it
        std::cout << "Number of lines: " << line_total << std::endl;
    }
    else
    {
        std::cerr << "Unable to open file \"" << log_filename << "\"." << std::endl;
    }
}

std::string
Logger::Get_Time(bool date) const
{
    // Get current time & convert it to string
    auto time = std::chrono::system_clock::now();
    const std::time_t current_time( std::chrono::system_clock::to_time_t(time) );

    // If false returns time as HH:MM:SS
    if ( !date )
    {
    // Get time structure and build string
    const std::tm calendar_time = *std::localtime( std::addressof(current_time) ) ;
    std::string s_current_time( std::to_string(calendar_time.tm_hour) + ":" +
                                std::to_string(calendar_time.tm_min) + ":" +
                                std::to_string(calendar_time.tm_sec) );

    return s_current_time;
    }

    // Else it returns complete date-time format
    std::string s_current_time( std::ctime(&current_time) );

    // Substract the "\n" char from the string and format it
    s_current_time.pop_back();

    return s_current_time;
}



