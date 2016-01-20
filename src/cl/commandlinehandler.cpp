#include <iostream>

#include <boost/filesystem/path.hpp>
#include <boost/program_options/parsers.hpp>

#include "commandlinehandler.h"


namespace sunshine {
namespace cl {


using namespace boost::program_options;

//Constants
const char* inputArgument = "input-scene";
const char* outputArgument = "output-scene";


// *****************************************************************************
boost::program_options::options_description CommandlineHandler::getDescription()
{
    //Add shorthand value to the arguments
    std::string input = std::string(inputArgument) + std::string(",i");
    std::string output = std::string(outputArgument) + std::string(",o");

    //Construct the commandline description
    options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Show this help message.")
        ("version,v", "Show the version number of the engine")
        (input.c_str(), value<std::string>(), "Scene file to render.")
        (output.c_str(), value<std::string>(), "Output image path.")
        ;

    return desc;
}


// *****************************************************************************
CommandlineHandler::CommandlineHandler(int argc, char * argv[])
    : mEmptyCommandline(argc <= 1), mVariables(variables_map()),
    mProgramName(argv[0])
{
    //Create positional argument for inputArgument, meaning you don't need
    //to pass it as -i foo, but simply foo.
    positional_options_description positionalDesc;
    positionalDesc.add(inputArgument, 1);

    //Parse the command line
    command_line_parser clp(argc, argv);
    store(
        clp.options(getDescription()).positional(positionalDesc).run(),
        mVariables
        );
}


// *****************************************************************************
CommandlineHandler::~CommandlineHandler()
{}


// *****************************************************************************
bool CommandlineHandler::validate(int & errorCode)
{
    if (mVariables.count("help") || mEmptyCommandline) {
        namespace bf = boost::filesystem;

        //Output help message
        bf::path p(mProgramName);
        std::cout << "Usage: \""
            << p.filename().string()
            << " [options] input.scene\""
            << std::endl;
        std::cout << getDescription();

        //It's an error if the commandline is empty. But a successful program
        //if the help command was requested.
        if (mEmptyCommandline) {
            errorCode = 1;
        } else {
            errorCode = 0;
        }
        return false;
    }

    if (mVariables.count(inputArgument) == 0) {
        std::cout << "Please supply a .scene file" << std::endl;
        errorCode = 1;
        return false;
    }

    return true;
}


// *****************************************************************************
std::string CommandlineHandler::getScene()
{
    if (mVariables.count(inputArgument)) {
        return mVariables[inputArgument].as<std::string>();
    }
    throw std::runtime_error("Could not find option "
        + std::string(inputArgument));
}


// *****************************************************************************
std::string CommandlineHandler::getOutputFile()
{
    if (mVariables.count(outputArgument)) {
        return mVariables[outputArgument].as<std::string>();
    }
    return std::string("");
}


// *****************************************************************************
bool CommandlineHandler::printVersion()
{
    return mVariables.count("version") > 0;
}

} // namespace cl
} // namespace sunshine