// Serial commands handler

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_WorkmemTools.h>
#include <me_Console.h>
#include <me_StreamTokenizer.h>
#include <me_StreamsCollection.h>

using namespace me_Menu;

// ( Menu

/*
  Release memory at death
*/
TMenu::~TMenu()
{
  Release();
}

/*
  Add copy of menu item to menu

  Memory allocated here is 12 bytes:
    command seg, description seg, stored call
*/
TBool TMenu::AddItem(
  TMenuItem OuterMenuItem
)
{
  const TSize ItemStrucSize = sizeof(TMenuItem);

  TAddressSegment ItemSeg;

  // Allocate memory for copy of item structure
  if (!me_WorkmemTools::Reserve(&ItemSeg, ItemStrucSize))
    return false;

  // Set fields
  me_WorkmemTools::CopyMemTo(ItemSeg, M_AsAddrSeg(OuterMenuItem));

  // Add address of that copy to menu list
  if (!List.Add(ItemSeg.Addr))
  {
    me_WorkmemTools::Release(&ItemSeg);

    return false;
  }

  return true;
}

/*
  List handler: release item memory
*/
void KillItem_Handler(
  TAddress Data,
  TAddress Instance [[gnu::unused]]
)
{
  Freetown::KillItem((TMenuItem *) Data);
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
  Execute given command

  Returns FALSE if command not found.
*/
TBool TMenu::RunCommand(
  TAddressSegment Command
)
{
  TMenuItem Item;

  if (!GetMenuItem(&Item, Command))
    return false;

  Item.Execute();

  return true;
}

/*
  Consume one entity from input stream and match it with our list of commands
*/
TBool TMenu::GetCommand(
  TMenuItem * ItemSelected
)
{
  const TUint_2 BuffSize = 32;
  TUint_1 Buff[BuffSize];
  TAddressSegment CmdSeg = M_AsAddrSeg(Buff);
  me_StreamsCollection::TWorkmemOutputStream CmdStream;

  CmdStream.Init(CmdSeg);

  if (
    !me_StreamTokenizer::GetEntity(
      &CmdStream,
      Console.GetInputStream()
    )
  )
    return false;

  CmdSeg = CmdStream.GetProcessedSegment();

  return GetMenuItem(ItemSelected, CmdSeg);
}

/*
  Loop of getting data and executing corresponding item for non-empty
  list.

  Yeah, empty list is the exit condition.
*/
void TMenu::Run()
{
  TMenuItem Item;

  while (!List.IsEmpty())
  {
    if (GetCommand(&Item))
      Item.Execute();
  }
}

// ) Menu

// ( Menu item

/*
  Check for equality

  Current implementation is return true when our <Command> is the same
  as in external data.

  This method is used in list Traverse() callback.
*/
TBool TMenuItem::ItsMe(
  TAddressSegment Data
)
{
  return me_WorkmemTools::AreEqual(Command, Data);
}

/*
  Run item's handler
*/
void TMenuItem::Execute()
{
  Console.Write("(");
  Console.Write(Command);
  Console.EndLine();
  Console.Indent();

  Handler.Run();

  Console.Unindent();
  Console.Print(")");
};

// ) Menu item

/*
  2024 # # # # # # # # # # # # # # #
  2025 #
  2026-04-05
*/
