// Shell: built-in commands (list, exit)

/*
  Author: Martin Eden
  Last mod.: 2024-06-21
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem,
  me_BaseTypes::TBool,
  me_BaseTypes::TUint_2;

/*
  Release() wrapper for builtin command

  Release() will empty list and empty list is exit condition
  in Run() loop.
*/
void Release_wrap(TUint_2 Instance)
{
  TMenu * Menu = (TMenu *) Instance;
  Menu->Release();
}

/*
  Add exit command

    ^ - exit from Run() cycle
*/
TBool TMenu::AddExitCommand()
{
  TMenuItem Item;

  Item.Command.Set("^");
  Item.Description.Set("Exit");
  Item.Method.Set((TUint_2) this, (TUint_2) &Release_wrap);
  if (!Add(&Item))
    return false;

  return true;
}

/*
  Print() wrapper for built-in command
*/
void Print_wrap(TUint_2 Instance)
{
  TMenu * Menu = (TMenu *) Instance;
  Menu->Print();
}

/*
  Add list command

    ? - print all available commands
*/
TBool TMenu::AddListCommand()
{
  TMenuItem Item;

  Item.Command.Set("?");
  Item.Description.Set("List commands");
  Item.Method.Set((TUint_2) this, (TUint_2) &Print_wrap);
  if (!Add(&Item))
    return false;

  return true;
}

/*
  2024-06-21 Spliced to standalone file
*/
