/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the Qt Quick Controls 2 module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL3$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPLv3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or later as published by the Free
** Software Foundation and appearing in the file LICENSE.GPL included in
** the packaging of this file. Please review the following information to
** ensure the GNU General Public License version 2.0 requirements will be
** met: http://www.gnu.org/licenses/gpl-2.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtCore/private/qfileselector_p.h>
#include <QtCore/qloggingcategory.h>
#include <QtQml/qqmlengine.h>
#include <QtQml/qqmlextensionplugin.h>
#include <QtQuickTemplates2/private/qquicktheme_p_p.h>
#include <QtQuickControls2/private/qquickstyle_p.h>
#include <QtQuickControls2/private/qquickstyleplugin_p.h>
#include <QtQuickControls2/qquickstyle.h>

QT_BEGIN_NAMESPACE

Q_LOGGING_CATEGORY(lcQtQuickControlsStylePlugin, "qt.quick.controls.qtquickcontrols2plugin")

class QtQuickControls2Plugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    QtQuickControls2Plugin(QObject *parent = nullptr);
    ~QtQuickControls2Plugin();

    void registerTypes(const char *uri) override;
    void unregisterTypes() override;

private:
    QQuickTheme *createTheme(const QString &name);

    // We store these because the style plugins can be unregistered before
    // QtQuickControls2Plugin, and since QQuickStylePlugin calls QQuickStylePrivate::reset(),
    // the style information can be lost when it comes time to call qmlUnregisterModuleImport().
    // It also avoids unnecessarily resolving the style after resetting it just to get the style
    // name in unregisterTypes().
    bool customStyle = false;
    QString registeredStyleUri;
    QString registeredFallbackStyleUri;
};

static const char *qtQuickControlsUri = "QtQuick.Controls";

QString styleUri()
{
    const QString style = QQuickStyle::name();
    if (!QQuickStylePrivate::isCustomStyle()) {
        // The style set is a built-in style.
        const QString styleName = QQuickStylePrivate::effectiveStyleName(style);
        return QString::fromLatin1("QtQuick.Controls.%1").arg(styleName);
    }

    // This is a custom style, so just use the name as the import uri.
    QString styleName = style;
    if (styleName.startsWith(QLatin1String(":/")))
        styleName.remove(0, 2);
    return styleName;
}

QString fallbackStyleUri()
{
    // The fallback style must be a built-in style, so we don't need to check for custom styles here.
    const QString fallbackStyle = QQuickStylePrivate::fallbackStyle();
    const QString fallbackStyleName = QQuickStylePrivate::effectiveStyleName(fallbackStyle);
    return QString::fromLatin1("QtQuick.Controls.%1").arg(fallbackStyleName);
}

QtQuickControls2Plugin::QtQuickControls2Plugin(QObject *parent) : QQmlExtensionPlugin(parent)
{
}

QtQuickControls2Plugin::~QtQuickControls2Plugin()
{
    // Intentionally empty: we use register/unregisterTypes() to do
    // initialization and cleanup, as plugins are not unloaded on macOS.
}

