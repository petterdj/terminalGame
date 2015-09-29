#ifndef MYAI
#define MYAI

namespace terminalGame {

class AI {
protected:

public:
  // CONSTRUCTORS //
  AI();

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
