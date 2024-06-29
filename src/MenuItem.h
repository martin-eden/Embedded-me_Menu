// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-06-29
*/

#pragma once

#include <me_ManagedMemory.h> // for .Command and .Description
#include <me_StoredCall.h> // for .Handler
#include <me_BaseTypes.h>

namespace me_MenuItem
{
  using
    me_ManagedMemory::TManagedMemory,
    me_StoredCall::TStoredCall,
    me_BaseTypes::TBool;

  /*
    Menu item

    Two strings (command and description) and stored handler to call.

    It _owns_ memory for strings, so data is cloned by setters.
    It releases memory upon death of course.
  */
  struct TMenuItem
  {
    TManagedMemory Command;
    TManagedMemory Description;
    TStoredCall Handler;

    // Copy from our specie
    TBool Set(TMenuItem * Src);
    // Run item handler
    void Execute();
    // Release memory of fields
    void Release();

    // [debug] Print state
    void PrintWrappings();
  };

  // Allocate mem for struc and clone from
  TBool SpawnItem(TMenuItem * * Item, TMenuItem * Value);
  // Release derived memory and struc
  void KillItem(TMenuItem * Item);
}

/*
  2024-05-25
  2024-05-29
  2024-05-30 Owning memory for command and description
  2024-06-04 Memory pwnage is delegated to TManagedMemory
  2024-06-07
  2024-06-16 TMenuItem.Method
*/
