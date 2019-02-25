#ifndef SHARED_EXPRESSION_MODEL_HANDLE_H
#define SHARED_EXPRESSION_MODEL_HANDLE_H

#include <poincare/context.h>
#include <poincare/expression.h>
#include <poincare/layout.h>

namespace Shared {

// ExpressionModelHandle is a handle to Ion::Record

class ExpressionModelHandle {
public:
  ExpressionModelHandle();

  // Getters
  void text(const Ion::Storage::Record * record, char * buffer, size_t bufferSize) const;
  Poincare::Expression expressionReduced(const Ion::Storage::Record * record, Poincare::Context * context) const;
  Poincare::Expression expressionClone(const Ion::Storage::Record * record) const;
  Poincare::Layout layout(const Ion::Storage::Record * record) const;

  // Setters
  virtual Ion::Storage::Record::ErrorStatus setContent(Ion::Storage::Record * record, const char * c, char symbol = 0);
  Ion::Storage::Record::ErrorStatus setExpressionContent(Ion::Storage::Record * record, Poincare::Expression & e);

  // Property
  bool isCircularlyDefined(const Ion::Storage::Record * record, Poincare::Context * context) const;
  virtual void * expressionAddress(const Ion::Storage::Record * record) const = 0;

  virtual void tidy() const;
protected:
  // Setters helper
  static Poincare::Expression BuildExpressionFromText(const char * c, char symbol = 0);
  mutable Poincare::Expression m_expression;
  mutable Poincare::Layout m_layout;
private:
  virtual size_t expressionSize(const Ion::Storage::Record * record) const = 0;
  mutable int m_circular;
};

}

#endif
