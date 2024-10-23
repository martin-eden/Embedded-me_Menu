// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2024-10-23
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>
#include <me_List.h>
#include <me_Console.h> // for PrintWrappings()

using namespace me_Menu;

using
  me_MemorySegment::TMemorySegment,
  me_StoredCall::TStoredCall;

// ( Menu

/*
  Release memory at death
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add copy of menu item to menu

  Memory allocated here is 12 bytes:
    command seg, description seg, stored call
*/
TBool TMenu::AddItem(
  TMenuItem OuterMenuItem
)
{
  using
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::FromAddrSize,
    me_MemorySegment::Freetown::CopyMemTo,
    me_MemorySegment::Freetown::Release;

  const TUint_2 ItemStrucSize = sizeof(TMenuItem);

  TMemorySegment ItemSeg;

  // Allocate memory for copy of item structure
  if (!Reserve(&ItemSeg, ItemStrucSize))
    return false;

  // Set fields
  CopyMemTo(ItemSeg, FromAddrSize((TUint_2) &OuterMenuItem, ItemStrucSize));

  // Add address of that copy to menu list
  if (!List.Add(ItemSeg.Addr))
  {
    Release(&ItemSeg);
    return false;
  }

  return true;
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TUint_2 Data,
  TUint_2 Instance __attribute__((unused))
)
{
  Freetown::KillItem((TMenuItem *) Data);
}

/*
  Release memory of list items and the list
*/
void TMenu::Release()
{
  List.Traverse(KillItem_Handler);
  List.Release();
}

/*
  Loop of getting data and executing corresponding item for non-empty
  list.

  Yeah, empty list is the exit condition.
*/
void TMenu::Run()
{
  while (!List.IsEmpty())
  {
    TMenuItem Item;

    while(!GetCommand(&Item));

    Item.Execute();
  }
}

// ) Menu

// ( Menu item

/*
  [Debug] Represent state
*/
void TMenuItem::PrintWrappings()
{
  using
    me_MemorySegment::Freetown::PrintWrappings;

  Console.Print("Menu item");

  Console.Indent();
  Console.Print("Command");
  PrintWrappings(Command);
  Console.Unindent();

  Console.Indent();
  Console.Print("Description");
  PrintWrappings(Description);
  Console.Unindent();
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
  return me_MemorySegment::Freetown::AreEqual(Command, Data);
}

/*
  Run item's handler
*/
void TMenuItem::Execute()
{
  Handler.Run();
};

// ) Menu item

// ( Freetown

/*
  [Handy] Return item structure from arguments

  No heap allocations here.
*/
TMenuItem Freetown::ToItem(
  TMemorySegment Command,
  TMemorySegment Description,
  TStoredCall Handler
)
{
  TMenuItem Result;

  Result.Command = Command;
  Result.Description = Description;
  Result.Handler = Handler;

  return Result;
}

/*
  [Handy] Create item from list of values

  Memory allocated here depends of length of ASCIIZs.
*/
TMenuItem Freetown::ToItem(
  const TChar * Command,
  const TChar * Description,
  TMethod Handler,
  TUint_2 Instance
)
{
  using
    me_MemorySegment::Freetown::Reserve,
    me_MemorySegment::Freetown::FromAsciiz,
    me_MemorySegment::Freetown::CopyMemTo,
    me_MemorySegment::Freetown::Release,
    me_StoredCall::Freetown::ToStoredCall;

  TMenuItem Result; // I hope it is zeroed, we can return it early

  /*
    Allocate memory and copy ASCIIZ. But first we need to describe
    them as memory segments.
  */
  TMemorySegment CommandCopy;
  TMemorySegment DescriptionCopy;
  {
    TMemorySegment CommandOrig = FromAsciiz(Command);
    TMemorySegment DescriptionOrig = FromAsciiz(Description);

    if (!Reserve(&CommandCopy, CommandOrig.Size))
      return Result;
    CopyMemTo(CommandCopy, CommandOrig);

    if (!Reserve(&DescriptionCopy, DescriptionOrig.Size))
    {
      Release(&CommandCopy);
      return Result;
    }
    CopyMemTo(DescriptionCopy, DescriptionOrig);
  }

  // Using existing shortcut. Because someone should use it
  return
    ToItem(
      CommandCopy,
      DescriptionCopy,
      ToStoredCall(Handler, Instance)
    );
}

/*
  Release memory from:
    * menu item strings (variable)
    * menu item structure (12 bytes)
*/
void Freetown::KillItem(
  TMenuItem * Item
)
{
  using
    me_MemorySegment::Freetown::Release,
    me_MemorySegment::Freetown::FromAddrSize;

  // Release item strings
  Release(&Item->Command);
  Release(&Item->Description);

  // Release item structure (12 bytes)
  {
    TMemorySegment ItemSeg =
      FromAddrSize((TUint_2) Item, sizeof(TMenuItem));

    Release(&ItemSeg);
  }
}

// ) Freetown

/*
  2024-05 1
  2024-06 9
  2024-07
  2024-10-05
  2024-10-17
  2024-10-18
*/
