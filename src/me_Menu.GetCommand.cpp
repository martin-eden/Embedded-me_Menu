// Shell: get command

/*
  Author: Martin Eden
  Last mod.: 2026-04-05
*/

#include <me_Menu.h>

#include <me_BaseTypes.h>

#include <me_StreamTokenizer.h>
#include <me_Console.h>
#include <me_StreamsCollection.h>

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
  const TUint_2 BuffSize = 32;
  TUint_1 Buff[BuffSize];
  TAddressSegment BuffSeg = M_AsAddrSeg(Buff);
  me_StreamsCollection::TWorkmemOutputStream BuffOutStream;
  TSearchAndCatch SearchState;

  // Part one: get string

  BuffOutStream.Init(BuffSeg);

  if (!me_StreamTokenizer::GetEntity(&BuffOutStream, Console.GetInputStream()))
    return false;

  BuffSeg = BuffOutStream.GetProcessedSegment();

  // Part two: search for this string

  SearchState.LookingFor = BuffSeg;
  SearchState.ItemFound = 0;

  List.Traverse(OnListVisit, (TUint_2) &SearchState);

  // Part three: fulfill contract

  if (SearchState.ItemFound == 0)
    return false;

  *ItemSelected = *SearchState.ItemFound;

  return true;
}

/*
  2024 # # #
  2025-09-04
*/
