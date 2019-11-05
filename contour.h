# include "Listclass.h"
using namespace std;

class contour {
   
  public :
          contour();
         // Reads the input file grids into original_matrix and NCOLS, NROWS, XLLCORNER, YLLCORNER, CELLSIZE, NODATA_VALUE 
          void readfile (char * inputfilename); 
         //Write to a file Region Segment in a counter clockwise order for regions with holes.
          void boundaryextraction();
         //Write to file the outercycles
          void writetofile(char * outputfilename);

  private : 
          struct cell
          {
           int intensity;    // This holds the intesity value of the cell.
           int polygonID;
           };
          cell** inputgrid;  // Original matrix
          Listclass list;       // will point to three Polygonwithholes nodes cycles 
          int NCOLS ;  // number of coloumn
          int NROWS ;  // number of rows
          float XLLCORNER;  // western most x coordinate
          float YLLCORNER;  // southern most y coordinate 
          float CELLSIZE;   // one side of a square cell
          int NODATA_VALUE; // missing or not applicable data value
          // Add segment to a polygonwithhole
          void add_segment(Polygonwithholes** PWH , float x1 , float y1 , float x2 , float y2 );
          int checkandaddseg(Outercycleheader **OCH , float x1 , float y1 , float x2 , float y2);
          // Merge polygonwithholes
          void mergeanddelete(int polygonID1 , int PolygonID2 , int intensity);
          bool assignpolygonID(int i , int j ,int polygonID);
          
};



