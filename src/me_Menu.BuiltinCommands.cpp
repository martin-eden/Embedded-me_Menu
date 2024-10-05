// Shell: built-in commands (list, exit)

/*
  Author: Martin Eden
  Last mod.: 2024-09-12
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem;

/*
  Release() wrapper for builtin command

  Release() will empty list and empty list is exit condition
  in Run() loop.
*/
void Release_wrap(
  TUint_2 Data __attribute__((unused)),
  TUint_2 State
)
{
  TMenu * Menu = (TMenu *) State;
  Menu->Release();
}

/*
  Add exit command

    ^ - exit from Run() cycle
*/
TBool TMenu::AddExitCommand()
{
  TMenuItem Item;

  Item.Command.LoadFrom("^");
  Item.Description.LoadFrom("Exit");
  Item.Handler.Set(Release_wrap, (TUint_2) this);
  if (!Add(&Item))
    return false;

  return true;
}

/*
  Print() wrapper for built-in command
*/
void Print_wrap(
  TUint_2 Data __attribute__((unused)),
  TUint_2 State
)
{
  TMenu * Menu = (TMenu *) State;
  Menu->Print();
}

/*
  Add list command

    ? - print all available commands
*/
TBool TMenu::AddListCommand()
{
  TMenuItem Item;

  Item.Command.LoadFrom("?");
  Item.Description.LoadFrom("List commands");
  Item.Handler.Set(Print_wrap, (TUint_2) this);
  if (!Add(&Item))
    return false;

  return true;
}

/*
  2024-06-21 Spliced to standalone file
*/
