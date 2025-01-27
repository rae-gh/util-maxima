

/************************************************************************
* RSA 10.9.21
************************************************************************/

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <cmath>

#include "VectorThree.h"
#include "helper.h"
#include "SpaceTransformation.h"

#include "CoutReports.h"
#include "Logger.h"

using namespace std;


void CoutReports::coutPeaks(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp, int interpNum)
{
    Logger::getInstance().log("coutPeaks");
    ccp4->CreatePeaks(interp,interpNum);

    unsigned int maxAtomNo = 99999;
    int maxDensity = (int)ccp4->DenLapPeaks.size();
    unsigned int maxResNo = 9999;
    vector<string> chains;
    chains.push_back("A");
    chains.push_back("B");
    chains.push_back("C");
    chains.push_back("D");
    chains.push_back("E");
    chains.push_back("F");
    chains.push_back("G");
    chains.push_back("H");
    chains.push_back("I");
    chains.push_back("J");
    chains.push_back("K");
    //if (ccp4->DenLapPeaks.size() < maxdensity)
    //    maxdensity = (int)ccp4->DenLapPeaks.size();
                
    //https://www.wwpdb.org/documentation/file-format-content/format33/v3.3.html
    //"REMARK   1                                                                      "
    //"HETATM  286  O   HOH B  57      17.652   2.846  -0.887  1.00 28.92           O  "
    cout << "BEGIN_CHIMERAPEAKS\n";
    cout << "REMARK   1 Peaks for " << pdb->getPdbCode() << " calculated by Leucippus (Birkbeck University of London 2021).\n";    
    cout << "REMARK   2 Software developed by Rachel Alcraft (2021) - supervisor Mark A. Williams.\n";    
    cout << "REMARK   3 Dummy atoms positioned at peaks calculated using both density and the laplacian.\n";    
    cout << "REMARK   4 All atoms have dummy type PK; element H; and chain P.\n";    
    cout << "REMARK   5 Residue DEN is for density calculated peaks and LAP for laplacian calculated.\n"; 
    unsigned int atomNo = 0;
    int resNo = 0;
    unsigned int i = 0;
    unsigned int chainNo = 0;
    while (atomNo < maxAtomNo && i < maxDensity)    
    {
        ++atomNo;
        ++resNo;
        ++i;
        if (resNo > maxResNo)
        {
            resNo = 0;
            ++chainNo;
        }
        string chain = chains[chainNo];

        pair<double, VectorThree> densityPair = ccp4->DenLapPeaks[i].first;
        pair<double, VectorThree> laplacianPair = ccp4->DenLapPeaks[i].second;
                
        VectorThree coords = densityPair.second;
        double density = densityPair.first;
        VectorThree XYZ = ccp4->getXYZFromCRS(coords.reverse());
        //FIRST THE DENSITY PEAKS        
        cout << helper::getWordStringGaps("HETATM",6) << "HETATM";                                      //1. Atom or Hetatm                
        cout << helper::getNumberStringGaps(atomNo,0,5) << atomNo;                                  //2. Atom no - 7        
        cout << helper::getWordStringGaps("PK",3) << "PK";                                          //3. Atom type, eg CA, CB...        
        cout << helper::getWordStringGaps("DEN",6) << "DEN";                                        //4. Amino Acid        
        cout << helper::getWordStringGaps(chain,2)<< chain;                                            //5. Chain        
        cout << helper::getNumberStringGaps(resNo,0,4) << resNo;                                  //6. Residue number        
        cout << helper::getNumberStringGaps(XYZ.A,3,12) << setprecision(3) << fixed << XYZ.A;       //7. x coord
        cout << helper::getNumberStringGaps(XYZ.B,3,8) << setprecision(3) << fixed << XYZ.B;        //8. y coord
        cout << helper::getNumberStringGaps(XYZ.C,3,8) << setprecision(3) << fixed << XYZ.C;        //9. z coord                        
        cout << helper::getNumberStringGaps(1,2,6) << "1.00";                                       //10. Occupancy        
        cout << helper::getNumberStringGaps(density,2,6) << setprecision(2) << fixed << density;    //11. BFactor,which is really density        
        cout << helper::getWordStringGaps("H",12) << "H";                                           //12. Element     
        cout << "  \n";
        //THEN the laplacian peaks which are currenly the same TODO
        ++atomNo;
        VectorThree coordsL = laplacianPair.second;
        double laplacian = laplacianPair.first;
        XYZ = ccp4->getXYZFromCRS(coordsL.reverse());
        cout << helper::getWordStringGaps("HETATM",6) << "HETATM";                                      //1. Atom or Hetatm                
        cout << helper::getNumberStringGaps(atomNo,0,5) << atomNo;                                  //2. Atom no - 7        
        cout << helper::getWordStringGaps("PK",3) << "PK";                                          //3. Atom type, eg CA, CB...        
        cout << helper::getWordStringGaps("LAP",6) << "LAP";                                        //4. Amino Acid        
        cout << helper::getWordStringGaps(chain,2)<< chain;                                            //5. Chain        
        cout << helper::getNumberStringGaps(resNo,0,4) << resNo;                                  //6. Residue number        
        cout << helper::getNumberStringGaps(XYZ.A,3,12) << setprecision(3) << fixed << XYZ.A;       //7. x coord
        cout << helper::getNumberStringGaps(XYZ.B,3,8) << setprecision(3) << fixed << XYZ.B;        //8. y coord
        cout << helper::getNumberStringGaps(XYZ.C,3,8) << setprecision(3) << fixed << XYZ.C;        //9. z coord                        
        cout << helper::getNumberStringGaps(1,2,6) << "1.00";                                       //10. Occupancy        
        cout << helper::getNumberStringGaps(laplacian*-1.00,2,6) << setprecision(2) << fixed << laplacian*-1;    //11. BFactor,which is really density        
        cout << helper::getWordStringGaps("H",12) << "H";                                           //12. Element     
        cout << "  \n";
    }
       /*http://www.bmsc.washington.edu/CrystaLinks/man/pdb/part_72.html
                 1         2         3         4         5         6         7
        1234567890123456789012345678901234567890123456789012345678901234567890
        MASTER       40    0    0    0    0    0    0    6 2930    2    0   29
        */                      
    cout << helper::getWordStringGaps("MASTER",6) << "MASTER";//1 -  6       Record name    "MASTER"             
    cout << helper::getNumberStringGaps(4,0,9) << 5;//11 - 15       Integer        numRemark     Number of REMARK records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//16 - 20       Integer        "0"
    cout << helper::getNumberStringGaps(0,0,5) << 0;//21 - 25       Integer        numHet        Number of HET records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//26 - 30       Integer        numHelix      Number of HELIX records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//31 - 35       Integer        numSheet      Number of SHEET records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//36 - 40       Integer        numTurn       Number of TURN records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//41 - 45       Integer        numSite       Number of SITE records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//46 - 50       Integer        numXform      Number of coordinate transformation  records (ORIGX+SCALE+MTRIX)
    cout << helper::getNumberStringGaps(atomNo,0,5) << atomNo;//51 - 55       Integer        numCoord      Number of atomic coordinate records (ATOM+HETATM)
    cout << helper::getNumberStringGaps(0,0,5) << 0;//56 - 60       Integer        numTer        Number of TER records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//61 - 65       Integer        numConect     Number of CONECT records
    cout << helper::getNumberStringGaps(0,0,5) << 0;//66 - 70       Integer        numSeq        Number of SEQRES records
    cout << "\nEND\n";
    cout << "END_CHIMERAPEAKS\n";
        
    cout << "BEGIN_ALLPEAKS\n";
    cout << "Density,C,R,S,X,Y,Z,NearestAtom,Distance\n";
    for (unsigned int i = 0; i < maxDensity; ++i)
    {
                
        VectorThree coords = ccp4->DenLapPeaks[i].first.second;
        double density = ccp4->DenLapPeaks[i].first.first;
        VectorThree XYZ = ccp4->getXYZFromCRS(coords.reverse());
        
        
        double distance = 0;
        string line = "-";
        if (pdb->isLoaded())
        {
            Atom* atm = pdb->getNearest(XYZ.A, XYZ.B, XYZ.C);
            if (atm != NULL)
            {
                line = atm->getLine();
                distance = atm->distance(XYZ.A, XYZ.B, XYZ.C);
            }
        }
        if (line == "-")
            cout << "" << density << "," << coords.C << "," << coords.B << "," << coords.A << "," << XYZ.A << "," << XYZ.B << "," << XYZ.C << "," << line << ",-" << "\n";
        else
            cout << "" << density << "," << coords.C << "," << coords.B << "," << coords.A << "," << XYZ.A << "," << XYZ.B << "," << XYZ.C << "," << line << "," << distance << "\n";
    }
    cout << "END_ALLPEAKS\n";

    cout << "BEGIN_ATOMPEAKS\n";
    cout << "Density,C,R,S,X,Y,Z,NearestAtom,Distance\n";
    for (unsigned int i = 0; i < maxDensity; ++i)
    {
        VectorThree coords = ccp4->DenLapPeaks[i].first.second;
        double density = ccp4->DenLapPeaks[i].first.first;
        VectorThree XYZ = ccp4->getXYZFromCRS(coords.reverse());

        double distance = 0;
        string line = "-";
        if (pdb->isLoaded())
        {
            Atom* atm = pdb->getNearest(XYZ.A, XYZ.B, XYZ.C);
            if (atm != NULL)
            {
                line = atm->getLine();
                distance = atm->distance(XYZ.A, XYZ.B, XYZ.C);
            }
        }
        if (line != "-")                    
            cout << "" << density << "," << coords.C << "," << coords.B << "," << coords.A << "," << XYZ.A << "," << XYZ.B << "," << XYZ.C << "," << line << "," << distance << "\n";
    }
    cout << "END_ATOMPEAKS\n";

}

