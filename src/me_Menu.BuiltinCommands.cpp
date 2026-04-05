// Shell: built-in commands (list, exit)

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_Console.h>
#include <me_WorkmemTools.h>

using namespace me_Menu;

/*
  [Internal] List handler: print item
*/
static void PrintListNode(
  TUint_2 Data,
  TUint_2 HandlerData [[gnu::unused]]
)
{
  using me_Menu::TMenuItem;
  TMenuItem * Item = (TMenuItem *) Data;

  Console.Write(Item->Command);
  if (Item->Description.Size > 0)
  {
    Console.Write("-");
    Console.Write(Item->Description);
  }
  Console.EndLine();
}

/*
  Print list of commands

  Conceptually it's internal function. Do not call it from your code,
  call RunListCommand() instead.

  But we can't make it "private" because we're getting Menu from
  external pointer. So we can call only "public" functions there.
*/
void me_Menu::TMenu::Print()
{
  List.Traverse(PrintListNode);
}

/*
  List command caller
*/
void ListCommand_Handler(
  TUint_2 Data [[gnu::unused]],
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
  return
    AddItem(
      Freetown::ToItem(
        "?",
        "List commands",
        ListCommand_Handler,
        (TUint_2) this
      )
    );
}

/*
  Execute "Print" command as if it was read as normal command

  Usually we wish to print some intro/help before waiting commands.
  This function is convenient shortcut for that.
*/
void TMenu::RunListCommand()
{
  RunCommand(me_WorkmemTools::FromAsciiz("?"));
}

/*
  Exit command implementation

  Menu.Release() will empty list. And empty list is exit condition
  in Menu.Run() loop.
*/
void ExitCommand_Handler(
  TUint_2 Data [[gnu::unused]],
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
  return
    AddItem(
      Freetown::ToItem(
        "^",
        "Exit",
        ExitCommand_Handler,
        (TUint_2) this
      )
    );
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
