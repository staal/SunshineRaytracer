#ifndef SUNSHINE_ENGINE_MTL_GRAMMAR_H_
#define SUNSHINE_ENGINE_MTL_GRAMMAR_H_

//#define BOOST_SPIRIT_QI_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <map>

#include "../surface.h"
#include "../material.h"



namespace sunshine {
namespace engine {

namespace qi = boost::spirit::qi;

/*
Format of Wavefront MTL files:
newmtl ShortBox
Ka  0.6 0.6 0.6
Kd  0.5 0.5 0.5
Ks  0 0 0
d  1
Ns  0
illum 2
# Comment
...
*/
template <typename Iterator>
struct MTLGrammar :
    qi::grammar<Iterator, std::map<std::string, Material>(), qi::rule<Iterator>> {


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

        /*The ordering here must match the BOOST_FUSION_ADAPT_STRUCT macro above
        for Material. Omit fields to be ignored. */
        mtlDetailRule %=
            (
            ("Ka" >> glmRule) ^
            ("Kd" >> glmRule) ^
            ("Ks" >> glmRule) ^
            ("d" >> omit[float_]) ^
            ("Ns" >> float_) ^
            ("illum" >> omit[int_])
            );

        stringRule %= lexeme[+(char_ - qi::eol)];
        glmRule %= float_ >> float_ >> float_;

        //Skip comments and spaces/tabs including \r and \n.
        skipper = (('#' >> *(qi::char_ - qi::eol)) >> qi::eol) |
            ascii::space;

        BOOST_SPIRIT_DEBUG_NODES((stringRule)(startRule));
    };

    qi::rule<Iterator, std::map<std::string, Material>(), qi::rule<Iterator>> 
        startRule;
    qi::rule<Iterator, Material(), qi::rule<Iterator>> mtlDetailRule;

    qi::rule<Iterator, std::string(), qi::rule<Iterator>> stringRule;
    qi::rule<Iterator, glm::vec3(), qi::rule<Iterator>> glmRule;

    qi::rule<Iterator> skipper;
};

} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_MTL_GRAMMAR_H_
