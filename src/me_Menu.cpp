// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h>
#include <me_List.h>

using namespace me_Menu;

using
  me_Menu::Unit::TUnit;

// ( Menu

/*
  Release memory at death
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add menu item to menu
*/
TBool TMenu::AddItem(
  TUnit * Item
)
{
  TUint_2 ItemAddr = (TUint_2) Item;

  if (!List.Add(ItemAddr))
    return false;

  return true;
}

/*
  [Handy] Create and add item from explicit list of values
*/
TBool TMenu::CreateAndAddItem(
  const TChar * Command,
  TMethod Handler,
  TUint_2 Instance
)
{
  using
    me_Menu::Unit::Create,
    me_Menu::Unit::Destroy;

  TUnit * Item;
  TBool IsOk;

  IsOk = Create(&Item, Command, Handler, Instance);

  if (!IsOk)
    return false;

  IsOk = AddItem(Item);

  if (!IsOk)
  {
    Destroy(Item);
    return false;
  }

  return true;
}

/*
  Loop of getting data and executing corresponding item for non-empty
  list.

  Yeah, empty list is the exit condition.
*/
void TMenu::Run()
{
  TUnit Item;

  while (true)
  {
    if (List.IsEmpty())
      break;

    if (GetCommand(&Item))
      Item.Execute();
  }
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TUint_2 Data,
  TUint_2 Instance __attribute__((unused))
)
{
  using
    me_Menu::Unit::Destroy;

  TUnit * Unit = (TUnit *) Data;

  Destroy(Unit);
}

/*
  Release memory of list items and the list
*/
void TMenu::Release()
{
  List.Traverse(KillItem_Handler);
  List.Release();
}

// ) Menu

/*
  2024-05 #
  2024-06 #########
  2024-07 #
  2024-10 ###
  2024-11 ##
*/
