// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-06-04
*/

#pragma once

#include <me_ManagedMemory.h>
#include <me_BaseTypes.h>

namespace me_MenuItem
{
  using
    me_ManagedMemory::TManagedMemory,
    me_BaseTypes::TBool,
    me_BaseTypes::TChar;

  /*
    Menu item

    Two strings: command and description.

    It _owns_ memory for these strings, so data is cloned by setters.
    It releases memory upon death of course.
  */
  struct TMenuItem
  {
    TManagedMemory Command;
    TManagedMemory Description;

    // Copy from our specie
    TBool Set(TMenuItem * Src);

    // Release memory of fields
    void Release();

    // Print data (production)
    void Print();

    // Print state (test/debug)
    void PrintWrappings();
    // Print [0x7389 TMenuItem] (test/debug)
    void PrintTag();
  };
}

/*
  2024-05-25
  2024-05-29
  2024-05-30 Owning memory for command and description
  2024-06-04 Memory pwnage is delegated to TManagedMemory
  2024-06-07
*/
