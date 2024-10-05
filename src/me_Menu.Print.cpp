// Shell: print list of available commands

/*
  Author: Martin Eden
  Last mod.: 2024-10-05
*/

#include "me_Menu.h"

#include <stdio.h> // printf()

#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // for me_MemorySegment::Freetown::Print

using
  me_Menu::TMenu,
  me_Menu::TMenuItem,
  me_MemorySegment::Freetown::Print;

/*
  List handler: print item
*/
void PrintListNode(
  TUint_2 Data,
  TUint_2 HandlerData __attribute__((unused))
)
{
  TMenuItem * Item = (TMenuItem *) Data;

  Print(Item->Command.GetData());
  printf(" - ");
  Print(Item->Description.GetData());
  printf("\n");
}

/*
  Print menu
*/
void TMenu::Print()
{
  printf("--\n");
  List.Traverse(PrintListNode);
  printf("==\n");
}

/*
  2024-06-21 Spliced to standalone file
  2024-10-05
*/
