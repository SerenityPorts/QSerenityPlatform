/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "qserenitystring.h"

#include <AK/Span.h>
#include <AK/String.h>
#include <AK/Error.h>

AK::ErrorOr<AK::String> QSerenityString::fromQString(const QString &str) {
    const auto utf8_string = str.toUtf8();
    return AK::String::from_utf8(AK::StringView(utf8_string.data(), utf8_string.size()));
}

QString QSerenityString::toQString(const AK::String &v) {
    const auto bytes = v.bytes();
    return QString::fromUtf8(reinterpret_cast<const char*>(bytes.data()), bytes.size());
}
