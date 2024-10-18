// Shell: built-in commands (list, exit)

/*
  Author: Martin Eden
  Last mod.: 2024-10-18
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>

using namespace me_Menu;

/*
  List command caller
*/
void ListCommand_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
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
  using
    Freetown::ToItem;

  return AddItem(ToItem("?", "List commands", ListCommand_Handler, (TUint_2) this));
}

/*
  Exit command implementation

  Menu.Release() will empty list. And empty list is exit condition
  in Menu.Run() loop.
*/
void ExitCommand_Handler(
  TUint_2 Data __attribute__((unused)),
  TUint_2 Instance
)
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
  using
    Freetown::ToItem;

  return AddItem(ToItem("^", "Exit", ExitCommand_Handler, (TUint_2) this));
}

/*
  Add internal commands: list and exit
*/
TBool TMenu::AddBuiltinCommands()
{
  return (AddListCommand() && AddExitCommand());
}

/*
  2024-06-21 Spliced to standalone file
  2024-10-18
*/
