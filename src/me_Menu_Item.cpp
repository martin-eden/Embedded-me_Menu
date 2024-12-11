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

using
  me_MemorySegment::TMemorySegment;

// Set command. Reallocates memory
TBool TCommandHandler::SetCommand(
  TMemorySegment NewCommand
)
{
  using
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
void TCommandHandler::ReleaseMemory()
{
  using
    me_MemorySegment::Freetown::Release;

  Release(&Command);
}

// Return command (design burden to complement SetCommand())
TMemorySegment TCommandHandler::GetCommand()
{
  return Command;
}

// Run handler
void TCommandHandler::RunHandler()
{
  Handler.Run();
}

// Allocate memory for structure
TBool me_Menu::CommandHandler::Allocate(
  TCommandHandler * * MenuItem
)
{
  using
    me_MemorySegment::Freetown::Reserve;

  TMemorySegment UnitSegment;

  if (!Reserve(&UnitSegment, sizeof(TCommandHandler)))
    return false;

  *MenuItem = (TCommandHandler *) UnitSegment.Addr;

  return true;
}

// Release memory of structure
void me_Menu::CommandHandler::Deallocate(
  TCommandHandler * MenuItem
)
{
  using
    me_MemorySegment::Freetown::Release,
    me_MemorySegment::Freetown::FromAddrSize;

  TMemorySegment UnitSegment =
    FromAddrSize((TUint_2) MenuItem, sizeof(TCommandHandler));

  Release(&UnitSegment);
}

// Create item from values. Allocates data memory
TBool me_Menu::CommandHandler::Create(
  TCommandHandler * * MenuItem,
  const TChar * CommandAsciiz,
  TMethod Handler,
  TUint_2 Instance
)
{
  using
    me_MemorySegment::Freetown::FromAsciiz,
    me_StoredCall::Freetown::ToStoredCall;

  if (!Allocate(MenuItem))
    return false;

  if (!(*MenuItem)->SetCommand(FromAsciiz(CommandAsciiz)))
  {
    Deallocate(*MenuItem);
    return false;
  }

  (*MenuItem)->Handler = ToStoredCall(Handler, Instance);

  return true;
}

// [Handy] Destroy item. Deallocates data memory
void me_Menu::CommandHandler::Destroy(
  TCommandHandler * MenuItem
)
{
  MenuItem->ReleaseMemory();

  Deallocate(MenuItem);
}

/*
  2024-11-29
*/