void QtQuickControls2Plugin::registerTypes(const char *uri)
{
    qCDebug(lcQtQuickControlsStylePlugin) << "registerTypes() called with uri" << uri;

    // It's OK that the style is resolved more than once; some accessors like name() cause it to be called, for example.
    QQuickStylePrivate::init();

    const QString styleName = QQuickStylePrivate::effectiveStyleName(QQuickStyle::name());
    const QString fallbackStyleName = QQuickStylePrivate::effectiveStyleName(QQuickStylePrivate::fallbackStyle());
    qCDebug(lcQtQuickControlsStylePlugin) << "style:" << QQuickStyle::name() << "effective style:" << styleName
        << "fallback style:" << QQuickStylePrivate::fallbackStyle() << "effective fallback style:" << fallbackStyleName;

    createTheme(styleName);

    // If the style is Basic, we don't need to register the fallback because the Basic style
    // provides all controls. Also, if we didn't return early here, we can get an infinite import loop
    // when the style is set to Basic.
    if (styleName != fallbackStyleName && styleName != QLatin1String("Basic")) {
        registeredFallbackStyleUri = ::fallbackStyleUri();
        qCDebug(lcQtQuickControlsStylePlugin) << "calling qmlRegisterModuleImport() to register fallback style with"
            << " uri \"" << qtQuickControlsUri << "\" moduleMajor" << QQmlModuleImportModuleAny
            << "import" << registeredFallbackStyleUri << "importMajor" << QQmlModuleImportAuto;
        // The fallback style must be a built-in style, so we match the version number.
        qmlRegisterModuleImport(qtQuickControlsUri, QQmlModuleImportModuleAny, registeredFallbackStyleUri.toUtf8().constData(),
            QQmlModuleImportAuto, QQmlModuleImportAuto);
    }

    // If the user imports QtQuick.Controls 2.15, and they're using the Material style, we should import version 2.15.
    // However, if they import QtQuick.Controls 2.15, but are using a custom style, we want to use the latest version
    // number of their style.
    customStyle = QQuickStylePrivate::isCustomStyle();
    registeredStyleUri = ::styleUri();
    const int importMajor = !customStyle ? QQmlModuleImportAuto : QQmlModuleImportLatest;
    qCDebug(lcQtQuickControlsStylePlugin).nospace() << "calling qmlRegisterModuleImport() to register primary style with"
        << " uri \"" << qtQuickControlsUri << "\" moduleMajor " << importMajor
        << " import " << registeredStyleUri << " importMajor " << importMajor;
    qmlRegisterModuleImport(qtQuickControlsUri, QQmlModuleImportModuleAny, registeredStyleUri.toUtf8().constData(), importMajor);

    const QString style = QQuickStyle::name();
    if (!style.isEmpty())
        QFileSelectorPrivate::addStatics(QStringList() << style);
}

void QtQuickControls2Plugin::unregisterTypes()
{
    qCDebug(lcQtQuickControlsStylePlugin) << "unregisterTypes() called";

    if (!registeredFallbackStyleUri.isEmpty()) {
        // We registered a fallback style, so now we need to unregister it.
        qmlUnregisterModuleImport(qtQuickControlsUri, QQmlModuleImportModuleAny, registeredFallbackStyleUri.toUtf8().constData(),
            QQmlModuleImportAuto, QQmlModuleImportAuto);
        registeredFallbackStyleUri.clear();
    }

    const int importMajor = !customStyle ? QQmlModuleImportAuto : QQmlModuleImportLatest;
    qmlUnregisterModuleImport(qtQuickControlsUri, QQmlModuleImportModuleAny, registeredStyleUri.toUtf8().constData(), importMajor);
    customStyle = false;
    registeredStyleUri.clear();

    QQuickThemePrivate::instance.reset();
    QQuickStylePrivate::reset();
}

/*!
    \internal

    Responsible for setting the font and palette settings that were specified in the
    qtquickcontrols2.conf file.

    Style-specific settings (e.g. Variant=Dense) are read in the constructor of the
    appropriate style plugin (e.g. QtQuickControls2MaterialStylePlugin).

    Implicit style-specific font and palette values are assigned in the relevant theme
    (e.g. QQuickMaterialTheme).
*/
QQuickTheme *QtQuickControls2Plugin::createTheme(const QString &name)
{
    qCDebug(lcQtQuickControlsStylePlugin) << "creating QQuickTheme instance to be initialized by style-specific theme of" << name;

    QQuickTheme *theme = new QQuickTheme;
#if QT_CONFIG(settings)
    QQuickThemePrivate *p = QQuickThemePrivate::get(theme);
    QSharedPointer<QSettings> settings = QQuickStylePrivate::settings(name);
    if (settings) {
        p->defaultFont.reset(QQuickStylePrivate::readFont(settings));
        // Set the default font as the System scope, because that's what
        // QQuickControlPrivate::parentFont() uses as its fallback if no
        // parent item has a font explicitly set. QQuickControlPrivate::parentFont()
        // is used as the starting point for font inheritance/resolution.
        // The same goes for palettes below.
        theme->setFont(QQuickTheme::System, *p->defaultFont);

        p->defaultPalette.reset(QQuickStylePrivate::readPalette(settings));
        theme->setPalette(QQuickTheme::System, *p->defaultPalette);
    }
#endif
    QQuickThemePrivate::instance.reset(theme);
    return theme;
}

QT_END_NAMESPACE

#include "qtquickcontrols2plugin.moc"
