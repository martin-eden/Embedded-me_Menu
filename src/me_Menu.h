// Managing endpoints

/*
  Author: Martin Eden
  Last mod.: 2024-10-18
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
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
    me_MemorySegment::TMemorySegment Command;
    me_MemorySegment::TMemorySegment Description;
    me_StoredCall::TStoredCall Handler;

    // [Debug] Print state
    void PrintWrappings();

    // Return true when <.Command> == <Data>
    TBool ItsMe(
      me_MemorySegment::TMemorySegment Data
    );

    // Run item handler
    void Execute();
  };

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

      // Add copy of menu item to menu
      TBool AddItem(
        TMenuItem MenuItem
      );

      // Add builtin commands: list, exit
      TBool AddBuiltinCommands();

      // Remove all items
      void Release();

      // Print menu list
      void Print();

      // Read command from stdin and execute corresponding item
      void Run();

    protected:
      // Get entity from stdin and match it with our commands
      TBool GetCommand(
        TMenuItem * ItemSelected
      );

      // Add "print menu" ("?") command
      TBool AddListCommand();

      // Add "exit" ("^") command
      TBool AddExitCommand();
  };

  namespace Freetown
  {
    // Set fields in one call
    TMenuItem ToItem(
      me_MemorySegment::TMemorySegment Command,
      me_MemorySegment::TMemorySegment Description,
      me_StoredCall::TStoredCall Handler
    );

    // Create item from values. Allocates memory
    TMenuItem ToItem(
      const TChar * Command,
      const TChar * Description,
      TMethod Handler,
      TUint_2 Instance
    );

    // Allocate mem for structure
    TBool SpawnItem(
      TMenuItem * * Item
    );

    // Release derived memory and struc
    void KillItem(
      TMenuItem * Item
    );
  }
}

/*
  2024-05 3
  2024-06 4
  2024-10-18
*/
