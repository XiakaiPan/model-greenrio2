#ifndef __RENAMETABLE_HH__
#define __RENAMETABLE_HH__

#include "../../Common/Common.hh"
#include "../../Trace/Logging.hh"

#include <vector>

namespace Emulator
{

template<size_t IsaRegCount, bool ZeroReg>
class RenameTable : public Trace::TraceObject
{
private:

    std::vector<PhyRegId_t> m_AliasTable;

public:
    RenameTable(std::string Name)
    :   TraceObject(Name)
    {
        this->m_AliasTable.resize(IsaRegCount);
    };
    ~RenameTable(){};

    PhyRegId_t& operator[](IsaRegId_t index){
        DASSERT((index<IsaRegCount) , "index[{}] > {}",IsaRegCount);
        return this->m_AliasTable[index];
    };

    void Reset(bool RenameRegister = true){
        for(size_t i = 0 ; i < IsaRegCount ; i++){
            if(!ZeroReg | (i!=0)){
                this->m_AliasTable[i] = RenameRegister ? 0 : i;
            }else{
                this->m_AliasTable[i] = 0;
            }
        }
    };  

};


} // namespace Emulator


#endif