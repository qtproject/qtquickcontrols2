#####################################################################
## qtquickcontrols2windowsstyleplugin Plugin:
#####################################################################

set(qml_files
    "Button.qml"
    "CheckBox.qml"
    "ComboBox.qml"
    "Frame.qml"
    "GroupBox.qml"
    "ProgressBar.qml"
    "RadioButton.qml"
    "Slider.qml"
    "SpinBox.qml"
    "TextArea.qml"
    "TextField.qml"
    "ScrollBar.qml"
    "ScrollView.qml"
)
set_source_files_properties(${qml_files} PROPERTIES
    QT_QML_SOURCE_VERSION "2.0;6.0"
)

qt_internal_add_qml_module(qtquickcontrols2windowsstyleplugin
    URI "QtQuick.Controls.Windows"
    VERSION "${PROJECT_VERSION}"
    CLASS_NAME QtQuickControls2WindowsStylePlugin
    IMPORTS
        QtQuick.Controls.Fusion/auto
    PAST_MAJOR_VERSIONS 2
    PLUGIN_TARGET qtquickcontrols2windowsstyleplugin
    NO_PLUGIN_OPTIONAL
    NO_GENERATE_PLUGIN_SOURCE
    SOURCES
        qtquickcontrols2windowsstyleplugin.cpp
    QML_FILES
        ${qml_files}
    DEFINES
        QT_NO_CAST_FROM_ASCII
        QT_NO_CAST_TO_ASCII
    LIBRARIES
        Qt::CorePrivate
        Qt::GuiPrivate
        Qt::QmlPrivate
        Qt::QuickControls2Private
        Qt::QuickPrivate
        Qt::QuickTemplates2Private
)
