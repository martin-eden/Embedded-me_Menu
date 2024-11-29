// "Menu" - list of (string, function pointer) items

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_List.h>

#include "me_Menu_Item.h" // Menu item

namespace me_Menu
{
  /*
    Menu

    Menu is a list of items.

    Main method is Run(). It is loop of reading command from stdin,
    finding item by command name and executing it. Exit condition is
    empty items list which may be done by "builtin" "exit" command.
  */
  class TMenu
  {
    private:
      me_List::TQueue List;

    public:
      ~TMenu();

      // Add menu item
      TBool AddItem(
        Unit::TUnit * Item
      );

      // [Handy] Create and add item from explicit list of values
      TBool CreateAndAddItem(
        const TChar * Command,
        TMethod Handler,
        TUint_2 Instance
      );

      // [Handy] Add builtin commands: "? - list" and "^ - exit"
      TBool AddBuiltinCommands();

      // [Handy] Print menu list
      void Print();

      // Read command from stdin and execute corresponding item
      void Run();

      // Remove all items
      void Release();

    protected:
      // Get entity from stdin and match it with our commands
      TBool GetCommand(
        Unit::TUnit * ItemSelected
      );

      // Add "print menu" ("?") command
      TBool AddListCommand();

      // Add "exit" ("^") command
      TBool AddExitCommand();
  };
}

/*
  2024-05 ###
  2024-06 ####
  2024-10 #
  2024-11 ##
*/
