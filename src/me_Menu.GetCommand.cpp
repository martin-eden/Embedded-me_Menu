// Shell: get command

/*
  Author: Martin Eden
  Last mod.: 2024-07-06
*/

#include "me_Menu.h"

#include <me_MemorySegment.h> // (Reserve/Release)Chunk()
#include <me_ManagedMemory.h> // more modern way of managing memseg
#include <me_SerialTokenizer.h> // GetEntity()
#include <me_BaseTypes.h>

using
  me_Menu::TMenu,
  me_Menu::TMenuItem,
  me_MemorySegment::TMemorySegment,
  me_ManagedMemory::TManagedMemory,
  me_BaseTypes::TBool,
  me_BaseTypes::TUint_2,
  me_BaseTypes::TChar;

/*
  Structure to hold state of search in list

  Implementation-specific detail.
*/
struct TLookedAndFound
{
  TMemorySegment LookingFor;
  TMenuItem * ItemFound;
};

/*
  List handler: find entity

  We are matching string in <State.LookingFor> to <.Command> in one of
  our items.
*/
void Match(
  TUint_2 NodeData,
  TUint_2 HandlerData
)
{
  TMenuItem * Item = (TMenuItem *) NodeData;
  TLookedAndFound * State = (TLookedAndFound *) HandlerData;

  if (Item->ItsMe(State->LookingFor))
    State->ItemFound = Item;
}

/*
  Get command from serial and match it to our list

  If we found menu item in our list with same <.Command>, copy
  that menu item to provided argument. Yes, we are returning a copy.
*/
TBool TMenu::GetCommand(TMenuItem * ItemSelected)
{
  // Part one: get string
  TManagedMemory String;
  {
    const TUint_2 InputBufferSize = 32;
    TChar Buffer[InputBufferSize];

    TMemorySegment BufferMem;
    BufferMem.Start.Addr = (TUint_2) &Buffer;
    BufferMem.Size = sizeof(Buffer);

    me_SerialTokenizer::TCapturedEntity Entity;

    me_SerialTokenizer::WaitEntity(&Entity, BufferMem);

    if (Entity.IsTrimmed)
    {
      // Entity was too long for our input buffer
      return false;
    }

    String.Set(Entity.Segment);
  }

  // Part two: search by this string
  TLookedAndFound SearchState;
  {
    SearchState.LookingFor = String.Get();
    SearchState.ItemFound = 0;

    List.Traverse(Match, (TUint_2) &SearchState);
  }

  // Part three: fulfill contract
  {
    if (SearchState.ItemFound != 0)
    {
      ItemSelected->Set(SearchState.ItemFound);
      return true;
    }
    return false;
  }
}

/*
  2024-06-21 Spliced to standalone file
*/