void CoutReports::coutEmbellishPdb(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp, int interpNum)
{
    Logger::getInstance().log("coutPeaks");
    ccp4->CreatePeaks(interp, interpNum);

    unsigned int maxAtomNo = 500;
    int maxDensity = (int)ccp4->DenLapPeaks.size();
    unsigned int maxResNo = 9999;
    
    //https://www.wwpdb.org/documentation/file-format-content/format33/v3.3.html
    //"REMARK   1                                                                      "
    //"HETATM  286  O   HOH B  57      17.652   2.846  -0.887  1.00 28.92           O  "
    cout << "BEGIN_EMBELLISH\n";
    cout << "REMARK   1 Unassigned peaks for " << pdb->getPdbCode() << " calculated by Leucippus (Birkbeck University of London 2021).\n";
    cout << "REMARK   2 Software developed by Rachel Alcraft (2021) - supervisor Mark A. Williams.\n";
    cout << "REMARK   3 Unassigned peaks >1A and <5A from nearest atom, added as dummy HEATAMS.\n";
    cout << "REMARK   4 All atoms have dummy type PK; element H; and chain P.\n";
    cout << "REMARK   5 Residue DEN is for density calculated peaks and LAP for laplacian calculated.\n";
    unsigned int atomNo = 0;
    int resNo = 0;
    unsigned int i = 0;
    unsigned int chainNo = 0;
    //maxDensity = 1000;
    while (atomNo < maxAtomNo && i < maxDensity)
    {                        
        pair<double, VectorThree> densityPair = ccp4->DenLapPeaks[i].first;
        ++i;
        
        VectorThree coords = densityPair.second;
        double density = densityPair.first;
        //we only want thguis if it is near an atom but unassigned.
        VectorThree XYZ = ccp4->getXYZFromCRS(coords.reverse());
        Atom* atm = pdb->getNearest(XYZ.A, XYZ.B, XYZ.C);
        if (atm != NULL)
        {            

            double distance = atm->distance(XYZ.A, XYZ.B, XYZ.C);            
            if (distance < 4 && distance > 0.5)
            {
                ++atomNo;
                ++resNo;

                cout << helper::getWordStringGaps("HETATM", 6) << "HETATM";                                      //1. Atom or Hetatm                
                cout << helper::getNumberStringGaps(atomNo, 0, 5) << atomNo;                                  //2. Atom no - 7        
                cout << helper::getWordStringGaps("PK", 3) << "PK";                                          //3. Atom type, eg CA, CB...        
                cout << helper::getWordStringGaps("DEN", 6) << "DEN";                                        //4. Amino Acid        
                cout << helper::getWordStringGaps("P", 2) << "P";                                            //5. Chain        
                cout << helper::getNumberStringGaps(resNo, 0, 4) << resNo;                                  //6. Residue number        
                cout << helper::getNumberStringGaps(XYZ.A, 3, 12) << setprecision(3) << fixed << XYZ.A;       //7. x coord
                cout << helper::getNumberStringGaps(XYZ.B, 3, 8) << setprecision(3) << fixed << XYZ.B;        //8. y coord
                cout << helper::getNumberStringGaps(XYZ.C, 3, 8) << setprecision(3) << fixed << XYZ.C;        //9. z coord                        
                cout << helper::getNumberStringGaps(1, 2, 6) << "1.00";                                       //10. Occupancy        
                cout << helper::getNumberStringGaps(density, 2, 6) << setprecision(2) << fixed << density;    //11. BFactor,which is really density        
                cout << helper::getWordStringGaps("H", 12) << "H";                                           //12. Element     
                cout << "  \n";
            }
        }
        
    }
    /*http://www.bmsc.washington.edu/CrystaLinks/man/pdb/part_72.html
              1         2         3         4         5         6         7
     1234567890123456789012345678901234567890123456789012345678901234567890
     MASTER       40    0    0    0    0    0    0    6 2930    2    0   29
     */
    cout << helper::getWordStringGaps("MASTER", 6) << "MASTER";//1 -  6       Record name    "MASTER"             
    cout << helper::getNumberStringGaps(4, 0, 9) << 5;//11 - 15       Integer        numRemark     Number of REMARK records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//16 - 20       Integer        "0"
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//21 - 25       Integer        numHet        Number of HET records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//26 - 30       Integer        numHelix      Number of HELIX records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//31 - 35       Integer        numSheet      Number of SHEET records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//36 - 40       Integer        numTurn       Number of TURN records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//41 - 45       Integer        numSite       Number of SITE records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//46 - 50       Integer        numXform      Number of coordinate transformation  records (ORIGX+SCALE+MTRIX)
    cout << helper::getNumberStringGaps(atomNo, 0, 5) << atomNo;//51 - 55       Integer        numCoord      Number of atomic coordinate records (ATOM+HETATM)
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//56 - 60       Integer        numTer        Number of TER records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//61 - 65       Integer        numConect     Number of CONECT records
    cout << helper::getNumberStringGaps(0, 0, 5) << 0;//66 - 70       Integer        numSeq        Number of SEQRES records
    cout << "\nEND\n";
    cout << "END_EMBELLISH\n";
        
}

