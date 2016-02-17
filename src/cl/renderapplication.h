#ifndef SUNSHINE_CL_RENDER_APPLICATION_H_
#define SUNSHINE_CL_RENDER_APPLICATION_H_

#include "commandlinehandler.h"

namespace sunshine {
namespace cl {


/*!
    \brief The main application class.

    The command line application using the sunshine render engine.
*/
class RenderApplication {
public:
    /*!
        \param handler which is responsible for handling the
        commandline itself.
    */
    RenderApplication(CommandlineHandler  handler);


    /*!
        Processes the commandline and handle the response, including rendering
    */
    int run();


private:
    //! Processes command line, including malformed formats
    CommandlineHandler mCommandlineHandler;
};


} // namespace cl
} // namespace sunshine
#endif // !SUNSHINE_CL_RENDER_APPLICATION_H_