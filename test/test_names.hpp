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
  bool rollback(void *data) override {
    auto &d_ = *reinterpret_cast<int *>(data);
    d_ -= 2;
    return true;
  }
};

TEST(StateMachineTest, GetNamesEmpty) {
  States::StateMachine sm;
  EXPECT_EQ(sm.getNames().size(), 0);
}

TEST(StateMachineTest, GetNamesFilled) {
  States::StateMachine sm;
  tempState s("TestState");
  sm.addState(&s);
  EXPECT_EQ(sm.getNames().size(), 1);
  EXPECT_EQ(sm.getNames()[0], "TestState");
}

TEST(StateMachineTest, OneStateRunSync) {
  States::StateMachine sm;
  tempState s("TestState");
  sm.addState(&s);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 2);
}

TEST(StateMachineTest, OneStateRunAsync) {
  States::StateMachine sm(true);
  tempState s("TestState");
  sm.addState(&s);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 2);
}

TEST(StateMachineTest, TwoStateRunSync) {
  States::StateMachine sm;
  tempState s1("S1");
  tempState s2("S2");
  sm.addState(&s1).addState(&s2);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 4);
}

TEST(StateMachineTest, TwoStateRunAsync) {
  States::StateMachine sm(true);
  tempState s1("S1");
  tempState s2("S2");
  sm.addState(&s1).addState(&s2);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  EXPECT_EQ(data, 4);
}

TEST(StateMachineTest, TwoStateRollBackRunSync) {
  States::StateMachine sm;
  tempState s1("S1");
  tempState s2("S2");
  sm.addState(&s1).addState(&s2);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  sm.rollBack();
  EXPECT_EQ(data, 0);
}

TEST(StateMachineTest, TwoStateRollBackRunAsync) {
  States::StateMachine sm(true);
  tempState s1("S1");
  tempState s2("S2");
  sm.addState(&s1).addState(&s2);
  int data = 0;
  sm.setData(reinterpret_cast<void *>(&data));
  sm.run();
  sm.awaitCompletion();
  sm.rollBack();
  sm.awaitCompletion();
  EXPECT_EQ(data, 0);
}