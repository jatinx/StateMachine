#include <StateMachine.hpp>
#include <iostream>
namespace States {

bool State::init(void *data) {
  DevLog("Running Default Init");
  return true;
}
bool State::exit(void *data) {
  DevLog("Running Default Exit");
  return true;
}
bool State::error(void *data) {
  DevLog("Running Default Error");
  return true;
}
bool State::rollback(void *data) {
  DevLog("Running Default Rollback");
  return true;
}

StateMachine &StateMachine::addState(State *state_) {
  if (state_ == nullptr) {
    DevLog("State Pass is NULL");
    return *this;
  }
  DevLog(state_->getName() + " - Adding State");
  states.push_back(state_);
  return *this;
}

std::vector<std::string> StateMachine::getNames() {
  std::vector<std::string> names;
  for (const auto &i : states) {
    names.push_back(i->getName());
  }
  return names;
}

void StateMachine::runImpl() {
  for (const auto &i : states) {
    runningState = i;
    // First Gather Data then run the error process
    if (!i->init(data) || !i->process(data) || !i->exit(data)) {
      DevLog(i->getName() + " - State has errors");
      status = ERROR;
      i->error(data);
      return;
    }
    if (isAsync && forceStop) {
      status = STOPPED;
      return;
    }
  }
  status = FINISHED;
}

bool StateMachine::run() {
  status = RUNNING;
  if (isAsync) {
    DevLog("Async Execution");
    runThread = std::thread(&StateMachine::runImpl, this);
  } else {
    runImpl();
    if (status != FINISHED)
      return false;
  }
  return true;
}
} // namespace States