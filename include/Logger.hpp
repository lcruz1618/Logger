#pragma once

#include <string>

class Logger
{

public:
    /**
    *   @brief Default constructor for the Logger class.
    */
    Logger();

    /**
    *   @brief Default Destructor for the Logger class.
    */
    virtual ~Logger();

    /**
    *   @brief Logs a message with custom prefix
    *   @param input_string as the message to be logged
    */
    virtual void Log(const std::string& input_string);

    /**
    *   @brief Logs a message with the calling function ID as prefix
    *   @param input_string as the message to be logged
    *   @param function_name for the calling function name
    */
    virtual void Log( const std::string& input_string,
                      const std::string& function_name );

    /**
    *   @brief Logs a message with time and the calling function ID as prefix.
    *   @param input_string as the message to be logged
    *   @param function_name for the calling function name
    */
    virtual void Log_STDOUT( const std::string& input_string,
                             const std::string& function_name ) const;

    /**
    *   @brief Read even lines from file
    *   @param log_filename String with file's name
    */
    virtual void Read(const std::string& log_filename) const;

    /**
    *   @brief Count number of lines from file and write into STDOUT
    *   @param log_filename string containing file's name
    */
    virtual void CountTotalLines(const std::string& log_filename) const;

protected:
    /**
    *   @brief Get system clock current time as a string
    *   @param date True if date included otherwise just HH:MM:SS
    *   @return String containing time
    */
    std::string Get_Time(bool date) const;

private:
    // Counting "functional_log.log" file line number
    unsigned int m_functionallog_line_nr;
};
