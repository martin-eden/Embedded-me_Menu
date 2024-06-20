// Managing endpoints

/*
  Author: Martin Eden
  Last mod.: 2024-06-21
*/

#pragma once

#include <me_List.h>
#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // for definition of entity to match

#include "MenuItem.h"

namespace me_Menu
{
  using
    me_List::TQueue,
    me_List::TStack,
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
      // Run
      void Run();

      // Print menu list
      void Print();

      // Add builtin commands: list, exit
      TBool AddBuiltinCommands();

    protected:
      // Get entity from stdin and match it with our commands
      TBool GetSelection(TMenuItem * ItemSelected);
  };
}

/*
  2024-05-30
  2024-06-02
  2024-06-04
  2024-06-20
  2024-06-21
*/
