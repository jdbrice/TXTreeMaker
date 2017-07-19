#ifndef TX_TRACK_H
#define TX_TRACK_H

#include "TObject.h"

class TXTrack : public TObject
{
public:
	TXTrack() {}
	~TXTrack() {}



	Int_t mGeantID;
	Double_t mPt;
	Double_t mEta;
	Double_t mPhi;
	ClassDef( TXTrack, 2 )
};

#endif