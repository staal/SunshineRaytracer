/*!
    The ´handler for commandline arguments
*/

#ifndef COMMANDLINE_HANDLER_H_
#define COMMANDLINE_HANDLER_H_

#include <string>

#include "boost/program_options/variables_map.hpp"
#include "boost/program_options/options_description.hpp"

namespace sunshine {

class CommandlineHandler {
public:
    CommandlineHandler(int argc, char *argv[]);
    ~CommandlineHandler();


    bool process(int& error);

    std::string getScene();
    std::string getOutputFile();


protected:
    boost::program_options::options_description getDescription();

private:
    boost::program_options::variables_map mVariables;
    const bool mEmptyCommandline;
};


} // namespace sunshine
#endif // !COMMANDLINE_HANDLER_H_