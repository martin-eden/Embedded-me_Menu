// "Menu" - list of (string, function pointer) items

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
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
        CommandHandler::TCommandHandler * Item
      );

      // Find item in our list by command text
      TBool FindItem(
        CommandHandler::TCommandHandler * Item,
        me_MemorySegment::TMemorySegment Name
      );

      // Print all available commands
      void PrintCommands();

      // Read command from stdin and execute corresponding item
      void Run();

      // Remove all items
      void Release();

    protected:
      // Get something like word of text from serial
      void WaitCommand(
        me_MemorySegment::TMemorySegment * Name,
        me_MemorySegment::TMemorySegment NameBuffer
      );

  };

  // Create and add item from explicit list of values
  TBool AddNewItem(
    TMenu * Menu,
    TAsciiz Command,
    TMethod Handler,
    TAddress Instance
  );

  // Add "list" command ("?" - print available commands)
  TBool AddListCommand(
    TMenu * Menu
  );

  // Add "exit" command ("^" - destroy menu items)
  TBool AddExitCommand(
    TMenu * Menu
  );

  // Add "list" and "exit" commands
  TBool AddBuiltinCommands(
    TMenu * Menu
  );
}

/*
  2024-05 ###
  2024-06 ####
  2024-10 #
  2024-11 ##
*/
