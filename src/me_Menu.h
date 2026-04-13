// Managing endpoints

/*
  Author: Martin Eden
  Last mod.: 2026-04-13
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_StoredCall.h>
#include <me_List.h>

namespace me_Menu
{
  /*
    Menu item

    Two strings (command and description) and stored handler to call.
  */
  struct TMenuItem
  {
    TAddressSegment Command;
    TAddressSegment Description;
    me_StoredCall::TStoredCall Handler;

    // Return true when <.Command> == <Data>
    TBool ItsMe(TAddressSegment);

    // Run item handler
    void Execute();
  };

  /*
    Menu

    Menu is a list of items.

    Main method is Run(). It is loop of reading command from stdin,
    finding item by command name and executing it. Exit condition is
    empty items list which may be reached by executing "exit" command.
  */
  class TMenu
  {
    private:
      me_List::TQueue List;

    public:
      ~TMenu();

      // Add copy of menu item to menu
      TBool AddItem(TMenuItem);

      // Add builtin commands: list, exit
      TBool AddBuiltinCommands();

      // Execute given command
      TBool RunCommand(TAddressSegment);

      // [Internal] Print menu list
      void Print();

      // Execute "Print()" as standard menu item
      void RunListCommand();

      // Read command from stdin and execute corresponding item
      void Run();

      // Remove all items
      void Release();

    protected:
      // Find menu item by command
      TBool GetMenuItem(TMenuItem *, TAddressSegment);

      // Get entity from stdin and match it with our commands
      TBool GetCommand(TMenuItem *);

      // Add "print menu" ("?") command
      TBool AddListCommand();

      // Add "exit" ("^") command
      TBool AddExitCommand();
  };

  namespace Freetown
  {
    // Set fields in one call
    TMenuItem ToItem(
      TAddressSegment Command,
      TAddressSegment Description,
      me_StoredCall::TStoredCall Handler
    );

    // Create item from values. Allocates memory
    TMenuItem ToItem(
      const TAsciiz Command,
      const TAsciiz Description,
      TCallback Method,
      TAddress Instance
    );

    // Allocate mem for structure
    TBool SpawnItem(TMenuItem **);

    // Release derived memory and struc
    void KillItem(TMenuItem *);
  }
}

/*
  2024 # # # # # # # #
*/
