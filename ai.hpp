#ifndef MYAI
#define MYAI

namespace terminalGame {

class AI {
protected:
  float _reactionTime; // How often the AI may execute in the main loop

public:
  // CONSTRUCTORS //
  AI();
  AI(float reactionTime);

  AI(const AI&);
  AI(AI&&);

  // OPERATORS //
  AI& operator=(const AI&);
  AI& operator=(AI&&);

  // DESTRUCTOR //
  ~AI();

  // FUNCTIONS //
  float getReactionTime() const;

  void setReactionTime(const float);

};
}

#endif
