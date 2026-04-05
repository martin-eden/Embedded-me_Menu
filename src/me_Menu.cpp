// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_WorkmemTools.h>
#include <me_Console.h>

using namespace me_Menu;

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
  const TSize ItemStrucSize = sizeof(TMenuItem);

  TAddressSegment ItemSeg;

  // Allocate memory for copy of item structure
  if (!me_WorkmemTools::Reserve(&ItemSeg, ItemStrucSize))
    return false;

  // Set fields
  me_WorkmemTools::CopyMemTo(ItemSeg, M_AsAddrSeg(OuterMenuItem));

  // Add address of that copy to menu list
  if (!List.Add(ItemSeg.Addr))
  {
    me_WorkmemTools::Release(&ItemSeg);

    return false;
  }

  return true;
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TAddress Data,
  TAddress Instance [[gnu::unused]]
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

  while (!List.IsEmpty())
  {
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
  return me_WorkmemTools::AreEqual(Command, Data);
}

/*
  Run item's handler
*/
void TMenuItem::Execute()
{
  Console.Write("(");
  Handler.Run();
  Console.Write(")");
  Console.EndLine();
};

// ) Menu item

/*
  2024 # # # # # # # # # # # # # # #
  2025 #
  2026-04-05
*/
