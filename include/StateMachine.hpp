#pragma once

#include <iostream>
#include <string>
#include <thread>
#include <vector>

// Logging Mechanism
static int debug_flag =
#if defined(DEV_LOG_ENABLE)
    1;
#else
    0;
#endif
#define LogMsg(msg)                                                            \
  { std::cout << "Log :\t" << msg << std::endl; }
#define DevLogMsg(msg)                                                         \
  {                                                                            \
    if (debug_flag)                                                            \
      LogMsg(msg)                                                              \
  }
#if defined(DEBUG)
#define DevLog(msg) DevLogMsg(msg)
#else
#define DevLog(msg)
#endif

namespace States {
// Inherit this class to create state machine
class State {
  std::string name;

public:
  State(std::string name_) : name(name_) {}
  const std::string &getName() const { return name; }
  virtual bool init(void *data);
  virtual bool process(void *data) = 0;
  virtual bool exit(void *data);
  virtual bool error(void *data);
  virtual bool rollback(void *data);
  ~State() {}
};

// State Machine Status
typedef enum { CREATED = 0, RUNNING, FINISHED, STOPPED, ERROR } SMStatus;

// State Machine instance to execite States
class StateMachine {
  bool isAsync;
  std::vector<State *> states;
  SMStatus status;
  State *runningState;
  bool forceStop;
  std::thread runThread;
  void runImpl();
  void *data;

public:
  StateMachine(bool isAsync_ = false) : isAsync(isAsync_) {
    status = CREATED;
    runningState = nullptr;
    forceStop = false;
  }
  void setData(void *data_) { data = data_; }
  bool hasErrorOccured() { return status == ERROR; }
  std::string getLastState() { return runningState->getName(); }
  bool finished() { return status == FINISHED || status == ERROR; }
  void *getData() { return data; }
  void stop() {
    if (isAsync)
      forceStop = true;
  }
  void awaitCompletion() {
    if (isAsync && runThread.joinable()) {
      runThread.join();
    }
  }

  StateMachine &addState(State *state_);
  std::vector<std::string> getNames();
  bool run();

  ~StateMachine() { awaitCompletion(); }
};
} // namespace States