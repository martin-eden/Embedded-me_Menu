// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-12-15
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>

namespace me_Menu
{
  /*
    Menu item district

    Contains menu item struc and allocators.
  */
  namespace CommandHandler
  {
    /*
      Menu item

      Menu item is command (string) and handler to call.

      Menu item owns memory for command text.
      Memory should be released by calling ReleaseMemory().
    */
    struct TCommandHandler
    {
      // Command (string)
      me_MemorySegment::TMemorySegment Command;
      // Handler (pointer to method)
      me_StoredCall::TStoredCall Handler;

      // Set new command. Reallocates memory
      TBool SetCommand(me_MemorySegment::TMemorySegment NewCommand);
      // Return command
      me_MemorySegment::TMemorySegment GetCommand();
      // Run handler
      void RunHandler();
      // Release memory of all variable-length structures
      void ReleaseMemory();
    };

    // Allocate memory for structure
    TBool Allocate(
      TCommandHandler * * Unit
    );

    // Release memory of structure
    void Deallocate(
      TCommandHandler * Unit
    );

    // Create item from values. Allocates memory
    TBool Create(
      TCommandHandler * * Unit,
      TAsciiz Command,
      TMethod Handler,
      TAddress Instance
    );

    // Destroy item. Deallocates memory
    void Destroy(
      TCommandHandler * Unit
    );
  }
}

/*
  2024-05 ###
  2024-06 ####
  2024-10 #
  2024-11 #
  2024-12-11
*/
