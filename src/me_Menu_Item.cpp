// Menu item methods implementation

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
*/

#include "me_Menu_Item.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>

using namespace me_Menu::Unit;

/*
TUnit
{
  TMemorySegment Command;
  TStoredCall Handler;

  TBool SetCommand(TMemorySegment NewCommand);
  void ReleaseMemory();
  TMemorySegment GetCommand();
  void Execute();
};
*/

// Allocate memory for structure
TBool me_Menu::Unit::Allocate(
  TUnit * * Unit
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Reserve;

  TMemorySegment UnitSegment;

  if (!Reserve(&UnitSegment, sizeof(TUnit)))
    return false;

  *Unit = (TUnit *) UnitSegment.Addr;

  return true;
}

// Release memory of structure
void me_Menu::Unit::Deallocate(
  TUnit * Unit
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Release,
    me_MemorySegment::Freetown::FromAddrSize;

  TMemorySegment UnitSegment =
    FromAddrSize((TUint_2) Unit, sizeof(TUnit));

  Release(&UnitSegment);
}

// ( TUnit

// Set command. Reallocates memory
TBool me_Menu::Unit::TUnit::SetCommand(
  me_MemorySegment::TMemorySegment NewCommand
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::CopyMemTo,
    me_MemorySegment::Freetown::Release;

  TMemorySegment NewCommandCopy;

  if (!Reserve(&NewCommandCopy, NewCommand.Size))
    return false;

  CopyMemTo(NewCommandCopy, NewCommand);

  Release(&Command);

  Command = NewCommandCopy;

  return true;
}

// Release memory used by data
void me_Menu::Unit::TUnit::ReleaseMemory()
{
  using
    me_MemorySegment::Freetown::Release;

  Release(&Command);
}

// Return command
me_MemorySegment::TMemorySegment me_Menu::Unit::TUnit::GetCommand()
{
  return Command;
}

// Run handler
void me_Menu::Unit::TUnit::Execute()
{
  Handler.Run();
}

// ) TUnit

// [Handy] Create item from values. Allocates data memory
TBool me_Menu::Unit::Create(
  TUnit * * Unit,
  const TChar * CommandAsciiz,
  TMethod Handler,
  TUint_2 Instance
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz,
    me_StoredCall::Freetown::ToStoredCall;

  if (!Allocate(Unit))
    return false;

  if (!(*Unit)->SetCommand(FromAsciiz(CommandAsciiz)))
  {
    Deallocate(*Unit);
    return false;
  }

  (*Unit)->Handler = ToStoredCall(Handler, Instance);

  return true;
}

// [Handy] Destroy item. Deallocates data memory
void me_Menu::Unit::Destroy(
  TUnit * Unit
)
{
  Unit->ReleaseMemory();

  Deallocate(Unit);
}

/*
  2024-11-29
*/
