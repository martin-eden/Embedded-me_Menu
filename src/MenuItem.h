// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-06-23
*/

#pragma once

#include <me_ManagedMemory.h>
#include <me_BaseTypes.h>

#include <stdio.h>

namespace me_MenuItem
{
  using
    me_ManagedMemory::TManagedMemory,
    me_BaseTypes::TBool,
    me_BaseTypes::TUint_2;

  /*
    Method call

    Storage and execution class.

    It's out of place here, just sketching.
  */
  class TMethodCall
  {
    TUint_2 DataAddr;
    TUint_2 MethodAddr;

    public:
      TMethodCall(): DataAddr(0), MethodAddr(0) {};
      void Set(TUint_2 DataAddr, TUint_2 MethodAddr)
      {
        this->DataAddr = DataAddr;
        this->MethodAddr = MethodAddr;
      }
      void Run()
      {
        if (DataAddr == 0) return;
        typedef void (*TMethod) (TUint_2 DataAddr);
        TMethod Method = (TMethod) MethodAddr;
        Method(DataAddr);
      }
  };

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
    TMethodCall Method;

    // Copy from our specie
    TBool Set(TMenuItem * Src);
    // [debug] Print state
    void PrintWrappings();
    // Run item handler
    void Execute() { Method.Run(); };
    // Release memory of fields
    void Release();
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