void CoutReports::coutAtomsDensity(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp)
{
    cout << "BEGIN_ATOMDENSITY\n";
    cout << "Density,X,Y,Z,AtomNo,AtomLine\n";
    if (pdb->isLoaded())
    {
        for (unsigned int i = 0; i < pdb->Atoms.size(); ++i)
        {
            Atom atm = pdb->Atoms[i];
            VectorThree XYZ = atm.getXYZ();
            //float density = ccp4->getDensity(XYZ);    
            VectorThree crs = ccp4->getCRSFromXYZ(XYZ);
            double density = interp->getValue(crs.A, crs.B, crs.C);
            string line = atm.getLine();
            int atmNo = atm.AtomNo;
            cout << "" << density << "," << XYZ.A << "," << XYZ.B << "," << XYZ.C << "," << atmNo << "," << line << "\n";
        }
    }
    cout << "END_ATOMDENSITY\n";

}

void CoutReports::coutAtomsAdjusted(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp)
{
    Logger::getInstance().log("coutAtomsAdjusted");
    if (pdb->isLoaded())
    {
        cout << "BEGIN_DENSITYADJUSTED\n";
        cout << "REMARK   1 Atom positions for " << pdb->getPdbCode() << " adjusted on density maxima by Leucippus (Birkbeck University of London 2021).\n";
        cout << "REMARK   2 Software developed by Rachel Alcraft (2021) - supervisor Mark A. Williams.\n";
        cout << "REMARK   3 Only atoms with full occupancy have been included.\n";
        cout << "REMARK   4 Where a nearby density peak could not be found the atom has been removed\n";

        Logger::getInstance().log("Adjusting by density");
        int numAtoms = 0;
        for (unsigned int i = 0; i < pdb->Atoms.size(); ++i)
        {
            if (i % 100 == 0)
            {
                stringstream status;
                status << i << "/" << pdb->Atoms.size();
                Logger::getInstance().log(status.str());
            }

            Atom atm = pdb->Atoms[i];
            if (atm.peakable("DEN"))
            {
                VectorThree CRS = ccp4->getCRSFromXYZ(atm.getXYZ());                
                VectorThree ABC = interp->getNearbyAtomPeak(CRS.reverse(), true);                
                if (ABC.Valid) 
                {
                    VectorThree XYZ = ccp4->getXYZFromCRS(ABC.reverse());
                    ++numAtoms;
                    string line = atm.getLineCoords(XYZ);
                    cout << line << "\n";
                }
            }            
        }
        cout << helper::getWordStringGaps("MASTER", 6) << "MASTER";//1 -  6       Record name    "MASTER"             
        cout << helper::getNumberStringGaps(4, 0, 9) << 4;//11 - 15       Integer        numRemark     Number of REMARK records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//16 - 20       Integer        "0"
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//21 - 25       Integer        numHet        Number of HET records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//26 - 30       Integer        numHelix      Number of HELIX records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//31 - 35       Integer        numSheet      Number of SHEET records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//36 - 40       Integer        numTurn       Number of TURN records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//41 - 45       Integer        numSite       Number of SITE records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//46 - 50       Integer        numXform      Number of coordinate transformation  records (ORIGX+SCALE+MTRIX)
        cout << helper::getNumberStringGaps(numAtoms, 0, 5) << numAtoms;//51 - 55       Integer        numCoord      Number of atomic coordinate records (ATOM+HETATM)
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//56 - 60       Integer        numTer        Number of TER records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//61 - 65       Integer        numConect     Number of CONECT records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//66 - 70       Integer        numSeq        Number of SEQRES records
        cout << "END_DENSITYADJUSTED\n";

        cout << "BEGIN_LAPLACIANADJUSTED\n";
        cout << "REMARK   1 Atom positions for " << pdb->getPdbCode() << " adjusted on laplacian minima by Leucippus (Birkbeck University of London 2021).\n";
        cout << "REMARK   2 Software developed by Rachel Alcraft (2021) - supervisor Mark A. Williams.\n";
        cout << "REMARK   3 Only atoms with full occupancy have been included.\n";
        cout << "REMARK   4 Where a nearby laplacian peak could not be found the atom has been removed\n";

        numAtoms = 0;
        Logger::getInstance().log("Adjusting by Laplacian");
        for (unsigned int i = 0; i < pdb->Atoms.size(); ++i)
        {
            if (i % 100 == 0)
            {
                stringstream status;
                status << i << "/" << pdb->Atoms.size();
                Logger::getInstance().log(status.str());
            }

            Atom atm = pdb->Atoms[i];
            if (atm.peakable("LAP"))
            {
                VectorThree CRS = ccp4->getCRSFromXYZ(atm.getXYZ());
                VectorThree ABC = interp->getNearbyAtomPeak(CRS.reverse(), false);                
                if (ABC.Valid)
                {
                    VectorThree XYZ = ccp4->getXYZFromCRS(ABC.reverse());
                    ++numAtoms;
                    string line = atm.getLineCoords(XYZ);
                    cout << line << "\n";
                }
            }
        }
        cout << helper::getWordStringGaps("MASTER", 6) << "MASTER";//1 -  6       Record name    "MASTER"             
        cout << helper::getNumberStringGaps(4, 0, 9) << 4;//11 - 15       Integer        numRemark     Number of REMARK records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//16 - 20       Integer        "0"
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//21 - 25       Integer        numHet        Number of HET records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//26 - 30       Integer        numHelix      Number of HELIX records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//31 - 35       Integer        numSheet      Number of SHEET records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//36 - 40       Integer        numTurn       Number of TURN records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//41 - 45       Integer        numSite       Number of SITE records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//46 - 50       Integer        numXform      Number of coordinate transformation  records (ORIGX+SCALE+MTRIX)
        cout << helper::getNumberStringGaps(numAtoms, 0, 5) << numAtoms;//51 - 55       Integer        numCoord      Number of atomic coordinate records (ATOM+HETATM)
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//56 - 60       Integer        numTer        Number of TER records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//61 - 65       Integer        numConect     Number of CONECT records
        cout << helper::getNumberStringGaps(0, 0, 5) << 0;//66 - 70       Integer        numSeq        Number of SEQRES records
        cout << "END_LAPLACIANADJUSTED\n";
    }
    


}

