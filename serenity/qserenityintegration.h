/****************************************************************************
/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#define AK_DONT_REPLACE_STD

#include <qpa/qplatformintegration.h>
#include <qpa/qplatformscreen.h>

#include "qserenityscreen.h"
#include "qserenitywindow.h"

#include <AK/StdLibExtraDetails.h>
#include <LibGUI/Application.h>

#include <private/qunixeventdispatcher_qpa_p.h>

#include <QTimer>

class QSerenityEventDispatcher : public QUnixEventDispatcherQPA {
    Q_OBJECT
public:
    explicit QSerenityEventDispatcher(QObject *parent = nullptr);
    ~QSerenityEventDispatcher();

private slots:
    bool processSerenityEvents();

protected:
    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

private:
};

class QSerenityIntegration : public QPlatformIntegration
{
public:
    explicit QSerenityIntegration(const QStringList &parameters);
    ~QSerenityIntegration();

    bool hasCapability(QPlatformIntegration::Capability cap) const override;
    QPlatformFontDatabase *fontDatabase() const override;

    QPlatformWindow *createPlatformWindow(QWindow *window) const override;
    QPlatformBackingStore *createPlatformBackingStore(QWindow *window) const override;
    QAbstractEventDispatcher *createEventDispatcher() const override;

    static QSerenityIntegration *instance();

private:
    mutable QPlatformFontDatabase *m_fontDatabase;
    QSerenityScreen *m_primaryScreen;
    RefPtr<GUI::Application> app;
};
