// INDENTING (emacs/vi): -*- mode:c++; tab-width:2; c-basic-offset:2; intent-tabs-mode:nil; -*- ex: set tabstop=2 expandtab:

/*
 * Qt Virtual Chart Table (QVCT)
 * Copyright (C) 2012 Cedric Dufour <http://cedric.dufour.name>
 * Author: Cedric Dufour <http://cedric.dufour.name>
 *
 * The Qt Virtual Chart Table (QVCT) is free software:
 * you can redistribute it and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation, Version 3.
 *
 * The Qt Virtual Chart Table (QVCT) is distributed in the hope
 * that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details.
 */

#ifndef QVCT_CVESSELPOSITIONDOCKVIEW_HPP
#define QVCT_CVESSELPOSITIONDOCKVIEW_HPP

// QT
#include <QBoxLayout>
#include <QDockWidget>
#include <QLabel>
#include <QWidget>

// QVCT
class COverlayObject;
class COverlayText;
class CVesselPoint;


/// [UI] Vessel position view (dock widget)
/**
 *  This class provides the user-interface (QDockWidget) that allows to display
 *  a vessel point's live position data.
 *  @author Cedric Dufour <http://cedric.dufour.name>
 */
class CVesselPositionDockView: public QDockWidget
{
  Q_OBJECT


  //------------------------------------------------------------------------------
  // FIELDS
  //------------------------------------------------------------------------------

private:
  /// [UI:Widget] Container widget
  QWidget* pqWidget;
  /// [UI:Layout] Layout
  QBoxLayout* pqBoxLayout;

  /// Overlay point being displayed
  /** @see setVesselPoint(), resetVesselPoint() */
  CVesselPoint* poVesselPoint;

  /// [UI:Label] Longitude
  COverlayText* poTextLongitude;
  /// [UI:Label] Latitude
  COverlayText* poTextLatitude;
  /// [UI:Label] Elevation
  COverlayText* poTextElevation;


  //------------------------------------------------------------------------------
  // CONSTRUCTORS / DESTRUCTOR
  //------------------------------------------------------------------------------

public:
  CVesselPositionDockView( QWidget* _pqParent );
  virtual ~CVesselPositionDockView() {};

private:
  /// Constructs the layout of the user-interface
  void constructLayout();


  //------------------------------------------------------------------------------
  // METHODS: QWidget (override)
  //------------------------------------------------------------------------------

protected slots:
  virtual void resizeEvent( QResizeEvent* _pqResizeEvent );


  //------------------------------------------------------------------------------
  // METHODS
  //------------------------------------------------------------------------------

  // SLOTS
private slots:
  /// Slot to handle object destruction
  void slotDestroyed( QObject* _pqObject );

private slots:
  /// Slot to handle dock area change
  void slotLocationChanged( Qt::DockWidgetArea _qDockWidgetArea );
  /// Slot to handle floating change
  void slotTopLevelChanged( bool _bTopLevel );

  // SETTERS
public:
  /// Sets the overlay point to be displayed (and refreshes the underlying widget)
  void setVesselPoint( CVesselPoint* _poVesselPoint );
  /// Resets (clears) the overlay point being displayed (and clears the underlying widget)
  void resetVesselPoint();

  // OTHER
public:
  /// Refreshes the content of the underlying widget
  void refreshContent();

};

#endif // QVCT_CVESSELPOSITIONDOCKVIEW_HPP