#ifndef __RS_OUTOFORDER_HH__
#define __RS_OUTOFORDER_HH__

#include "../BaseSchedular.hh"
#include <deque>

namespace Emulator
{
    
class RS_OutOfOrder : public BaseSchedular
{
private:
    struct issueQueue_entry_t
    {
        bool        valid;
        InsnPtr_t   insn;
    };

    std::deque<issueQueue_entry_t>  m_issueQueue;

    uint64_t                        m_usage;

public:
    RS_OutOfOrder(
        const std::string    Name, 
        const uint16_t       SchedularId,
        const uint64_t       EntryCount,
        const uint64_t       EnqueWidth,
        const uint64_t       DequeWidth,
        std::shared_ptr<Rcu> rcu
    ):  BaseSchedular(Name,SchedularId,EntryCount,EnqueWidth,DequeWidth,rcu),
        m_issueQueue(EntryCount,{false,nullptr}),
        m_usage(0)
    {};

    ~RS_OutOfOrder() {};

    void Reset(){
        this->m_usage = 0;
        for(auto entry : this->m_issueQueue){
            entry.insn  = nullptr;
            entry.valid = false;
        }
    };

    bool IssueQueueFull(){
        return this->m_usage == this->m_issueQueue.size();
    };

    bool Empty(){
        return this->m_usage == 0;
    };

    uint64_t GetAvailibleEntryCount(){
        return this->m_issueQueue.size() - this->m_usage;
    };

    uint64_t AllocateEntry(){
        DASSERT((!this->Busy()), "Allocate When there is no available entry!");
        for(size_t i = 0 ; i < this->m_issueQueue.size(); i++){
            if(!this->m_issueQueue[i].valid){
                this->m_issueQueue[i].valid = true;
                this->m_usage++;
                return i;
            }
        }
        return -1;
    };

    void Dispatch(InsnPtr_t& insn, uint64_t& index){
        this->m_issueQueue[index].insn = insn;
    };

    
    void IssueSelect(uint64_t& index, InsnPtr_t& insn, bool& Success){
        Success = false;
            for(index = 0 ; index < this->m_issueQueue.size(); index++){
                auto& entry = this->m_issueQueue[index];
                if(entry.valid && entry.insn){
                    insn = entry.insn;
                    if(((insn->Rs1Type == RegType_t::INT && !insn->Operand1Ready) ||
                        (insn->Rs2Type == RegType_t::INT && !insn->Operand2Ready)
                    )){
                        continue;
                    }else{
                        for(auto fu : this->m_FuncUnitVec){
                            if(fu->m_SupportFunc.count(insn->Fu) && !fu->Busy()){
                                Success = true;
                                fu->Allocate();
                                fu->Issue(insn);
                                return;
                            }
                        }
                        for(auto subs : this->m_SubSchedular){
                            if(subs->m_SupportFunc.count(insn->Fu) && !subs->Busy()){
                                Success = true;
                                uint64_t index = subs->Allocate();
                                subs->Schedule(insn,index);
                                return;
                            }
                        }
                    }
                }
            }
    };

    void Deallocate(uint64_t& index){
        this->m_issueQueue[index].valid = false;
        this->m_issueQueue[index].insn  = nullptr;
        this->m_usage--;
    }; 

    void Forwarding(InsnPtr_t& insn){
        if(insn->RdType != RegType_t::NONE && insn->PhyRd != 0 && !this->Empty()){
            for(auto& entry : this->m_issueQueue){
                InsnPtr_t& insn_wfIssue = entry.insn;
                if(entry.valid && insn_wfIssue){
                    if(insn->RdType == insn_wfIssue->Rs1Type && insn->PhyRd == insn_wfIssue->PhyRs1){
                        insn_wfIssue->Operand1 = insn->RdResult;
                        insn_wfIssue->Operand1Ready  = true;
                        DPRINTF(Forwarding,"RobTag[{}],Pc[{:#x}] -> Get Forwarding Data Rs1[{}],PRs1[{}] - Value[{:#x}]",
                            insn_wfIssue->RobTag, 
                            insn_wfIssue->Pc,
                            insn_wfIssue->IsaRs1,
                            insn_wfIssue->PhyRs1,
                            insn_wfIssue->Operand1
                        )
                    }
                    if(insn->RdType == insn_wfIssue->Rs2Type && insn->PhyRd == insn_wfIssue->PhyRs2){
                        insn_wfIssue->Operand2 = insn->RdResult;
                        insn_wfIssue->Operand2Ready = true;
                        DPRINTF(Forwarding,"RobTag[{}],Pc[{:#x}] -> Get Forwarding Data Rs2[{}],PRs2[{}] - Value[{:#x}]",
                            insn_wfIssue->RobTag, 
                            insn_wfIssue->Pc,
                            insn_wfIssue->IsaRs2,
                            insn_wfIssue->PhyRs2,
                            insn_wfIssue->Operand2
                        )
                    }
                }
            }
        }
    };


};

} // namespace Emulator




#endif