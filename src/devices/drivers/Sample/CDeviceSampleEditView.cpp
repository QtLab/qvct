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

// QT
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>

// QVCT
#include "QVCTRuntime.hpp"
#include "overlays/COverlayText.hpp"
#include "devices/drivers/Sample/CDeviceSample.hpp"
#include "devices/drivers/Sample/CDeviceSampleEditView.hpp"


//------------------------------------------------------------------------------
// CONSTRUCTORS / DESTRUCTOR
//------------------------------------------------------------------------------

CDeviceSampleEditView::CDeviceSampleEditView( CDeviceSample* _poDeviceSample )
  : COverlayObjectEditView( _poDeviceSample )
{
  constructLayout();
}

void CDeviceSampleEditView::constructLayout()
{
  // Create layout
  QVBoxLayout* __pqVBoxLayout = new QVBoxLayout();

  // Add header
  QFont __qFontHeader;
  __qFontHeader.setPixelSize( 16 );
  __qFontHeader.setBold( true );
  QHBoxLayout* __pqHBoxLayoutHeader = new QHBoxLayout();
  QLabel* __pqLabelIcon = new QLabel();
  __pqLabelIcon->setPixmap( QPixmap( ":icons/32x32/device.png" ) );
  __pqHBoxLayoutHeader->addWidget( __pqLabelIcon, 0, Qt::AlignTop );
  QLabel* __pqLabelEdit = new QLabel( tr("Edit")+"..." );
  __pqLabelEdit->setFont( __qFontHeader );
  __pqHBoxLayoutHeader->addWidget( __pqLabelEdit, 1 );
  // ... [end]
  __pqVBoxLayout->addLayout( __pqHBoxLayoutHeader );

  // Add data
  CDeviceSample* __poDeviceSample = (CDeviceSample*)poOverlayObject;
  QFormLayout* __pqFormLayout = new QFormLayout();
  // ... name
  COverlayText* __poTextName = new COverlayText();
  __poTextName->setText( __poDeviceSample->getName() );
  __pqFormLayout->addRow( tr("Name")+":", __poTextName );
  // ... host
  pqLineEditHost = new QLineEdit();
  pqLineEditHost->setText( __poDeviceSample->getHost() );
  __pqFormLayout->addRow( tr("Host")+":", pqLineEditHost );
  // ... port
  pqLineEditPort = new QLineEdit();
  pqLineEditPort->setText( QString::number( __poDeviceSample->getPort() ) );
  __pqFormLayout->addRow( tr("Port")+":", pqLineEditPort );
  // ... [end]
  __pqVBoxLayout->addLayout( __pqFormLayout );

  // Add buttons
  QDialogButtonBox* __pqDialogButtonBox = new QDialogButtonBox( QDialogButtonBox::Cancel|QDialogButtonBox::Save, Qt::Horizontal );
  QDialog::connect( __pqDialogButtonBox, SIGNAL(accepted()), this, SLOT(accept()) );
  QDialog::connect( __pqDialogButtonBox, SIGNAL(rejected()), this, SLOT(reject()) );
  __pqVBoxLayout->addWidget( __pqDialogButtonBox );

  // Set the layout
  COverlayObjectEditView::setLayout( __pqVBoxLayout );

}


//------------------------------------------------------------------------------
// METHODS: QDialog (override)
//------------------------------------------------------------------------------

void CDeviceSampleEditView::accept()
{
  CDeviceSample* __poDeviceSample = (CDeviceSample*)poOverlayObject;

  // Check data
  bool __bOK;
  int __iPort = -1;
  __iPort = pqLineEditPort->text().toInt( &__bOK );
  if( !__bOK || __iPort <= 0 || __iPort > 65535 )
  {
    QVCTRuntime::useMainWindow()->parseError( pqLineEditPort->text() );
    return;
  }

  // Set data
  __poDeviceSample->setOperatingMode( CDevice::STOP );
  // ... host
  __poDeviceSample->setHost( pqLineEditHost->text() );
  // ... port
  __poDeviceSample->setPort( __iPort );

  // Done
  QDialog::accept();
}
