/*
 * Copyright (c) 2021, the SerenityOS developers.
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#define AK_DONT_REPLACE_STD

#include <qpa/qplatformwindow.h>

#include <LibCore/EventLoop.h>
#include <LibGUI/Application.h>
#include <LibGUI/Painter.h>
#include <LibGUI/Widget.h>
#include <LibGUI/Window.h>
#include <LibGfx/Bitmap.h>

#include "qserenitystring.h"

namespace GUI
{
    class Window;
}

class QSerenityWindow;

class SerenityProxyWidget : public GUI::Widget
{
    C_OBJECT(SerenityProxyWidget)
public:
    explicit SerenityProxyWidget(QSerenityWindow*);
    RefPtr<Gfx::Bitmap> m_buffer;

protected:
    void paint_event(GUI::PaintEvent&) override;
    void resize_event(GUI::ResizeEvent&) override;
    void show_event(GUI::ShowEvent&) override;
    void hide_event(GUI::HideEvent&) override;

    void mousedown_event(GUI::MouseEvent&) override;
    void mousemove_event(GUI::MouseEvent&) override;
    void mouseup_event(GUI::MouseEvent&) override;

    void keydown_event(GUI::KeyEvent& event) override;
    void keyup_event(GUI::KeyEvent& event) override;

    void enter_event(Core::Event&) override;
    void leave_event(Core::Event&) override;

private:
    QSerenityWindow* m_qtWindow = nullptr;
};

class QSerenityWindow : public QPlatformWindow
{
public:
    QSerenityWindow(QWindow* window);

    virtual void setWindowTitle(const QString& text) override;
    virtual QRect geometry() const override;

    SerenityProxyWidget* proxyWidget() { return m_proxyWidget; }

private:
    GUI::Window* w;
    NonnullRefPtr<GUI::Window> m_window;
    NonnullRefPtr<SerenityProxyWidget> m_proxyWidget;
};
