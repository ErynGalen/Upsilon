#ifndef GRAPH_STORAGE_GRAPH_CONTROLLER_H
#define GRAPH_STORAGE_GRAPH_CONTROLLER_H

#include "banner_view.h"
#include "storage_curve_parameter_controller.h"
#include "storage_graph_controller_helper.h"
#include "storage_graph_view.h"
#include "../../shared/storage_function_graph_controller.h"
#include "../../shared/curve_view_cursor.h"
#include "../../shared/round_cursor_view.h"
#include "../../shared/interactive_curve_view_range.h"
#include "../storage_cartesian_function_store.h"

namespace Graph {

class StorageGraphController : public Shared::StorageFunctionGraphController<StorageCartesianFunction>, public StorageGraphControllerHelper {
public:
  StorageGraphController(Responder * parentResponder, StorageCartesianFunctionStore * functionStore, Shared::InteractiveCurveViewRange * curveViewRange, Shared::CurveViewCursor * cursor, int * indexFunctionSelectedByCursor, uint32_t * modelVersion, uint32_t * rangeVersion, Poincare::Preferences::AngleUnit * angleUnitVersion, ButtonRowController * header);
  I18n::Message emptyMessage() override;
  void viewWillAppear() override;
  bool displayDerivativeInBanner() const;
  void setDisplayDerivativeInBanner(bool displayDerivative);
  float interestingXRange() override;
private:
  void selectFunctionWithCursor(int functionIndex) override;
  BannerView * bannerView() override;
  void reloadBannerView() override;
  bool moveCursorHorizontally(int direction) override;
  Shared::InteractiveCurveViewRange * interactiveCurveViewRange() override;
  StorageCartesianFunctionStore * functionStore() const override;
  StorageGraphView * functionGraphView() override;
  View * cursorView() override {
    return &m_cursorView;
  }
  StorageCurveParameterController * curveParameterController() override;
  Shared::RoundCursorView m_cursorView;
  BannerView m_bannerView;
  StorageGraphView m_view;
  Shared::InteractiveCurveViewRange * m_graphRange;
  StorageCurveParameterController m_curveParameterController;
  StorageCartesianFunctionStore * m_functionStore;
  bool m_displayDerivativeInBanner;
};

}

#endif
