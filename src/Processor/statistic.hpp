#include <cstdio>

namespace Emulator {
  uint64_t n_insn = 0;
  uint64_t n_insnDispatched = 0; // per cycle

  void stat() {
    // printf("Average Number of Insn Dispatched Per cycle: %lf\n", (double)Emulator::n_insnDispatched/(double)Emulator::Clock::CurTick());
    printf("total insn: %d, total cycle: %d, IPC: %f\n", Emulator::n_insn, Emulator::Clock::CurTick(), (double)Emulator::n_insn / (double)Emulator::Clock::CurTick());

  }
	
}