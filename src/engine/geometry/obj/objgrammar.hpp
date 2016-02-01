#ifndef SUNSHINE_ENGINE_OBJ_GRAMMAR_H_
#define SUNSHINE_ENGINE_OBJ_GRAMMAR_H_

//#define BOOST_SPIRIT_QI_DEBUG
#define BOOST_SPIRIT_USE_PHOENIX_V3 1
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_bind.hpp>

#include "../material.h"
#include "objdata.h"


namespace sunshine {
namespace engine {


namespace qi = boost::spirit::qi;
template <typename Iterator>
struct OBJGrammar :
    qi::grammar<Iterator, void(), qi::rule<Iterator>> {

    void useMtl(const std::string &s) {}

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
            (int_[at_c<0>(_val) = qi::_1] >> "//" >> 
            int_[at_c<2>(_val) = qi::_1] >> qi::eps[at_c<1>(_val) = 0]) | //Match x//y
            (int_[at_c<0>(_val) = qi::_1] >>
            -("/" >> int_[at_c<1>(_val) = qi::_1]) >>
            -("/" >> int_[at_c<2>(_val) = qi::_1])) //Match x -(/y) -(/z)
            );

        multiFaceRule %= +faceRule;

        stringRule %= lexeme[+(char_ - qi::eol)];
        glmRule %= float_ >> float_ >> float_;

        //Skip comments and spaces/tabs including \r and \n.
        skipper = (('#' >> *(qi::char_ - qi::eol)) >> qi::eol) |
            ascii::space;

        BOOST_SPIRIT_DEBUG_NODES((stringRule)(startRule)(faceRule)(glmRule));
    };
    qi::rule<Iterator, void(), qi::rule<Iterator>> startRule;
    qi::rule<Iterator, ObjFaceIndices(), qi::rule<Iterator>> faceRule;
    qi::rule<Iterator, std::vector<ObjFaceIndices>(), qi::rule<Iterator>>
        multiFaceRule;

    qi::rule<Iterator, std::string(), qi::rule<Iterator>> stringRule;
    qi::rule<Iterator, glm::vec3(), qi::rule<Iterator>> glmRule;

    qi::rule<Iterator> skipper;

private:
    ObjData &data;
};



} // namespace engine
} // namespace sunshine
#endif // !SUNSHINE_ENGINE_OBJ_GRAMMAR_H_
