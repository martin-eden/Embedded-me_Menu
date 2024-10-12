// Shell: built-in commands (list, exit)

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
  List command caller
*/
void ListCommand_Handler(
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
  Item.Handler.Set(ListCommand_Handler, (TUint_2) this);

  if (!Add(&Item))
    return false;

  return true;
}

/*
  Exit command implementation

  Menu.Release() will empty list. And empty list is exit condition
  in Menu.Run() loop.
*/
void ExitCommand_Handler(
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
  Item.Handler.Set(ExitCommand_Handler, (TUint_2) this);

  if (!Add(&Item))
    return false;

  return true;
}

/*
  Add internal commands: list and exit
*/
TBool TMenu::AddBuiltinCommands()
{
  /* [To do]

    Implement generic "AddCommand".

    Example usage:

      if (!AddCommand("^", "Exit", ExitCommand_Handler, this))
        return false;
      if (!AddCommand("?", "List", ListCommand_Handler, this))
        return false;
  */
  if (!AddListCommand())
    return false;

  if (!AddExitCommand())
    return false;

  return true;
}

/*
  2024-06-21 Spliced to standalone file
*/
