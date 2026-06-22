#include "ActionInitialization.hh"

#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"

void ActionInitialization::BuildForMaster() const
{
  SetUserAction(new RunAction);
}

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction);     // GENERATES PRIMARY PARTICLES FOR EACH EVENT.

  auto runAction = new RunAction;                // CREATES AND STORES INFORMATION IN ROOT FILE.
  SetUserAction(runAction);

  auto eventAction = new EventAction(runAction); // COLLECTS ENERGY DEPOSITED FOR BOTH THE
  SetUserAction(eventAction);                    // TOTAL SYSTEM AND A PARTICULAR CELL DURING
                                                 // AN EVENT. IT THEN FEEDS INFORMATION TO
                                                 // RUN ACTION, ESSENTIALLY.
  SetUserAction(new SteppingAction(eventAction));
  
}


