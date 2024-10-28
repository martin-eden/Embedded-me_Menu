#!/bin/bash

# Uninstall library
arduino-cli lib uninstall me_Menu

# Uninstall dependencies
arduino-cli lib uninstall \
  me_StoredCall \
  me_List \
  me_Console \
  me_SerialTokenizer \
  me_MemorySegment \
  me_Uart \
  me_UartSpeeds \
  me_BaseTypes
