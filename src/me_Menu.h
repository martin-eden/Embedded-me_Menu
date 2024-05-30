// WIP. Menu navigation

/*
  Author: Martin Eden
  Last mod.: 2024-05-30
*/

#pragma once

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>

namespace me_MenuItem
{
  using
    me_MemorySegment::TMemorySegment,
    me_BaseTypes::TBool;

  /*
    Menu item.

    Two strings: command and description.

    It _owns_ memory for these strings, so data is cloned by setters.
    It releases memory upon death of course.
  */
  struct TMenuItem
  {
    TMemorySegment Command;
    TMemorySegment Description;

    // Sets fields to data copy of segments
    TMenuItem(
      TMemorySegment OuterCommand,
      TMemorySegment OuterDescription
    );
    // Release memory upon death
    ~TMenuItem();

    // Set .Command to memory copy of argument
    TBool SetCommand(TMemorySegment OuterCommand);
    // Set .Description to memory copy of argument
    TBool SetDescription(TMemorySegment OuterDescription);

    // Print data (production)
    void Print();
    // Print state (test/debug)
    void PrintWrappings();
  };
}

/*
  2024-05-25
  2024-05-29
  2024-05-30 Owning memory for command and description
*/
