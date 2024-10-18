// Shell: get command

/*
  Author: Martin Eden
  Last mod.: 2024-10-18
*/

#include "me_Menu.h"

#include <me_BaseTypes.h>
#include <me_MemorySegment.h> // Freetown::FromAddrSize()
#include <me_SerialTokenizer.h> // GetEntity()

using namespace me_Menu;

using
  me_MemorySegment::TMemorySegment;

/*
  Structure to hold search criteria and result

  Implementation-specific detail.
*/
struct TSearchAndCatch
{
  TMemorySegment LookingFor;
  TMenuItem * ItemFound;
};

/*
  List handler: find entity

  If item says "It's me!", that's it.
*/
void OnListVisit(
  TUint_2 NodeData,
  TUint_2 HandlerData
)
{
  TMenuItem * Item = (TMenuItem *) NodeData;
  TSearchAndCatch * State = (TSearchAndCatch *) HandlerData;

  if (Item->ItsMe(State->LookingFor))
    State->ItemFound = Item;
}

/*
  Consume one entity from serial and match it with our list of commands
*/
TBool TMenu::GetCommand(
  TMenuItem * ItemSelected
)
{
  using
    me_SerialTokenizer::TCapturedEntity,
    me_MemorySegment::Freetown::FromAddrSize;

  /*
    Part one: get string

    String will be pointed by <TCapturedEntity.Segment>.
    That segment will be inside of our buffer segment.
  */
  TCapturedEntity Entity;

  const TUint_2 BuffSize = 32;
  TUint_1 Buff[BuffSize];
  {
    TMemorySegment BuffSeg =
      FromAddrSize((TUint_2) &Buff, BuffSize);

    me_SerialTokenizer::WaitEntity(&Entity, BuffSeg);

    if (Entity.IsTrimmed)
    {
      // Entity was too long for our input buffer
      return false;
    }
  }

  // Part two: search by this string
  TSearchAndCatch SearchState;
  {
    SearchState.LookingFor = Entity.Segment;
    SearchState.ItemFound = 0;

    List.Traverse(OnListVisit, (TUint_2) &SearchState);
  }

  // Part three: fulfill contract
  {
    if (SearchState.ItemFound != 0)
    {
      *ItemSelected = *SearchState.ItemFound;

      return true;
    }
    return false;
  }
}

/*
  2024-06-21 Spliced to standalone file
  2024-10-18
*/