void CoutReports::coutSlices(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp, vector<VectorThree> centrals, vector<VectorThree> linears, vector<VectorThree> planars, double width, double gap)
{
    cout << "BEGIN_SLICENUMS\n" << centrals.size() << "\nEND_SLICENUMS\n";

    for (unsigned int p = 0; p < centrals.size(); ++p)
    {
        coutSlice(ccp4,pdb,interp,centrals[p],linears[p],planars[p],width,gap,p);

    }
}

void CoutReports::coutSlice(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp, VectorThree central, VectorThree linear, VectorThree planar, double width, double gap, int position)
{
    Logger::getInstance().log("coutSlices");
    SpaceTransformation space(central,linear,planar);
    stringstream strpos;
    strpos << position;
        
    //////////////
    cout << "BEGIN_DENSITYSLICE_" << position << "\n";    
    Logger::getInstance().log("BEGIN_DENSITYSLICE_" + strpos.str());
    int length = (int)(width / gap);
    int halfLength = length/2;
    cout << "i,j,Density\n";
    for (int i = -1*halfLength; i <= halfLength; ++i)
    {
        for (int j = -1*halfLength; j <= halfLength; ++j)
        {
            double x0 = (i*gap);
            double y0 = (j*gap);
            double z0 = 0;            
            VectorThree transformed = space.applyTransformation(VectorThree(x0,y0,z0));            
            //double density2 = ccp4->getDensity(transformed);
            VectorThree crs = ccp4->getCRSFromXYZ(transformed);
            double density = interp->getValue(crs.A, crs.B, crs.C);
            cout << i+halfLength << "," << j+halfLength << "," << density << "\n";            
        }        
    }
    cout << "END_DENSITYSLICE_" << position << "\n";

    cout << "BEGIN_RADIANTSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_RADIANTSLICE_" + strpos.str());
    cout << "i,j,Radiant\n";
    for (int i = -1*halfLength; i <= halfLength; ++i)
    {
        for (int j = -1*halfLength; j <= halfLength; ++j)
        {
            double x0 = (i*gap);
            double y0 = (j*gap);
            double z0 = 0;            
            VectorThree transformed = space.applyTransformation(VectorThree(x0,y0,z0));            
            //double radiant2 = ccp4->getRadiant(transformed);
            VectorThree crs = ccp4->getCRSFromXYZ(transformed);
            double radiant = interp->getRadiant(crs.A, crs.B, crs.C);
            cout << i+halfLength << "," << j+halfLength << "," << radiant << "\n";
        }        
    }
    cout << "END_RADIANTSLICE_" << position << "\n";

    cout << "BEGIN_LAPLACIANSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_LAPLACIANSLICE_" + strpos.str());
    cout << "i,j,Laplacian\n";
    for (int i = -1*halfLength; i <= halfLength; ++i)
    {
        for (int j = -1*halfLength; j <= halfLength; ++j)
        {
            double x0 = (i*gap);
            double y0 = (j*gap);
            double z0 = 0;            
            VectorThree transformed = space.applyTransformation(VectorThree(x0,y0,z0));            
            //double laplacian1 = ccp4->getLaplacian(transformed);
            VectorThree crs = ccp4->getCRSFromXYZ(transformed);
            double laplacian = interp->getLaplacian(crs.A, crs.B, crs.C);
            cout << i+halfLength << "," << j+halfLength << "," << laplacian << "\n";
        }        
    }
    cout << "END_LAPLACIANSLICE_" << position << "\n";

    //FINALLY CRATE THE position matrix
    cout << "BEGIN_POSITIONSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_POSITIONSLICE_" + strpos.str());
    cout << "i,j,Position\n";
    //we do not need a massive matrix of zeros, these positions go with the above, so we fill with zeros and then place these points
    VectorThree ccc = space.reverseTransformation(central);    
    VectorThree lll = space.reverseTransformation(linear);    
    VectorThree ppp = space.reverseTransformation(planar);
    ccc = ccc/gap;
    ccc.A += (double)halfLength; 
    ccc.B += halfLength;    
    int x = (int)ccc.A;
    int y = (int)ccc.B;
    double val = 1;
    if (abs(ccc.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    lll = lll/gap;
    lll.A += (double)halfLength;
    lll.B += halfLength;    
    x = (int)lll.A;
    y = (int)lll.B;
    val = 1;
    if (abs(lll.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    ppp = ppp/gap;
    ppp.A += (double)halfLength;
    ppp.B += halfLength;    
    x = (int)ppp.A;
    y = (int)ppp.B; 
    val = 1;
    if (abs(ppp.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    
    cout << "END_POSITIONSLICE_" << position << "\n";

}
void CoutReports::coutSamples(Ccp4* ccp4, PdbFile* pdb, Interpolator* interpMap, Interpolator* interpSample)
{
    Logger::getInstance().log("coutSamples");
    interpSample->addAtoms(pdb->Atoms);
    vector<float> SyntheticMatrix;
    Logger::getInstance().log("Creating synthetic matrix");
    for (unsigned int i = 0; i < ccp4->Matrix.size(); ++i)
    {
        if (i % 5000 == 0)
        {
            int percent = float(i) / ccp4->Matrix.size() * 100;

            stringstream status;
            status << i << "/" << ccp4->Matrix.size() << "\t = " << percent << " %";
            Logger::getInstance().log(status.str());
        }
        VectorThree crs = ccp4->getCRS(i);
        VectorThree XYZ = ccp4->getXYZFromCRS(crs.reverse());
        double val = interpSample->getValue(XYZ.A, XYZ.B, XYZ.C);
        double valCheck = interpMap->getValue(XYZ.A, XYZ.B, XYZ.C);
        SyntheticMatrix.push_back(val);
        
    }
    //now I can replace the ccp4 matrix with the sample matrix
    ccp4->Matrix = SyntheticMatrix;
    ccp4->MatrixDiff = SyntheticMatrix;
    //and then I can find the adjusted pdb files with my new interpolator
    Interpolator* interpMap2 = new Thevenaz(ccp4->Matrix, ccp4->W01_NX, ccp4->W02_NY, ccp4->W03_NZ);

    Logger::getInstance().log("Using synthetic matrix");
    coutAtomsAdjusted(ccp4, pdb, interpMap2);
}

void CoutReports::coutSyntheticIAM(Ccp4* ccp4, PdbFile* pdb, Interpolator* interp)
{
    Logger::getInstance().log("coutSyntheticIAM");
    interp->addAtoms(pdb->Atoms);
    cout << "BEGIN_SYNTHETIC_IAM\n";
    cout << "i,j,k,Density\n";
    cout << ccp4->W01_NX << "," << ccp4->W02_NY << "," << ccp4->W03_NZ << ",Dimensions\n";
    for (int i = 0; i < ccp4->W01_NX; ++i)
    {
        for (int j = 0; j < ccp4->W02_NY; ++j)
        {
            for (int k = 0; k < ccp4->W03_NZ; ++k)
            {
                VectorThree XYZ = ccp4->getXYZFromCRS(VectorThree(i,j,k).reverse());
                double val = interp->getValue(XYZ.A, XYZ.B, XYZ.C);
                double absval = abs(val);
                if (absval > 0.0001)
                    cout << i << "," << j << "," << k << "," << val <<"\n";
            }
        }
    }

    cout << "END_SYNTHETIC_IAM\n";

}

void CoutReports::coutDeformation(Ccp4* ccp4, PdbFile* pdb, Interpolator* interpMap, Interpolator* interpSample)
{
    Logger::getInstance().log("coutDeformation");
    vector<float> orig_stats = interpMap->getStatsValues();
    vector<int> orig_poses = interpMap->getStatsPoses();
    cout << "BEGIN_ORIGINAL_STATS\n";
    cout << "min,q1,q2,q3,max\n";
    for (unsigned int o = 0; o < orig_poses.size(); ++o)
    {
        if (o > 0)
            cout << ",";
        cout << orig_poses[o];
    }
    for (unsigned int o = 0; o < orig_stats.size(); ++o)
    {
        if (o > 0)
            cout << ",";
        else
            cout << "\n";
        cout << orig_stats[o];
    }
    cout << "\n";
    cout << "END_ORIGINAL_STATS\n";
    
    cout << "BEGIN_ORIGINAL\n";
    cout << "i,j,k,Density\n";
    cout << ccp4->W01_NX << "," << ccp4->W02_NY << "," << ccp4->W03_NZ << ",Dimensions\n";
    for (int i = 0; i < ccp4->W01_NX; ++i)
    {
        for (int j = 0; j < ccp4->W02_NY; ++j)
        {
            for (int k = 0; k < ccp4->W03_NZ; ++k)
            {
                VectorThree XYZ = ccp4->getXYZFromCRS(VectorThree(i, j, k).reverse());                
                double val_orig = interpMap->getValue(XYZ.A, XYZ.B, XYZ.C);
                double absval = abs(val_orig);
                if (absval > 0.0001)
                    cout << i << "," << j << "," << k << "," << val_orig << "\n";
            }
        }
    }
    cout << "END_ORIGINAL\n";    
    
    Logger::getInstance().log("Add atoms");
    interpSample->addAtoms(pdb->Atoms);
    vector<float> iam_vals;
    for (unsigned int i = 0; i < interpMap->getSize(); ++i)
        iam_vals.push_back(0);
    cout << "BEGIN_IAM\n";
    cout << "i,j,k,Density\n";
    cout << ccp4->W01_NX << "," << ccp4->W02_NY << "," << ccp4->W03_NZ << ",Dimensions\n";
    for (int i = 0; i < ccp4->W01_NX; ++i)
    {
        for (int j = 0; j < ccp4->W02_NY; ++j)
        {
            for (int k = 0; k < ccp4->W03_NZ; ++k)
            {
                VectorThree XYZ = ccp4->getXYZFromCRS(VectorThree(i, j, k).reverse());
                double val_syn = interpSample->getValue(XYZ.A, XYZ.B, XYZ.C);     
                double absval = abs(val_syn);
                int pos = interpMap->getPosition(i, j, k);
                VectorThree tmp = ccp4->getCRS(pos);
                iam_vals[pos] = val_syn;
                if (absval > 0.0001)
                    cout << i << "," << j << "," << k << "," << val_syn << "\n";
                if ((i + j + k) % 100 == 0)
                {
                    stringstream ss;
                    ss << i << "," << j << "," << k;
                    Logger::getInstance().log(ss.str());
                }
            }
        }
    }
    cout << "END_IAM\n";
    ccp4->writeFile(iam_vals, "_IAM");
    interpSample->addMatrix(iam_vals, ccp4->W01_NX, ccp4->W02_NY, ccp4->W03_NZ);
    vector<float> syn_stats = interpSample->getStatsValues();
    vector<int> syn_poses = interpMap->getStatsPoses();
    cout << "BEGIN_IAM_STATS\n";
    cout << "min,q1,q2,q3,max\n";
    for (unsigned int o = 0; o < syn_poses.size(); ++o)
    {
        if (o > 0)
            cout << ",";
        cout << syn_poses[o];
    }
    for (unsigned int o = 0; o < orig_stats.size(); ++o)
    {
        if (o > 0)
            cout << ",";
        else
            cout << "\n";
        cout << syn_stats[o];
    }
    cout << "\n";
    cout << "END_IAM_STATS\n";

    cout << "BEGIN_DEFORMATION\n";    
    cout << "i,j,k,Density\n";
    cout << ccp4->W01_NX << "," << ccp4->W02_NY << "," << ccp4->W03_NZ << ",Dimensions\n";
    for (int i = 0; i < ccp4->W01_NX; ++i)
    {
        for (int j = 0; j < ccp4->W02_NY; ++j)
        {
            for (int k = 0; k < ccp4->W03_NZ; ++k)
            {
                VectorThree XYZ = ccp4->getXYZFromCRS(VectorThree(i, j, k).reverse());
                double val_orig = interpMap->getValue(XYZ.A, XYZ.B, XYZ.C);
                int pos = interpMap->getPosition(i, j, k);
                double val_syn = iam_vals[pos];                
                double absval = abs(val_syn+val_orig);                
                if (absval > 0.0001)
                {
                    double diff = val_orig - val_syn; //no attempt to manipulate them yet.
                    cout << i << "," << j << "," << k << "," << diff << "\n";
                }
                if ((i + j + k) % 1000 == 0)
                {
                    stringstream ss;
                    ss << i << "," << j << "," << k;
                    Logger::getInstance().log(ss.str());
                }
            }
        }
    }
    cout << "END_DEFORMATION\n";

}

void CoutReports::coutSyntheticSlices(string atoms, string model, Interpolator* interp, vector<VectorThree> centrals, vector<VectorThree> linears, vector<VectorThree> planars, double width, double gap)
{
    Logger::getInstance().log("coutSyntheticSlice");
    //The atoms are a list of lines
    if (atoms.size() > 2)
    {
        vector<string> lines = helper::stringToVector(atoms, "@");
        //we want to turn each line ibnto a synthetic atom

        vector<Atom> atomsList;
        for (unsigned int i = 0; i < lines.size(); ++i)
        {
            string line = lines[i];
            if (line.size() > 5)
            {
                atomsList.push_back(Atom(line, false));
            }
        }

        interp->addAtoms(atomsList);

        cout << "BEGIN_ATOMDATA\n";
        cout << "AtomStrings\n";
        for (unsigned int i = 0; i < atomsList.size(); ++i)
            cout << atomsList[i].info() << "\n";
        cout << "END_ATOMDATA\n";
    }
    if (model == "BEM")
        interp->createBondElectrons();//will add bond electron pairs here when do that model TODO

    
    cout << "BEGIN_SLICENUMS\n" << centrals.size() << "\nEND_SLICENUMS\n";
    
    for (unsigned int p = 0; p < centrals.size(); ++p)
    {
        coutSyntheticSlice(interp, centrals[p], linears[p], planars[p], width, gap,p);
    }

}
void CoutReports::coutSyntheticSlice(Interpolator* interp, VectorThree central, VectorThree linear, VectorThree planar, double width, double gap, int position)
{
    //CRETAE SYNTHETIC DENSITY SLICES
    SpaceTransformation space(central, linear, planar);            
    stringstream strpos;
    strpos << position;
    //////////////
    cout << "BEGIN_DENSITYSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_DENSITYSLICE_" + strpos.str());

    int length = (int)(width / gap);
    int halfLength = length / 2;
    cout << "i,j,Density\n";
    for (int i = -1 * halfLength; i <= halfLength; ++i)
    {
        for (int j = -1 * halfLength; j <= halfLength; ++j)
        {
            double x0 = (i * gap);
            double y0 = (j * gap);
            double z0 = 0;
            VectorThree transformed = space.applyTransformation(VectorThree(x0, y0, z0));            
            double density = interp->getValue(transformed.A, transformed.B, transformed.C);
            cout << i + halfLength << "," << j + halfLength << "," << density << "\n";
        }
    }
    cout << "END_DENSITYSLICE_" << position << "\n";

    cout << "BEGIN_RADIANTSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_RADIANTSLICE_" + strpos.str());
    cout << "i,j,Radiant\n";
    for (int i = -1 * halfLength; i <= halfLength; ++i)
    {
        for (int j = -1 * halfLength; j <= halfLength; ++j)
        {
            double x0 = (i * gap);
            double y0 = (j * gap);
            double z0 = 0;
            VectorThree transformed = space.applyTransformation(VectorThree(x0, y0, z0));            
            double radiant = interp->getRadiant(transformed.A, transformed.B, transformed.C);
            cout << i + halfLength << "," << j + halfLength << "," << radiant << "\n";
        }
    }
    cout << "END_RADIANTSLICE_" << position << "\n";

    cout << "BEGIN_LAPLACIANSLICE_" << position << "\n";
    Logger::getInstance().log("BEGIN_LAPLACIANSLICE_" + strpos.str());
    cout << "i,j,Laplacian\n";
    for (int i = -1 * halfLength; i <= halfLength; ++i)
    {
        for (int j = -1 * halfLength; j <= halfLength; ++j)
        {
            double x0 = (i * gap);
            double y0 = (j * gap);
            double z0 = 0;
            VectorThree transformed = space.applyTransformation(VectorThree(x0, y0, z0));            
            double laplacian = interp->getLaplacian(transformed.A, transformed.B, transformed.C);
            cout << i + halfLength << "," << j + halfLength << "," << laplacian << "\n";
        }
    }
    cout << "END_LAPLACIANSLICE_" << position << "\n";

    //FINALLY CRATE THE position matrix
    cout << "BEGIN_POSITIONSLICE_" << position << "\n";
    cout << "i,j,Position\n";
    //we do not need a massive matrix of zeros, these positions go with the above, so we fill with zeros and then place these points
    VectorThree ccc = space.reverseTransformation(central);    
    VectorThree lll = space.reverseTransformation(linear);    
    VectorThree ppp = space.reverseTransformation(planar);
    ccc = ccc/gap;
    ccc.A += (double)halfLength;
    ccc.B += halfLength;    
    int x = (int)ccc.A;
    int y = (int)ccc.B;
    double val = 1;
    if (abs(ccc.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    lll = lll/gap;
    lll.A += (double)halfLength;
    lll.B += halfLength;    
    x = (int)lll.A;
    y = (int)lll.B;
    val = 1;
    if (abs(lll.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    ppp = ppp/gap;
    ppp.A += (double)halfLength;
    ppp.B += halfLength;    
    x = (int)ppp.A;
    y = (int)ppp.B;
    val = 1;
    if (abs(ppp.C > 0.01))
        val = 0.5;//non-planar
    cout << x << "," << y << "," << val << "\n";

    
    cout << "END_POSITIONSLICE_" << position << "\n";

}

void CoutReports::coutText(Ccp4* ccp4,bool cap500)
{
    Logger::getInstance().log("coutText");
    ccp4->coutText(cap500);
}
