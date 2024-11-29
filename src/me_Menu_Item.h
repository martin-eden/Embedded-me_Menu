// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-11-29
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
  namespace Unit
  {
    /*
      Menu item

      Menu item is command (string) and handler to call.

      Menu item owns data memory. Memory should be released by
      calling ReleaseMemory().
    */
    struct TUnit
    {
      // [Data]

      // Command (string)
      me_MemorySegment::TMemorySegment Command;

      // Handler (pointer to method)
      me_StoredCall::TStoredCall Handler;

      // [Management]

      // Set new command. Reallocates memory
      TBool SetCommand(me_MemorySegment::TMemorySegment NewCommand);

      // Release memory of all variable-length structures
      void ReleaseMemory();

      // [Handy]

      // Return command
      me_MemorySegment::TMemorySegment GetCommand();

      // Run handler
      void Execute();
    };

    // Allocate memory for structure
    TBool Allocate(
      TUnit * * Unit
    );

    // Release memory of structure
    void Deallocate(
      TUnit * Unit
    );

    // [Handy] Create item from values. Allocates memory
    TBool Create(
      TUnit * * Unit,
      const TChar * Command,
      TMethod Handler,
      TUint_2 Instance
    );

    // [Handy] Destroy item. Deallocates memory
    void Destroy(
      TUnit * Unit
    );
  }
}

/*
  2024-05 3
  2024-06 4
  2024-10
  2024-11-29
*/
