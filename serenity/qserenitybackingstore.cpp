/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "qserenitybackingstore.h"
#include "qserenityintegration.h"
#include "qscreen.h"
#include <QtCore/qdebug.h>
#include <qpa/qplatformscreen.h>
#include <QGuiApplication>

#include <iostream>
#include <cstdlib>

QSerenityBackingStore::QSerenityBackingStore(QWindow *window)
    : QPlatformBackingStore(window)

{
}

QSerenityBackingStore::~QSerenityBackingStore()
{
}

QPaintDevice *QSerenityBackingStore::paintDevice()
{
    return &mImage;
}

void QSerenityBackingStore::flush(QWindow *window, const QRegion &region, const QPoint &offset)
{
    Q_UNUSED(window);
    Q_UNUSED(region);
    Q_UNUSED(offset);

    QPlatformWindow *platformWindow = this->window()->handle();
    QSerenityWindow *qSerenityWindow = dynamic_cast<QSerenityWindow*>(platformWindow);

    auto proxyWidget = qSerenityWindow->proxyWidget();

    for (auto &r : region) {
        for (int i = offset.x() + r.left(); i < mImage.width() && i < offset.x() + r.right(); i++) {
            for (int j = offset.y() + r.top(); j < mImage.height() && j < offset.y() + r.bottom(); j++) {
                auto currentColor = mImage.pixel(i, j);
                proxyWidget->m_buffer->set_pixel(i, j, Gfx::Color(currentColor >> 16 & 0xFF, currentColor >> 8 & 0xFF, currentColor & 0xFF));
            }
        }
        proxyWidget->update(Gfx::IntRect(r.x() + offset.x(), r.y() + offset.y(), r.width(), r.height()));
    }
}

void QSerenityBackingStore::resize(const QSize &size, const QRegion &)
{
    QPlatformWindow *platformWindow = window()->handle();
    QSerenityWindow *qSerenityWindow = dynamic_cast<QSerenityWindow*>(platformWindow);

    auto proxyWidget = qSerenityWindow->proxyWidget();

    QImage::Format format = QGuiApplication::primaryScreen()->handle()->format();
    if (mImage.size() != size) {
        mImage = QImage(size, format);
        proxyWidget->m_buffer = Gfx::Bitmap::create(Gfx::BitmapFormat::BGRx8888, Gfx::IntSize(window()->width(), window()->height())).value();
        proxyWidget->m_buffer->set_volatile();
        proxyWidget->resize(Gfx::IntSize(size.width(), size.height()));
        proxyWidget->update();
    }
}
