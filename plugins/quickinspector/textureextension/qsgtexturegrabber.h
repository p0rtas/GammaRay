/*
  qsgtexturegrabber.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2017 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMMARAY_QSGTEXTUREGRABBER_H
#define GAMMARAY_QSGTEXTUREGRABBER_H

#include <QMutex>
#include <QPointer>
#include <QObject>
#include <QSGTexture>

QT_BEGIN_NAMESPACE
class QMutex;
class QQuickWindow;
QT_END_NAMESPACE

namespace GammaRay {

class QSGTextureGrabber : public QObject
{
    Q_OBJECT
public:
    explicit QSGTextureGrabber(QObject *parent = nullptr);
    ~QSGTextureGrabber();

public slots:
    void objectCreated(QObject *obj);
    void requestGrab(QSGTexture *tex);
    void requestGrab(int textureId, const QSize &texSize);

signals:
    void textureGrabbed(QSGTexture *tex, const QImage &img);

private:
    void addQuickWindow(QQuickWindow *window);
    void windowAfterRendering(QQuickWindow *window);

    void resetRequest();

    QMutex m_mutex;
    QPointer<QSGTexture> m_pendingTexture;

    int m_textureId;
    QSize m_textureSize;
};
}

#endif // GAMMARAY_QSGTEXTUREGRABBER_H
