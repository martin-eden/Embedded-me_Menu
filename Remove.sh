#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_Menu

# Uninstall dependencies
arduino-cli lib uninstall \
  me_UartSpeeds \
  me_InstallStandardStreams \
  me_SerialTokenizer \
  me_List \
  me_MemorySegment \
  me_BaseTypes
