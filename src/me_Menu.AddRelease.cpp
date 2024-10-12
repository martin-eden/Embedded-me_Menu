// Shell: add item, remove items

/*
  Author: Martin Eden
  Last mod.: 2024-10-12
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem;

/*
  Add menu item to menu
*/
TBool TMenu::Add(
  TMenuItem * OuterMenuItem
)
{
  TMenuItem * Item;

  // Create our copy in dynamic memory
  if (!me_MenuItem::Freetown::SpawnItem(&Item, OuterMenuItem))
    return false;

  // Add our copy to menu list
  if (!List.Add((TUint_2) Item))
  {
    me_MenuItem::Freetown::KillItem(Item);
    return false;
  }

  return true;
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TUint_2 Data,
  TUint_2 HandlerData __attribute__((unused))
)
{
  me_MenuItem::Freetown::KillItem((TMenuItem *) Data);
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
  2024-06-21 Spliced to standalone file
  2024-10-05 Freetown
*/
