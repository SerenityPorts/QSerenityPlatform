/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#define AK_DONT_REPLACE_STD

#include <AK/Forward.h>
#include <QString>

namespace QSerenityString
{
    AK::ErrorOr<AK::String> fromQString(const QString& str);
    QString toQString(const AK::String& v);
};
