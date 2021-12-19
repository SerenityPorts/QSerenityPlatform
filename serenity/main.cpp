/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <qpa/qplatformintegrationplugin.h>
#include "qserenityintegration.h"

class QSerenityIntegrationPlugin : public QPlatformIntegrationPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QPlatformIntegrationFactoryInterface_iid FILE "serenity.json")
public:
    QPlatformIntegration *create(const QString&, const QStringList&) override;
};

QPlatformIntegration *QSerenityIntegrationPlugin::create(const QString& system, const QStringList& paramList)
{
    if (!system.compare(QLatin1String("serenity"), Qt::CaseInsensitive))
        return new QSerenityIntegration(paramList);

    return 0;
}

#include "main.moc"
