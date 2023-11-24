#-------------------------------------------------
#
# Project created by QtCreator 2020-09-02T22:09:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = logo.ico

TARGET = PeachDemo
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    cglobal.cpp \
    data_define.cpp \
    dialog_delete_data.cpp \
    dialog_gen_data.cpp \
    disk_manager.cpp \
    disk_monitor.cpp \
    folder_manager.cpp \
    gendatathread.cpp \
        main.cpp \
    memory_manager.cpp \
    memory_monitor.cpp \
    systemwindow.cpp \
    user.cpp \
        widget.cpp \
    appinit.cpp \
    mymessagebox.cpp \
    window_exe_data.cpp

HEADERS += \
    cereal/access.hpp \
    cereal/archives/adapters.hpp \
    cereal/archives/binary.hpp \
    cereal/archives/json.hpp \
    cereal/archives/portable_binary.hpp \
    cereal/archives/xml.hpp \
    cereal/cereal.hpp \
    cereal/details/helpers.hpp \
    cereal/details/polymorphic_impl.hpp \
    cereal/details/polymorphic_impl_fwd.hpp \
    cereal/details/static_object.hpp \
    cereal/details/traits.hpp \
    cereal/details/util.hpp \
    cereal/external/base64.hpp \
    cereal/external/rapidjson/allocators.h \
    cereal/external/rapidjson/cursorstreamwrapper.h \
    cereal/external/rapidjson/document.h \
    cereal/external/rapidjson/encodedstream.h \
    cereal/external/rapidjson/encodings.h \
    cereal/external/rapidjson/error/en.h \
    cereal/external/rapidjson/error/error.h \
    cereal/external/rapidjson/filereadstream.h \
    cereal/external/rapidjson/filewritestream.h \
    cereal/external/rapidjson/fwd.h \
    cereal/external/rapidjson/internal/biginteger.h \
    cereal/external/rapidjson/internal/diyfp.h \
    cereal/external/rapidjson/internal/dtoa.h \
    cereal/external/rapidjson/internal/ieee754.h \
    cereal/external/rapidjson/internal/itoa.h \
    cereal/external/rapidjson/internal/meta.h \
    cereal/external/rapidjson/internal/pow10.h \
    cereal/external/rapidjson/internal/regex.h \
    cereal/external/rapidjson/internal/stack.h \
    cereal/external/rapidjson/internal/strfunc.h \
    cereal/external/rapidjson/internal/strtod.h \
    cereal/external/rapidjson/internal/swap.h \
    cereal/external/rapidjson/istreamwrapper.h \
    cereal/external/rapidjson/memorybuffer.h \
    cereal/external/rapidjson/memorystream.h \
    cereal/external/rapidjson/msinttypes/inttypes.h \
    cereal/external/rapidjson/msinttypes/stdint.h \
    cereal/external/rapidjson/ostreamwrapper.h \
    cereal/external/rapidjson/pointer.h \
    cereal/external/rapidjson/prettywriter.h \
    cereal/external/rapidjson/rapidjson.h \
    cereal/external/rapidjson/reader.h \
    cereal/external/rapidjson/schema.h \
    cereal/external/rapidjson/stream.h \
    cereal/external/rapidjson/stringbuffer.h \
    cereal/external/rapidjson/writer.h \
    cereal/external/rapidxml/rapidxml.hpp \
    cereal/external/rapidxml/rapidxml_iterators.hpp \
    cereal/external/rapidxml/rapidxml_print.hpp \
    cereal/external/rapidxml/rapidxml_utils.hpp \
    cereal/macros.hpp \
    cereal/specialize.hpp \
    cereal/types/array.hpp \
    cereal/types/atomic.hpp \
    cereal/types/base_class.hpp \
    cereal/types/bitset.hpp \
    cereal/types/boost_variant.hpp \
    cereal/types/chrono.hpp \
    cereal/types/common.hpp \
    cereal/types/complex.hpp \
    cereal/types/concepts/pair_associative_container.hpp \
    cereal/types/deque.hpp \
    cereal/types/forward_list.hpp \
    cereal/types/functional.hpp \
    cereal/types/list.hpp \
    cereal/types/map.hpp \
    cereal/types/memory.hpp \
    cereal/types/optional.hpp \
    cereal/types/polymorphic.hpp \
    cereal/types/queue.hpp \
    cereal/types/set.hpp \
    cereal/types/stack.hpp \
    cereal/types/string.hpp \
    cereal/types/tuple.hpp \
    cereal/types/unordered_map.hpp \
    cereal/types/unordered_set.hpp \
    cereal/types/utility.hpp \
    cereal/types/valarray.hpp \
    cereal/types/variant.hpp \
    cereal/types/vector.hpp \
    cereal/version.hpp \
    cglobal.h \
    data_define.h \
    dialog_delete_data.h \
    dialog_gen_data.h \
    disk_manager.h \
    disk_monitor.h \
    folder_manager.h \
    gendatathread.h \
    memory_manager.h \
    memory_monitor.h \
    systemwindow.h \
    user.h \
        widget.h \
    appinit.h \
    mymessagebox.h \
    window_exe_data.h

FORMS += \
    dialog_delete_data.ui \
    dialog_gen_data.ui \
    disk_monitor.ui \
    memory_monitor.ui \
    systemwindow.ui \
        widget.ui \
    mymessagebox.ui \
    window_exe_data.ui

RESOURCES += \
    qss.qrc \
    qss.qrc

DISTFILES += \
    .idea/encodings.xml \
    .idea/vcs.xml \
    .vscode/c_cpp_properties.json \
    cereal/external/rapidxml/license.txt \
    cereal/external/rapidxml/manual.html \
    css/index.css \
    icons/analysic.png \
    icons/check.png \
    icons/close.png \
    icons/down.png \
    icons/error.png \
    icons/home.png \
    icons/item_01.png \
    icons/item_02.png \
    icons/logo.png \
    icons/logout.png \
    icons/member.png \
    icons/mine.png \
    icons/mini.png \
    icons/modular.png \
    icons/money.png \
    icons/out.png \
    icons/phone.png \
    icons/question.png \
    icons/setting.png \
    icons/show.png \
    icons/umbrella.png \
    icons/up.png \
    icons/warn.png \
    logo.ico

SUBDIRS += \
    OperatingSystem.pro
