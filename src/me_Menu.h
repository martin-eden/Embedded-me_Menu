// Managing endpoints

/*
  Author: Martin Eden
  Last mod.: 2024-06-21
*/

#pragma once

#include <me_List.h>
#include <me_BaseTypes.h>

#include "MenuItem.h"

namespace me_Menu
{
  using
    me_List::TQueue,
    me_BaseTypes::TBool,
    me_MenuItem::TMenuItem;

  class TMenu
  {
    TQueue List;

    public:
      ~TMenu();

      // Add item
      TBool Add(TMenuItem * MenuItem);
      // Remove all items
      void Release();
      // Print menu list
      void Print();
      // Add builtin commands: list, exit
      TBool AddBuiltinCommands();
      // Run
      void Run();

    protected:
      // Get entity from stdin and match it with our commands
      TBool GetCommand(TMenuItem * ItemSelected);
      // Add "list" ("?") command
      TBool AddListCommand();
      // Add "exit" ("^") command
      TBool AddExitCommand();
  };
}

/*
  2024-05-30
  2024-06-02
  2024-06-04
  2024-06-20
  2024-06-21
*/
