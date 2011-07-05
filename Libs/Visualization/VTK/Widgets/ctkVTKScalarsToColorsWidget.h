/*=========================================================================

  Library:   CTK

  Copyright (c) Kitware Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkVTKScalarsToColorsWidget_h
#define __ctkVTKScalarsToColorsWidget_h

//Qt includes
#include <QWidget>

// CTK includes
#include <ctkVTKObject.h>
#include "ctkVisualizationVTKWidgetsExport.h"
class ctkVTKScalarsToColorsView;
class ctkVTKScalarsToColorsWidgetPrivate;

// VTK includes
class vtkControlPointsItem;
class vtkPlot;

class CTK_VISUALIZATION_VTK_WIDGETS_EXPORT ctkVTKScalarsToColorsWidget : public QWidget
{
  Q_OBJECT
  QVTK_OBJECT
  Q_PROPERTY(bool horizontalSliderVisible READ isHorizontalSliderVisible WRITE setHorizontalSliderVisible)
  Q_PROPERTY(bool verticalSliderVisible READ isVerticalSliderVisible WRITE setVerticalSliderVisible)
  Q_PROPERTY(bool editColors READ editColors WRITE setEditColors)
public:
  ctkVTKScalarsToColorsWidget(QWidget* parent = 0);
  virtual ~ctkVTKScalarsToColorsWidget();

  ctkVTKScalarsToColorsView* view()const;
  vtkControlPointsItem* currentControlPointsItem()const;

  bool isHorizontalSliderVisible()const;
  void setHorizontalSliderVisible(bool visible);

  bool isVerticalSliderVisible()const;
  void setVerticalSliderVisible(bool visible);
  
  bool editColors()const;
  void setEditColors(bool edit);

public slots:
  void setCurrentControlPointsItem(vtkControlPointsItem* item);
  void setCurrentPoint(int pointId);

protected slots:
  void onPlotAdded(vtkPlot*);
  void onBoundsChanged();
  void setCurrentPoint(vtkObject* controlPointsItem, void* pointId);
  void updateCurrentPoint();
  void onCurrentPointChanged(int pointId);
  void onColorChanged(const QColor& color);
  void onOpacityChanged(double opacity);
  void onMidPointChanged(double midPoint);
  void onSharpnessChanged(double sharpness);
  void onXRangeChanged(double min, double max);
  void onYRangeChanged(double min, double max);
  void onAxesModified();
protected:
  QScopedPointer<ctkVTKScalarsToColorsWidgetPrivate> d_ptr;

private:
  Q_DECLARE_PRIVATE(ctkVTKScalarsToColorsWidget);
  Q_DISABLE_COPY(ctkVTKScalarsToColorsWidget);
};

#endif
