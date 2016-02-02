#ifndef SUNSHINE_CL_COMMANDLINE_HANDLER_H_
#define SUNSHINE_CL_COMMANDLINE_HANDLER_H_

#include <string>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>

namespace sunshine {
namespace cl {

/*!
    \brief The handler for commandline arguments.
*/
class CommandlineHandler {
public:
    /*!
        Handles the commandline passed through \param argc and \param argv
    */
    CommandlineHandler(int argc, char *argv[]);

    /*!
        Default destructor
    */
    ~CommandlineHandler() = default;

    /*!
        Validates the commandline. If the function returns false
        \param errorCode is set to the exit code of the program.
    */
    bool validate(int& errorCode);

    /*!
        Returns the scene file passed in on the commandline.
    */
    std::string getScene();

    /*!
        Returns the output path for the resulting image rendered.
        \return Empty string if output is missing from the commandline,
        otherwise the path set.
    */
    std::string getOutputFile();

    /*!
        \return True if -v or --version was requested.
    */
    bool printVersion();


protected:
    /*!
        The commandline description used to parse the arguments and print
        the help message.

        \return The commandline description.
    */
    boost::program_options::options_description getDescription();

private:
    /*! False if no arguments is passed on the commandline. */
    const bool mEmptyCommandline;

    /*! The program name, argv[0] on the commandline. */
    const std::string mProgramName;

    /*! The parsed argumentline variables map. */
    boost::program_options::variables_map mVariables;
};

} // namespace cl
} // namespace sunshine
#endif // !SUNSHINE_CL_COMMANDLINE_HANDLER_H_