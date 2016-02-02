#ifndef SUNSHINE_ENGINE_OBJ_GRAMMAR_H_
#define SUNSHINE_ENGINE_OBJ_GRAMMAR_H_

#pragma warning(push)
#pragma warning(disable : 4348)
//#define BOOST_SPIRIT_QI_DEBUG
//Use Phoenix V3, defined before qi usage.
#define BOOST_SPIRIT_USE_PHOENIX_V3 1 
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>
#pragma warning(pop)

#include "mtldata.h"
#include "objdata.h"


namespace sunshine {
namespace engine {

/*!
\brief The grammar for the OBJ format.

\param Iterator the iterator type for the grammar.
Must be a forward iterator.

\param Skipper the skipper type, default type is compatible
with rule skipper in this grammar.
*/
namespace qi = boost::spirit::qi;
template <typename Iterator, typename Skipper = qi::rule<Iterator>>
struct OBJGrammar :
    qi::grammar<Iterator, void(), Skipper> {

    /*!
    Constructor, which specifies all the grammar rules according to
    boost.spirit grammar specifications. The inherited grammar is passed
    the entry rule for the grammar, startRule.

    The data is extracted through bound functions onto a ObjData object instead
    of synthesized attributes.

    \param &data a reference to the ObjData object to populate with the parsed
    data.
    */
    OBJGrammar(ObjData &data) : OBJGrammar::base_type(startRule), data(data)
    {
        using qi::char_;
        using qi::float_;
        using qi::int_;
        using qi::lexeme;
        using qi::_val;
        using boost::phoenix::at_c;

        namespace ascii = boost::spirit::ascii;
        namespace phx = boost::phoenix;

        //Bind through namespace instead of declare "using boost::phoenix::bind
        //since that wouldn't work for some reason.
        startRule = *(
            ("mtllib" >> stringRule[phx::bind(&ObjData::loadMtlLib, &data, qi::_1)]) |
            ("v" >> glmRule[phx::bind(&ObjData::addVertice, &data, qi::_1)]) |
            ("vn" >> glmRule[phx::bind(&ObjData::addNormal, &data, qi::_1)]) |
            ("f" >> multiFaceRule[phx::bind(&ObjData::addFace, &data, qi::_1)]) |
            ("usemtl" >> stringRule[phx::bind(&ObjData::useMtl, &data, qi::_1)]) |
            ("g" >> stringRule) |
            ("o" >> stringRule)
            );

        faceRule %= (
            //eps (empty parser) to set vt to 0
            //Match x//y
            (int_[at_c<0>(_val) = qi::_1] >> "//" >> 
            int_[at_c<2>(_val) = qi::_1] >> 
            qi::eps[at_c<1>(_val) = 0]) | 

            //Match x -(/y) -(/z)
            (int_[at_c<0>(_val) = qi::_1] >>
            -("/" >> int_[at_c<1>(_val) = qi::_1]) >>
            -("/" >> int_[at_c<2>(_val) = qi::_1])) 
            );

        multiFaceRule %= +faceRule;

        stringRule %= lexeme[+(char_ - qi::eol)];
        glmRule %= float_ >> float_ >> float_;

        //Skip comments and spaces/tabs including \r and \n.
        skipper = (('#' >> *(qi::char_ - qi::eol)) >> qi::eol) |
            ascii::space;

        //TODO: Add error handling

        BOOST_SPIRIT_DEBUG_NODES((stringRule)(startRule)(faceRule)(glmRule));
    };

    /*! Entry rule. */
    qi::rule<Iterator, void(), Skipper> startRule;

    /*! Face rule. Synthesizes a single ObjFaceIndices */
    qi::rule<Iterator, ObjFaceIndices(), Skipper> faceRule;

    /*! Multiple face rule, needed to ensure that the bound function addFace
    in startRule gets called with a complete vector of all face indices of a 
    line. */
    qi::rule<Iterator, std::vector<ObjFaceIndices>(), Skipper> multiFaceRule;

    /*! A simple string rule. */
    qi::rule<Iterator, std::string(), Skipper> stringRule;

    /*! A simple glm rule. */
    qi::rule<Iterator, glm::vec3(), Skipper> glmRule;

    /*! Grammar default skipper. */
    qi::rule<Iterator> skipper;

private:
    /*! The data object to be populated during parsing. */
    ObjData &data;
};



} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_GRAMMAR_H_
