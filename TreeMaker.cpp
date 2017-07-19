#include <iostream>
#include <fstream>

#include <sstream>
#include <string>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TVector3.h"

#include "TXTrack.h"
#include "TClonesArray.h"

TFile * tFile    = nullptr;
TTree * tree     = NULL;

int nParticles   = 0;

TClonesArray *txTracks = NULL;

void addTrack( int gid, double px, double py, double pz, int iTrack ){

	TXTrack * ptr = new ((*txTracks)[iTrack]) TXTrack( );

	ptr->mGeantID = gid;
	TVector3 p( px, py, pz );
	ptr->mPt = p.Perp();
	ptr->mEta = p.PseudoRapidity();
	ptr->mPhi = p.Phi();


	// ptr->mId       = iTrack;
	// ptr->mEnergy   = plc->GetEnergy();
	// ptr->mKF       = plc->GetKF();
	// ptr->mKS       = plc->GetKS();
	// ptr->mLifetime = plc->GetLifetime();
	// ptr->mMass     = plc->GetMass();
	// ptr->mParent   = plc->GetParent();
	// ptr->mPx       = plc->GetPx();
	// ptr->mPy       = plc->GetPy();
	// ptr->mPz       = plc->GetPz();
	// ptr->mTime     = plc->GetTime();
	// ptr->mVx       = plc->GetVx();
	// ptr->mVy       = plc->GetVy();
	// ptr->mVz       = plc->GetVz();


}

int main( int argc, char** argv ){

	string name( argv[1] );
	tFile = new TFile( ( name + ".root" ).c_str(), "RECREATE" );
	tFile->cd();

	float event_b = 0;

	tree 		= new TTree( "urqmd", "", 99 );
	txTracks 	= new TClonesArray( "TXTrack" );
	tree->Branch( "Tracks", &txTracks, 256000, 99 );
	tree->Branch( "b", &event_b, "b/F" );

	cout << "Hello world" << endl;
	cout << "input: " << argv[1] << endl;

	UInt_t event = 0;
	UInt_t iTrack = 0;
	ifstream infile( argv[1] );
	string line;
	while (std::getline(infile, line)) {
		std::istringstream iss(line);
		string s;
		iss >> s;

		if ( "EVENT:" == s ) {
			if ( event > 0 ){
				tree->Fill();
				txTracks->Clear();
				iTrack = 0;
			}

			int iEvent = -1;
			int nTracks = -1;
			int nVerts = -1;
			float b = 0;
			iss >> iEvent >>nTracks >> nVerts >> b;
			event_b = b;

			event++;
			continue;
		}
		if ( "VERTEX:" == s ) continue;

		int gid;
		double px, py, pz;
		iss >> gid >> px >> py >> pz;
		// cout << gid << " (" << px << ", " << py << ", " << pz << ")" << endl;

		
		addTrack( gid, px, py, pz, iTrack );
		iTrack++;
	}

	tree->Write();
	tFile->Close();



	return 0;
}