// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2024-06-21
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_BaseTypes::TBool,
  me_BaseTypes::TUint_2;

/*
  Release memory at death
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add internal commands: list and exit
*/
TBool TMenu::AddBuiltinCommands()
{
  if (!AddListCommand())
    return false;
  if (!AddExitCommand())
    return false;
  return true;
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

/*
  2024-05-30
  2024-06-01
  2024-06-02
  2024-06-04
  2024-06-07
  2024-06-12
  2024-06-13
  2024-06-14
  2024-06-20
  2024-06-21 extradited Print(), Add()/Release(), GetSelection()
*/
