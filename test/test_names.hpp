#pragma once
#include "common.hpp"

class tempState : public States::State {
public:
  tempState(std::string name) : States::State(name) {}
  bool process(void *data) override {
    auto &d_ = *reinterpret_cast<int *>(data);
    d_ += 2;
    return true;
  }
};

TEST(StateMachineTest, GetNamesEmpty) {
  States::StateMachine sm;
  EXPECT_EQ(sm.getNames().size(), 0);
}

TEST(StateMachineTest, GetNamesFill) {
  States::StateMachine sm;
  tempState s("TestState");
  sm.addState(&s);
  EXPECT_EQ(sm.getNames().size(), 1);
  EXPECT_EQ(sm.getNames()[0], "TestState");
}

TEST(StateMachineTest, GetNamesTestProcess) {
  States::StateMachine sm;
  tempState s("TestState");
  sm.addState(&s);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 2);
}

TEST(StateMachineTest, GetNamesTestProcessAsync) {
  States::StateMachine sm(true);
  tempState s("TestState");
  sm.addState(&s);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 2);
}