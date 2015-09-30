#ifndef MYAI
#define MYAI

namespace terminalGame {

class AI {
protected:
  float _reactionTime; // How often the AI may execute per second

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

};
}

#endif
