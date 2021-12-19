/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#define AK_DONT_REPLACE_STD

#include <QtCore/private/qstringconverter_p.h>
#include <forward_list>
#include <AK/StdLibExtraDetails.h>
#include <AK/String.h>
#include <QString>

class QSerenityString
{
public:
    static AK::String fromQString(const QString& str);
    static QString toQString(const AK::String& v);
};
