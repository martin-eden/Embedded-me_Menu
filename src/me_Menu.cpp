// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2025-08-29
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_StoredCall.h>
#include <me_List.h>

using namespace me_Menu;

using
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
    me_MemorySegment::Freetown::CopyMemTo,
    me_MemorySegment::Freetown::Release;

  const TUint_2 ItemStrucSize = sizeof(TMenuItem);

  TAddressSegment ItemSeg;

  // Allocate memory for copy of item structure
  if (!Reserve(&ItemSeg, ItemStrucSize))
    return false;

  // Set fields
  CopyMemTo(
    ItemSeg,
    { .Addr = (TAddress) &OuterMenuItem, .Size = ItemStrucSize }
  );

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
  TMenuItem Item;

  while (true)
  {
    if (List.IsEmpty())
      break;

    if (GetCommand(&Item))
      Item.Execute();
  }
}

// ) Menu

// ( Menu item

/*
  Check for equality

  Current implementation is return true when our <Command> is the same
  as in external data.

  This method is used in list Traverse() callback.
*/
TBool TMenuItem::ItsMe(
  TAddressSegment Data
)
{
  return me_MemorySegment::AreEqual(Command, Data);
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
  TAddressSegment Command,
  TAddressSegment Description,
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
  const TAsciiz Command,
  const TAsciiz Description,
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
  TAddressSegment CommandCopy;
  TAddressSegment DescriptionCopy;
  {
    TAddressSegment CommandOrig = FromAsciiz(Command);
    TAddressSegment DescriptionOrig = FromAsciiz(Description);

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
    me_MemorySegment::Freetown::Release;

  // Release item strings
  Release(&Item->Command);
  Release(&Item->Description);

  // Release item structure (12 bytes)
  {
    TAddressSegment ItemSeg =
      { .Addr = (TAddress) Item, .Size = sizeof(TMenuItem) };

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
  2024-12-15
*/
