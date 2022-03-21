APP_NAME = ConnectApplication


CONFIG += qt warn_on cascades10 
LIBS += -lbb -lhuapi -lbbsystem 
device {
    CONFIG(release, debug|release) {
        DESTDIR = o.le-v7
        LIBS += -Bstatic -L../../quazip/arm/o.le-v7 -lquazip -Bdynamic
    }
 
    CONFIG(debug, debug|release) {
        DESTDIR = o.le-v7-g
        LIBS += -Bstatic -L../../quazip/arm/o.le-v7-g -lquazip -Bdynamic
    }
}
simulator {
    CONFIG(release, debug|release) {
        DESTDIR = o
        LIBS += -Bstatic -L../../quazip/x86/o-g/ -lquazip -Bdynamic 
    }
 
    CONFIG(debug, debug|release) {
        DESTDIR = o-g
        LIBS += -Bstatic -L../../quazip/x86/o-g/ -lquazip -Bdynamic
    }
}
include(config.pri)
