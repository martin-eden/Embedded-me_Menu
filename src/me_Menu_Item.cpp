// Menu item methods implementation

/*
  Author: Martin Eden
  Last mod.: 2024-12-11
*/

#include "me_Menu_Item.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>

using namespace me_Menu::CommandHandler;

/*
TCommandHandler
{
  TMemorySegment Command
  TStoredCall Handler
}
*/

// Allocate memory for structure
TBool me_Menu::CommandHandler::Allocate(
  TCommandHandler * * Unit
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Reserve;

  TMemorySegment UnitSegment;

  if (!Reserve(&UnitSegment, sizeof(TCommandHandler)))
    return false;

  *Unit = (TCommandHandler *) UnitSegment.Addr;

  return true;
}

// Release memory of structure
void me_Menu::CommandHandler::Deallocate(
  TCommandHandler * Unit
)
{
  using
    me_MemorySegment::TMemorySegment,
    me_MemorySegment::Freetown::Release,
    me_MemorySegment::Freetown::FromAddrSize;

  TMemorySegment UnitSegment =
    FromAddrSize((TUint_2) Unit, sizeof(TCommandHandler));

  Release(&UnitSegment);
}

// ( TCommandHandler

// Set command. Reallocates memory
TBool me_Menu::CommandHandler::TCommandHandler::SetCommand(
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
void me_Menu::CommandHandler::TCommandHandler::ReleaseMemory()
{
  using
    me_MemorySegment::Freetown::Release;

  Release(&Command);
}

/*
  Return command

  Design burden to complement SetCommand().
*/
me_MemorySegment::TMemorySegment me_Menu::CommandHandler::TCommandHandler::GetCommand()
{
  return Command;
}

// Run handler
void me_Menu::CommandHandler::TCommandHandler::RunHandler()
{
  Handler.Run();
}

// ) TCommandHandler

// [Handy] Create item from values. Allocates data memory
TBool me_Menu::CommandHandler::Create(
  TCommandHandler * * Unit,
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
void me_Menu::CommandHandler::Destroy(
  TCommandHandler * Unit
)
{
  Unit->ReleaseMemory();

  Deallocate(Unit);
}

/*
  2024-11-29
*/
