#ifndef MTL_GRAMMAR_H_
#define MTL_GRAMMAR_H_

//#define BOOST_SPIRIT_QI_DEBUG
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <map>

#include "../scene/surface.h"

/*Adapt structure macros must be called on the global namespace*/
BOOST_FUSION_ADAPT_STRUCT(
    glm::vec3,
    (float, x)
    (float, y)
    (float, z)
    );

/*Only map the part of Material that is naturally occuring in mtl files*/
BOOST_FUSION_ADAPT_STRUCT(
    sunshine::engine::Material,
    (glm::vec3, Ka)
    (glm::vec3, Kd)
    (glm::vec3, Ks)
    (float, Ns)
    );


namespace sunshine {
namespace engine {

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

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


    MTLGrammar() : MTLGrammar::base_type(mtl)
    {
        using qi::char_;
        using qi::float_;
        using qi::int_;
        using qi::lexeme;
        using qi::omit;
        using boost::spirit::ascii::space;

        mtl %=
            *("newmtl" >> string_rule >> mtl_details
            );

        /*The ordering here must match the BOOST_FUSION_ADAPT_STRUCT macro above
        for Material. Omit fields to be ignored. */
        mtl_details %=
            (
            ("Ka" >> glm_rule) ^
            ("Kd" >> glm_rule) ^
            ("Ks" >> glm_rule) ^
            ("d" >> omit[float_]) ^
            ("Ns" >> float_) ^
            ("illum" >> omit[int_])
            );

        string_rule %= lexeme[+(char_ - qi::eol)];
        glm_rule %= float_ >> float_ >> float_;

        //Skip comments and spaces/tabs including \r and \n.
        skipper = (('#' >> *(qi::char_ - qi::eol)) >> qi::eol) |
            ascii::space;

        BOOST_SPIRIT_DEBUG_NODES((string_rule)(mtl));
    };

    qi::rule<Iterator, std::map<std::string, Material>(), qi::rule<Iterator>> mtl;
    qi::rule<Iterator, Material(), qi::rule<Iterator>> mtl_details;

    qi::rule<Iterator, std::string(), qi::rule<Iterator>> string_rule;
    qi::rule<Iterator, glm::vec3(), qi::rule<Iterator>> glm_rule;

    qi::rule<Iterator> skipper;
};

} // namespace engine
} // namespace sunshine
#endif // !MTL_GRAMMAR_H_
