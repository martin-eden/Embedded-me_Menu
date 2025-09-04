// Shell: get command

/*
  Author: Martin Eden
  Last mod.: 2025-09-04
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>
#include <me_BaseInterfaces.h>
#include <me_StreamTokenizer.h>
#include <me_Console.h>

using namespace me_Menu;

/*
  Structure to hold search criteria and result

  Implementation-specific detail.
*/
struct TSearchAndCatch
{
  TAddressSegment LookingFor;
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
  Consume one entity from input stream and match it with our list of commands
*/
TBool TMenu::GetCommand(
  TMenuItem * ItemSelected
)
{
  /*
    Part one: get string
  */
  const TUint_2 BuffSize = 32;
  TUint_1 Buff[BuffSize];
  TAddressSegment BuffSeg;
  BuffSeg = { .Addr = (TAddress) &Buff, .Size = BuffSize };

  if (!me_StreamTokenizer::GetEntity(&BuffSeg, Console.GetInputStream()))
    return false;

  // Part two: search for this string
  TSearchAndCatch SearchState;
  {
    SearchState.LookingFor = BuffSeg;
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
  2024-10-28
  2025-09-04
*/
