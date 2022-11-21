# README of PicoRio2.0 C-Model


## How to Configure Design

You can configurate your architecture design using `config/gr-2i.cfg` as reference.

## How to Execute Your Design and Get IPC

Type `./model -h` to get the basic usage information.

```shell
usage: ./model --config=string --elf=string [options] ... 
options:
  -c, --config       Simulator Config Path (string)
  -e, --elf          elf Path (string)
  -l, --log          Log Path (string [=])
  -d, --debugFlag    Open Debug Log (string [=])
  -m, --MaxCycle     Max Tick Cycle (unsigned long [=18446744073709551615])
  -h, --debugHelp    Print debug Flags description
  -?, --help         print this message
```

Type `./model -c config/gr-2i.yml -e thirdParty/benchmark/embench_aha-mont64.riscv -h` to get the runtime debug information:

```shell
[---------- Debug flags descriptions ----------]
[ ALL                    |        "Open All Flags" ]
[ Commit                 |                "Commit" ]
[ CommitLog              |       "Commit Log (Clean)" ]
[ DCacheReq              |        "DCache Request" ]
[ DCacheResp             |       "DCache Response" ]
[ Execute                |       "Issue Insn & Start Execute" ]
[ Flush                  |           "Flush Stage" ]
[ Forwarding             |       "Forwarding Result of a insn" ]
[ Global                 |           "Global Flag" ]
[ ICacheReq              |        "ICache Request" ]
[ ICacheResp             |       "ICache Response" ]
[ Issue                  |       "Issue a Insn to Schedulars" ]
[ LoadReq                |       "LSU Load Request" ]
[ MemoryDependancy       |       "MemoryDependancy" ]
[ MemoryOrder            |       "Fence & AMO State" ]
[ ReadOperand            |       "Insn read Operand" ]
[ ReceiveReq             |       "Stage Receive Request from Last Stage" ]
[ Redirect               |       "Redirect Request to Fetch1 Stage" ]
[ Replay                 |       "Instruction Buffer Full, Replay Fetch" ]
[ RollBack               |       "Recovery->Rollback instruction" ]
[ Stall                  |       "Function Unit Stalled beacuse of Write Back Failed" ]
[ StoreReq               |       "LSU Store Request" ]
[ Tick                   |           "Tick Object" ]
[ WriteBack              |       "WriteBack a insn" ]

[---------- Debug Object descriptions ----------]
[ DRAM                   |          "DRAM Request" ]
[ Decode                 |                "Decode" ]
[ Dispatch               |              "Dispatch" ]
[ Fetch1                 |                "Fetch1" ]
[ Fetch2                 |                "Fetch2" ]
[ Rcu                    |       "Resource Allocate/Rename/RollBack/Commit Managerment" ]
```
