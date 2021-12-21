/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "qserenityscreen.h"

QSerenityScreen::QSerenityScreen() 
        : mDepth(32), mFormat(QImage::Format_ARGB32_Premultiplied)
{
    // TODO
    mGeometry = QRect(0, 0, 1280, 1024);
    mDepth = 32;
    mFormat = QImage::Format_ARGB32_Premultiplied;
}
