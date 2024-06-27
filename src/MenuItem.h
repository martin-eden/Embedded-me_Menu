// Menu item

/*
  Author: Martin Eden
  Last mod.: 2024-06-27
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
    me_BaseTypes::TUint_2,
    me_BaseTypes::TMethod;

  /*
    Delayed method call

    Store handler now, call it later.

    It's out of place here, just sketching.
  */
  class TMethodCall
  {
    TMethod Method;
    TUint_2 State;

    public:
      TMethodCall(): Method(0), State(0) {};
      void Set(TMethod Method, TUint_2 State)
      {
        this->Method = Method;
        this->State = State;
      }
      void Run(TUint_2 Data = 0)
      {
        Method(Data, State);
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
