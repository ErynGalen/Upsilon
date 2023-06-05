#include "poincare/expression_node.h"
#include <poincare/real_part.h>
#include <poincare/complex_cartesian.h>
#include <poincare/layout_helper.h>
#include <poincare/serialization_helper.h>

#include <assert.h>
#include <cmath>

namespace Poincare {

constexpr Expression::FunctionHelper RealPart::s_functionHelper;

int RealPartNode::numberOfChildren() const { return RealPart::s_functionHelper.numberOfChildren(); }

Layout RealPartNode::createLayout(Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const {
  return LayoutHelper::Prefix(RealPart(this), floatDisplayMode, numberOfSignificantDigits, RealPart::s_functionHelper.name());
}

int RealPartNode::serialize(char * buffer, int bufferSize, Preferences::PrintFloatMode floatDisplayMode, int numberOfSignificantDigits) const {
  return SerializationHelper::Prefix(this, buffer, bufferSize, floatDisplayMode, numberOfSignificantDigits, RealPart::s_functionHelper.name());
}

Expression RealPartNode::shallowReduce(ReductionContext reductionContext) {
  LOG_REDUCE(RealPart(this).shallowReduce(reductionContext));
}

Expression RealPart::shallowReduce(ExpressionNode::ReductionContext reductionContext) {
  {
    Expression e = Expression::defaultShallowReduce();
    e = e.defaultHandleUnitsInChildren();
    if (e.isUndefined()) {
      return e;
    }
  }
  Expression c = childAtIndex(0);
  if (c.type() == ExpressionNode::Type::Matrix) {
    return mapOnMatrixFirstChild(reductionContext);
  }
  if (c.isReal(reductionContext.context())) {
    replaceWithInPlace(c);
    return c;
  }
  if (c.type() == ExpressionNode::Type::ComplexCartesian) {
    ComplexCartesian complexChild = static_cast<ComplexCartesian &>(c);
    Expression r = complexChild.real();
    replaceWithInPlace(r);
    return r.shallowReduce(reductionContext);
  }
  return *this;
}

}
