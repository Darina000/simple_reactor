
#include "globals.hh"
#include "G4VModularPhysicsList.hh"

class QGSP_BERT: public G4VModularPhysicsList
{
public:
QGSP_BERT(G4int ver = 1);
virtual ~QGSP_BERT()=default;

QGSP_BERT(const QGSP_BERT &) = delete;
QGSP_BERT & operator=(const QGSP_BERT &)=delete;

};
