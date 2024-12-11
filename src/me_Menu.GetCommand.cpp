// Consume entity from stdin and match to our commands

/*
  Author: Martin Eden
  Last mod.: 2024-11-30
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // Freetown::FromAddrSize(), AreEqual()
#include <me_SerialTokenizer.h> // GetEntity()

using namespace me_Menu;

using
  me_MemorySegment::TMemorySegment,
  me_Menu::CommandHandler::TCommandHandler;

/*
  Structure to hold search criteria and result

  Implementation-specific detail.
*/
struct TSearchAndCatch
{
  TMemorySegment LookingFor;
  TCommandHandler * ItemFound;
};

/*
  List handler: find entity

  If item's command is equal to what we got from serial then we found it.
*/
void OnListVisit(
  TUint_2 NodeData,
  TUint_2 HandlerData
)
{
  using
    me_MemorySegment::Freetown::AreEqual;

  TCommandHandler * Item = (TCommandHandler *) NodeData;

  TSearchAndCatch * State = (TSearchAndCatch *) HandlerData;

  if (AreEqual(Item->GetCommand(), State->LookingFor))
    State->ItemFound = Item;
}

/*
  Consume one entity from serial and match it with our list of commands
*/
TBool TMenu::GetCommand(
  TCommandHandler * ItemSelected
)
{
  using
    me_SerialTokenizer::TSerialTokenizer,
    me_MemorySegment::Freetown::FromAddrSize;

  /*
    Part one: get string

    String will be pointed by <Entity>.
    That segment will be inside of our buffer segment.
  */
  TMemorySegment Entity;

  const TUint_2 BuffSize = 32;
  TUint_1 Buffer[BuffSize];

  TMemorySegment BuffSeg = FromAddrSize((TUint_2) &Buffer, BuffSize);

  {
    TSerialTokenizer Tokenizer;

    Tokenizer.WaitEntity(&Entity, BuffSeg);
  }

  // Part two: search by this string
  TSearchAndCatch SearchState;

  {
    SearchState.LookingFor = Entity;
    SearchState.ItemFound = 0;

    List.Traverse(OnListVisit, (TUint_2) &SearchState);
  }

  // Part three: fulfill contract
  if (SearchState.ItemFound != 0)
  {
    *ItemSelected = *SearchState.ItemFound;

    return true;
  }

  return false;
}

/*
  2024-06 #
  2024-10 ##
  2024-11 ##
*/
