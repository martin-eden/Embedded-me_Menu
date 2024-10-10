// Menu item class

/*
  Author: Martin Eden
  Last mod.: 2024-10-10
*/

#include "me_MenuItem.h"

#include <stdio.h> // printf()

#include <me_MemorySegment.h>
#include <me_ManagedMemory.h> // Freetown::(Reserve/Release)()

using
  me_MenuItem::TMenuItem,
  me_MemorySegment::TMemorySegment;

/*
  Release fields memory
*/
void TMenuItem::Release()
{
  Command.Release();
  Description.Release();
}

/*
  Copy data from our specie
*/
TBool TMenuItem::Set(
  TMenuItem * Src
)
{
  TBool IsFullyCopied =
    (Command.LoadFrom(Src->Command.GetData())) &&
    (Description.LoadFrom(Src->Description.GetData()));

  if (!IsFullyCopied)
  {
    // No memory to fully copy item. No partial results allowed.
    Release();
    return false;
  }

  Handler = Src->Handler;

  return true;
}

/*
  Check for equality

  Current implementation is return true when our <Command> is the same
  as in external data.

  This method is used in list Traverse() callback.
*/
TBool TMenuItem::ItsMe(
  TMemorySegment Data
)
{
  return me_MemorySegment::Freetown::AreEqual(Command.GetData(), Data);
}

/*
  Run item's handler
*/
void TMenuItem::Execute()
{
  Handler.Run();
};

/*
  Represent state
*/
void TMenuItem::PrintWrappings()
{
  using me_MemorySegment::Freetown::PrintWrappings;

  printf("[TMenuItem 0x%04X]", (TUint_2) this);
  printf(" ");
  printf("(\n");

  printf("  Command ");
  PrintWrappings(Command.GetData());
  printf("\n");

  printf("  Description ");
  PrintWrappings(Description.GetData());
  printf("\n");

  printf(")\n");
}

/*
  2024-05-25
  2024-05-29
  2024-05-30
  2024-06-02
  2024-06-15
  2024-06-23
  2024-07-06
  2024-10-05
*/
