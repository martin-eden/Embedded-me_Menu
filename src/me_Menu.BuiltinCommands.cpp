// Shell: built-in commands (list, exit)

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
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
  return CreateAndAddItem("?", ListCommand_Handler, (TUint_2) this);
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
  return CreateAndAddItem("^", ExitCommand_Handler, (TUint_2) this);
}

/*
  Add internal commands: list and exit
*/
TBool TMenu::AddBuiltinCommands()
{
  return (AddListCommand() && AddExitCommand());
}

/*
  2024-06 #
  2024-10 #
  2024-11 #
*/
