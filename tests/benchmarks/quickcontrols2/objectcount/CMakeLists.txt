# Generated from objectcount.pro.

#####################################################################
## tst_objectcount Test:
#####################################################################

qt_internal_add_test(tst_objectcount
    SOURCES
        ../../../auto/quickcontrols2/shared/qtest_quickcontrols.h
        ../../../auto/quickcontrols2/shared/util.cpp ../../../auto/quickcontrols2/shared/util.h
        ../../../auto/quickcontrols2/shared/visualtestutil.cpp ../../../auto/quickcontrols2/shared/visualtestutil.h
        tst_objectcount.cpp
    DEFINES
        QQC2_IMPORT_PATH=\\\"${CMAKE_CURRENT_SOURCE_DIR}/../../../../src\\\"
    PUBLIC_LIBRARIES
        Qt::CorePrivate
        Qt::Gui
        Qt::GuiPrivate
        Qt::QmlPrivate
        Qt::Quick
        Qt::QuickControls2
        Qt::QuickControls2Private
        Qt::QuickPrivate
        Qt::QuickTemplates2Private
        Qt::QuickTest
        Qt::TestPrivate
)

#### Keys ignored in scope 1:.:.:objectcount.pro:<TRUE>:
# TEMPLATE = "app"

## Scopes:
#####################################################################

qt_internal_extend_target(tst_objectcount CONDITION ANDROID OR IOS
    DEFINES
        QT_QMLTEST_DATADIR=\\\":/data\\\"
)

qt_internal_extend_target(tst_objectcount CONDITION NOT ANDROID AND NOT IOS
    DEFINES
        QT_QMLTEST_DATADIR=\\\"${CMAKE_CURRENT_SOURCE_DIR}/data\\\"
)
