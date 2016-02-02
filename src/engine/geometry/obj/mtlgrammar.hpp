#ifndef SUNSHINE_ENGINE_MTL_GRAMMAR_H_
#define SUNSHINE_ENGINE_MTL_GRAMMAR_H_

#include <map>

#pragma warning(push)
#pragma warning(disable : 4348)
//#define BOOST_SPIRIT_QI_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#pragma warning(pop)

#include "mtldata.h"



namespace sunshine {
namespace engine {

namespace qi = boost::spirit::qi;

/*!
    \brief The grammar for MTL files, material files associated with OBJ format.

    Format of Wavefront MTL files:
    \code
    newmtl ShortBox
    Ka  0.6 0.6 0.6
    Kd  0.5 0.5 0.5
    Ks  0 0 0
    d  1
    Ns  0
    illum 2
    # Comment
    ...
    \endcode

    \param Iterator the iterator type for the grammar. 
    Must be a forward iterator.

    \param Skipper the skipper type, default type is compatible 
    with rule skipper in this grammar.
*/
template <typename Iterator, typename Skipper = qi::rule<Iterator>>
struct MTLGrammar :
    qi::grammar<Iterator, MtlMaterials(), Skipper> {

    /*!
        Constructor, which specifies all the grammar rules according to 
        boost.spirit grammar specifications. The inherited grammar is passed
        the entry rule for the grammar, startRule.
    */
    MTLGrammar() : MTLGrammar::base_type(startRule)
    {
        using qi::char_;
        using qi::float_;
        using qi::int_;
        using qi::lexeme;
        using qi::omit;

        namespace ascii = boost::spirit::ascii;

        startRule %=
            *("newmtl" >> stringRule >> mtlDetailRule
            );

        //The ordering here must match the BOOST_FUSION_ADAPT_STRUCT macro
        //defined for Material (in its header). Omit fields to be ignored.
        mtlDetailRule %=
            (
            ("Ka" >> glmRule) ^
            ("Kd" >> glmRule) ^
            ("Ks" >> glmRule) ^
            ("d" >> float_) ^
            ("Tr" >> float_) ^
            ("Ns" >> float_) ^
            ("illum" >> int_)
            );

        stringRule %= lexeme[+(char_ - qi::eol)];
        glmRule %= float_ >> float_ >> float_;

        //Skip comments and spaces/tabs including \r and \n.
        skipper = (('#' >> *(qi::char_ - qi::eol)) >> qi::eol) |
            ascii::space;

        //TODO: Add error handling

        BOOST_SPIRIT_DEBUG_NODES((stringRule)(startRule));
    };

    /*! 
        Entry rule, specifies the attribute type of the grammar, a map of 
        strings and associated Material.
    */
    qi::rule<Iterator, MtlMaterials(), Skipper> startRule;

    /*! Material rule, attribute is a complete Material. */
    qi::rule<Iterator, MtlData(), Skipper> mtlDetailRule;

    /*! Simple string match rule */
    qi::rule<Iterator, std::string(), Skipper> stringRule;

    /*! Simple glm::vec3 match rule */
    qi::rule<Iterator, glm::vec3(), Skipper> glmRule;

    /*! Grammar default skipper. */
    qi::rule<Iterator> skipper;
};

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_MTL_GRAMMAR_H_