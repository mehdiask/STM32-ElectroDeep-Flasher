TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = Core \
          CLI \
          GUI

CLI.depends = Core
GUI.depends = Core

Core.file = Core/Core.pro
Core.depends =

CLI.file = CLI/CLI.pro
CLI.depends = Core

GUI.file = GUI/GUI.pro
GUI.depends = Core
