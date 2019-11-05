#include<iostream> 
#include<stdio.h> 
#include<stdlib.h>  
#include<fstream> 
#include"contour.h"


using namespace std ;
int pkg;
/**********************************************Definition of Public members functions***********************************************/

//Construtor initialize the value of all variables to zero
   
	contour::contour()
	{
  	    NCOLS = 0 ;
	    NROWS = 0 ;
	    CELLSIZE = 0.0 ;
	    NODATA_VALUE = 0 ;
	    XLLCORNER = 0.0 ;
	    YLLCORNER = 0.0 ;
        }
 
//Function to read Input file into "Input grid Matrix and all the associated variables"
 
	void contour :: readfile (char * s) 
	  {
	    bool space_flag = false ,decimal_flag= false , negative_flag = false;
	    int row_count = 0 , col_count = 0 ,col =0;	
	    int current_character, num = 1;
	    float decimal_value = 0;
	    FILE  * fp = fopen ( s ,  "r" );
// Reading a file character by character and extract a relevant information
// Store the grid in an inputgrid
// Store all the variables

	     if ( !fp )        
	      {
	      cout<<"FILE NOT FOUND"<<endl ;        
	      }
             else 
	     {
	     while   ( ( current_character= fgetc ( fp ) )  != EOF ) 
	          {
	          if(row_count==2&&col==0)
	             {
	               inputgrid = (cell**) malloc((NROWS+2)*sizeof(cell*));  
	                 for (int i = 0; i < NROWS+2; i++)  
	                    inputgrid[i] = (cell*) malloc((NCOLS+2)*sizeof(cell)); 
		         for (int i = 0 ;i<NROWS+2;i++ ) 
		            for (int j = 0 ;j<NCOLS+2 ;j++ ) 
                		  {  
                		   inputgrid[i][j].intensity=0;
                		   inputgrid[i][j].polygonID=0;
                		  }                         
                      }

         	  if ( row_count > 5 )
         	    {
         	        if ( col%4 == 0 ) 
                	 {  
                	     if ( current_character == 49 ) 
                	       inputgrid[row_count-5][col_count+1].intensity = 1 ;
                	     if ( current_character == 50 ) 
                	       inputgrid[row_count-5][col_count+1].intensity = 2 ;   
                             if ( current_character == 51 ) 
                	       inputgrid[row_count-5][col_count+1].intensity = 3 ;     
                	     if ( current_character == 48 ) 
                	       inputgrid[row_count-5][col_count+1].intensity = 0 ;
                	     col_count++ ;
	                 } 
        	       col++;
                    }   
          	 else
                   {
	              if(space_flag == true && current_character!= 10 && current_character!= 13)
               		{
// Reading a NCOls variable 
	               if ( row_count == 0)     
	                 {
	                  NCOLS = NCOLS * 10 +   ( current_character- 48 )  ;                              
	                 }
// Reading a NROWS Variable
	               if ( row_count == 1) 
	                 {
	                  NROWS = NROWS * 10 +   ( current_character- 48 )  ;
	                 }
// Reading a XLLCORNER Variable
	               if ( row_count == 2 && current_character!= 46 && current_character!= 45)  
	                 {
	                  if (decimal_flag == false ) 
	                   {
	                    XLLCORNER = XLLCORNER * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true  ) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; ; 
	                   } 
	                 }
// Reading a YLLCORNER Variable 
	               if ( row_count == 3 && current_character!= 46 && current_character!= 45)     
	                 { 
	                  if (decimal_flag == false) 
	                   {
	                    YLLCORNER =  YLLCORNER * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; ; 
	                   } 
	                 }
// Reading  a CELLSIZE Variable
	               if ( row_count == 4 && current_character!= 46 && current_character!= 45)  
	                 {
	                  if (decimal_flag == false ) 
	                   {
	                    CELLSIZE = CELLSIZE * 10 +   ( current_character- 48 )  ;
	                   }
	                  if (decimal_flag == true) 
	                   {
	                    decimal_value= decimal_value* 10  +   ( current_character- 48 )  ;
	                    num*=10; 
	                   } 
	                 }             
// Reading a NODATA_VALUE Variable
	               if ( row_count == 5 && current_character!= 45)   
	                { 
	                 NODATA_VALUE = NODATA_VALUE * 10 +   ( current_character- 48 )  ;
	                }
	               }
// Set the corresponding flag to true
	               if ( current_character== 46 ) 
	                 {
	                  decimal_flag= true ;
	                 } 
	               if ( current_character== 32 ) 
	                 {
	                  space_flag = true ;
	                 }
	               if ( current_character== 45 ) 
	                 {
	                  negative_flag = true ;
	                 }
	              
// Adding sign (NODATA_VALUE) and decimal parts to a XLLCORNER, YLLCORNER, CELLSIZE
	               if ( current_character== 10)                                                                       
	                {
	                 if ( row_count == 2 ) 
	                  {
	                   XLLCORNER = XLLCORNER  +   ( decimal_value/num )  ;
	                   if ( negative_flag == true ) 
	                    XLLCORNER =  - XLLCORNER ; 
	                  }
	                 if ( row_count == 3 ) 
	                  {
	                   YLLCORNER = YLLCORNER  +   ( decimal_value/num );
	                   if ( negative_flag == true ) 
	                    YLLCORNER =  - YLLCORNER ;
	                  }   
	                 if ( row_count == 4 ) 
	                  {
	                   CELLSIZE = CELLSIZE  +   ( decimal_value/num );
	                  }
	                 if ( row_count == 5 ) 
	                  {
	                   if ( negative_flag == true )                
                    NODATA_VALUE =  - NODATA_VALUE ;
	                  }
	                }
	              }
// Setting and Resetting all the variables before starting with next row.
	           if(current_character== 10)             
	             {
	              space_flag = false ;
	              negative_flag = false ;
	              decimal_flag= false ;
	              decimal_value= 0 ;
	              col_count = 0 ;   
	              col=0;  
	              num = 1 ;
	              row_count++ ;              
	             }
	        }
	     }
	  fclose ( fp ) ;
	}

void contour :: boundaryextraction()
    {
      int polygonID=1 , polygonID1 =0 ,polygonID2 = 0;
      float x1 , x2 , y1 , y2;
      bool merging_required; 
      Polygonwithholes *PWH;
      
      for(int j=1;j<NCOLS+1;j++)
       { 
       for(int i=NROWS;i>0;i--)
        {
        if(inputgrid[i][j].intensity!=0)  // Stop at a cell that has some intensity value
         {   
 // Look weather anew polygon needs to be inserted.
          if(inputgrid[i][j-1].intensity==inputgrid[i][j].intensity || inputgrid[i+1][j].intensity==inputgrid[i][j].intensity)
                 {
 //polygon exists
                   

// assign a polygonID to a cell
                      polygonID1= inputgrid[i+1][j].polygonID;
                      polygonID2 = inputgrid[i][j-1].polygonID;
                      merging_required =  assignpolygonID(i,j, polygonID);
                    
//see if merging is required
                      if(merging_required == true)
                      { 
//merge two PWH nodes
                       mergeanddelete(polygonID1,polygonID2, inputgrid[i][j].intensity);
                      }
                       
                    if(inputgrid[i][j].intensity==1)
                     PWH = list.list->Intensity1List->first;
                    if(inputgrid[i][j].intensity==2)
                     PWH = list.list->Intensity2List->first;
                    if(inputgrid[i][j].intensity==3)
                     PWH = list.list->Intensity3List->first;
              
                   while(PWH->polygonID!=inputgrid[i][j].polygonID)
                     PWH = PWH->next;
//Move to a PWH node that has same polygonID
                     
                    if(inputgrid[i+1][j].intensity!=inputgrid[i][j].intensity)
                     {
//add segment to PWH
//lower segment of cell
                         x1 = XLLCORNER+((j-1)*CELLSIZE);
                         y1 = YLLCORNER+((NROWS-i)*CELLSIZE);
                         x2 = XLLCORNER+((j)*CELLSIZE); 
                         y2 = YLLCORNER+((NROWS-i)*CELLSIZE);
                         add_segment(&PWH , x1, y1, x2, y2);  
                           
                     }     
     

                    if(inputgrid[i][j-1].intensity!=inputgrid[i][j].intensity)
                     {
//add segment to PWH
//Left segment of cell
                         x1 = XLLCORNER+((j-1)*CELLSIZE);
                         y1 = YLLCORNER+((NROWS-i)*CELLSIZE);
                         x2 = XLLCORNER+((j-1)*CELLSIZE); 
                         y2 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                         add_segment(&PWH , x1, y1 , x2 , y2);
                      }
                        
                   if(inputgrid[i-1][j].intensity!=inputgrid[i][j].intensity)
                     {
//add segment to PWH
//upper segment of cell
                         x1 = XLLCORNER+((j-1)*CELLSIZE);
                         y1 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                         x2 = XLLCORNER+((j)*CELLSIZE); 
                         y2 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                         add_segment(&PWH , x1, y1 , x2 , y2);
                      }
                   if(inputgrid[i][j+1].intensity!=inputgrid[i][j].intensity)
                     {
//add segment to PWH 
//Right segment of cell
                         x1 = XLLCORNER+((j)*CELLSIZE);
                         y1 = YLLCORNER+((NROWS-i)*CELLSIZE);
                         x2 = XLLCORNER+((j)*CELLSIZE); 
                         y2 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                         add_segment(&PWH , x1, y1 , x2 , y2);
                     }     
                 
              }
              else
              {   
// create new polygonwithholenode of intensity of the cell
               
                  list.Insert(polygonID ,inputgrid[i][j].intensity);
                  if(inputgrid[i][j].intensity==1)
                  PWH = list.list->Intensity1List->last;
                  if(inputgrid[i][j].intensity==2)
                  PWH = list.list->Intensity2List->last;
                  if(inputgrid[i][j].intensity==3)
                  PWH = list.list->Intensity3List->last;
// lower
                  x1 = XLLCORNER+((j-1)*CELLSIZE);
                  y1 = YLLCORNER+((NROWS-i)*CELLSIZE);
                  x2 = XLLCORNER+((j)*CELLSIZE);
                  y2 = YLLCORNER+((NROWS-i)*CELLSIZE); 
                  list.Insertbegin(x1,y1,x2,y2,&PWH->outercycle);
// Left
                  x1 = XLLCORNER+((j-1)*CELLSIZE);
                  y1 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                  x2 = XLLCORNER+((j-1)*CELLSIZE);
                  y2 = YLLCORNER+((NROWS-i)*CELLSIZE);   
                  list.Insertbegin(x1,y1,x2,y2,&PWH->outercycle);
// upper               
                 if(inputgrid[i-1][j].intensity!=inputgrid[i][j].intensity)
                    {
                      x1 = XLLCORNER+(j*CELLSIZE);
                      y1 = YLLCORNER+((NROWS-i+1)*CELLSIZE);
                      x2 = XLLCORNER+((j-1)*CELLSIZE);
                      y2 = YLLCORNER+((NROWS-i+1)*CELLSIZE); 
                      list.Insertbegin(x1,y1,x2,y2,&PWH->outercycle);
                    }
// Right
                  if(inputgrid[i][j+1].intensity!=inputgrid[i][j].intensity)
                    {
                      x1 = XLLCORNER+(j*CELLSIZE);
                      y1 = YLLCORNER+((NROWS-i)*CELLSIZE);
                      x2 = XLLCORNER+(j*CELLSIZE);
                      y2 = YLLCORNER+((NROWS-i+1)*CELLSIZE); 
                      list.Insertend(x1,y1,x2,y2,&PWH->outercycle);
                       
                    }
                  inputgrid[i][j].polygonID = polygonID; 
                  polygonID++;
              }
            }
           
         }
       }
     }
        
bool contour :: assignpolygonID(int a, int b , int polygonID)
{int i=0 , removedID =0;
  if(inputgrid[a][b].intensity==inputgrid[a][b-1].intensity && inputgrid[a][b].intensity==inputgrid[a+1][b].intensity)
    {
      if(inputgrid[a+1][b].polygonID==inputgrid[a][b-1].polygonID)
        {
          inputgrid[a][b].polygonID = inputgrid[a+1][b].polygonID;
          return false;
        } 
      else
        {
//  Merging required 
          if(inputgrid[a+1][b].polygonID<inputgrid[a][b-1].polygonID)
            {
             inputgrid[a][b].polygonID = inputgrid[a+1][b].polygonID;
             removedID = inputgrid[a][b-1].polygonID;
            }
          else
            {
             inputgrid[a][b].polygonID = inputgrid[a][b-1].polygonID;
             removedID = inputgrid[a+1][b].polygonID;

//Make changes to grid Polygonids by removing the irrelevent polygonID
            }
          for(i=a-1;i>0;i--)
            if(inputgrid[i][b-1].polygonID==removedID)
               inputgrid[i][b-1].polygonID = inputgrid[a][b].polygonID;
          
          for(i=NROWS+1;i>a;i--)
            if(inputgrid[i][b].polygonID==removedID)
               inputgrid[i][b].polygonID = inputgrid[a][b].polygonID;
           

          return true;
        }
    }
  else if(inputgrid[a][b].intensity==inputgrid[a][b-1].intensity)
    { 
      inputgrid[a][b].polygonID = inputgrid[a][b-1].polygonID;
      return false;
    }
  else if(inputgrid[a][b].intensity==inputgrid[a+1][b].intensity)
    {
      inputgrid[a][b].polygonID = inputgrid[a+1][b].polygonID;
      return false;
    }
   
}

// try to attach segment to outer cycle and all the holecycles of a node
// if can be connected to two cycles then we merge those cycles.

void contour :: add_segment(Polygonwithholes **PWH , float x1 , float y1 , float x2 , float y2)
{
  Holeheader *HH , *POCH1, *OCHH1 , *OCHH2 , *POCH2 , *PHH;
  Outercycleheader *OCH , *OCH1 , *OCH2;
  int addedH =0 , w1 , w2 , y = 0;
  bool addedtooutercycle = false , added = false;
 
   if((y=checkandaddseg(&((*PWH)->outercycle), x1 , y1 , x2 , y2))!=0)
   {
    w1 = y;
    
    OCH1 = (*PWH)->outercycle;
    addedtooutercycle = true;
    added = true;
//added to outer cycle
   }
  HH = (*PWH)->holecycles;
  PHH = NULL;
  while(HH!=NULL)
   {
    OCH = HH->holecycle;
    if((y=checkandaddseg(&OCH, x1 , y1 , x2 , y2))!=0)
     { 
//added to hole cycle
       addedH++;
       added=true;

       if(addedtooutercycle == true || addedH==2)
         {
          w2 = y;
          POCH2=PHH;
          OCH2 = OCH;
          OCHH2 = HH;
          if((OCH1->start->x1!=OCH2->start->x1 && OCH1->start->x1 < OCH2->start->x1)||(OCH1->start->x1==OCH2->start->x1 && OCH1->start->y1 < OCH2->start->y1) )
            {
//OCH1 before OCH2 in lexicographical

            if((w1 == 1 || w1 == 2) && (w2 == 1 || w2 == 2)) // If lower ends of both needs to be merged
             {
              list.Invertcycle(&OCH2);
              list.Mergecycles(&OCH1 ,&OCH2 , 0);
              list.DeleteH(POCH2 ,OCHH2);
              if(POCH2==NULL)
                (*PWH)->holecycles = NULL;
             }
            else if((w1 == 3 || w1 == 4) && (w2 == 3 || w2 == 4))  // if upper end of both needs to be merged
             {
              list.Invertcycle(&OCH2);
              list.Mergecycles(&OCH1 ,&OCH2 , 1);
              list.DeleteH(POCH2 , OCHH2);
               if(POCH2==NULL)
                (*PWH)->holecycles = NULL;
           
             }
            else if((w1 == 3 || w1 == 4) && (w2 == 1 || w2 == 2)) // if upper of first and lower of second needs to be merged
             {
              list.Mergecycles(&OCH1 ,&OCH2 , 2);
              list.DeleteH(POCH2 , OCHH2);
              if(POCH2==NULL)
               (*PWH)->holecycles = NULL;
             }
            else if((w1 == 1 || w1 == 2) && (w2 == 3 || w2 == 4)) // if lower of first and upper of second needs to be merged
             {  
              list.Mergecycles(&OCH1 ,&OCH2 , 3);
              list.DeleteH(POCH2 ,OCHH2);
              if(POCH2==NULL)
                (*PWH)->holecycles = NULL;
              
             }
             
            }
          else
            {
// OCH2 before in lexicographical order

             if((w1 == 1 || w1 == 2) && (w2 == 1 || w2 == 2)) // If lower ends of both needs to be merged
             {
              list.Invertcycle(&OCH1);
              list.Mergecycles(&OCH2 ,&OCH1 , 0);
              list.DeleteH(POCH1 , OCHH1);
               if(POCH1==NULL)
                (*PWH)->holecycles = NULL;
             }
             else  if((w1 == 3 || w1 == 4)  && (w2 == 3 || w2 == 4)) // if upper end of both needs to be merged
             {
              list.Invertcycle(&OCH1);
              list.Mergecycles(&OCH2 ,&OCH1 , 1);
              list.DeleteH(POCH1 , OCHH1);
              if(POCH1==NULL)
                (*PWH)->holecycles = NULL; 
             }
             else if((w1 == 3 || w1 == 4) && (w2 == 1 || w2 == 2)) // if upper of first and lower of second needs to be merged
             {
              list.Mergecycles(&OCH2 ,&OCH1 , 2);
              list.DeleteH(POCH1 , OCHH1);
               if(POCH2==NULL)
                (*PWH)->holecycles = NULL;
             }
             else if((w1 == 1 || w1 == 2) && (w2 == 3 || w2 == 4)) // if lower of first and upper of second needs to be merged
             { 
              list.Mergecycles(&OCH2 ,&OCH1 , 3);
              list.DeleteH(POCH1 ,OCHH1);
              if(POCH2==NULL)
                (*PWH)->holecycles = NULL;

             }
            }
            break;
         }
        else
         {
          OCHH1=HH;
          POCH1=PHH;
          w1 = y; 
          OCH1 = OCH;
         }
  
     }
    PHH = HH;
    HH = HH->next;
   } 
// if it can not be attached to any of the existing outer cycle + hole cycles  than inser a new hole cycle
  if(added!=true)
   {
     list.Insertholeheader(PWH);
     HH = (*PWH)->holecycles;
     while(HH->next!=NULL)
     HH = HH->next; 
     list.Insertend( x2 , y2 ,x1 ,y1  ,&(HH->holecycle));
   }
  
}

// this function will try to attach segment to a outercycle to its both ends.
// will return 1 and 2 if the segment is attached to the lower end. 1 and 2 is segment algnment. if segment is a horizontal segment than 1 means its is connected from left to right if 2 then from right to left. if segment is vertical segment then 1 means its connected from down to up and 2 means up to down.
// will return 3 and 4 if the segment is attached to the upper end. Similarly with 3 and 4.
int contour :: checkandaddseg(Outercycleheader **OCH , float x1 , float y1 , float x2 , float y2)
{ 
  if(!(((*OCH)->last->x2==x1&&(*OCH)->last->y2==y1&&(*OCH)->first->x1==x2&&(*OCH)->first->y1==y2) ||((*OCH)->first->x1==x1&&(*OCH)->first->y1==y1&&(*OCH)->last->x2==x2&&(*OCH)->last->y2==y2)))
   {
  
   if((*OCH)->last->x2==x1&&(*OCH)->last->y2==y1)
     {
      if(((*OCH)->last->x1==x2|| (*OCH)->last->y1==y2))
      list.Updateend(x2,y2,OCH);
      else
      list.Insertend(x1,y1,x2,y2,OCH);

      return 1;
     }
    else if((*OCH)->last->x2==x2&&(*OCH)->last->y2==y2)
    {
     if(((*OCH)->last->x1==x1|| (*OCH)->last->y1==y1))
      list.Updateend(x1,y1,OCH);
      else
      list.Insertend(x2,y2,x1,y1,OCH);      

      return 2;
    }
    else if((*OCH)->first->x1==x1&&(*OCH)->first->y1==y1)
      { 
       if(((*OCH)->first->x2==x2|| (*OCH)->first->y2==y2))
      list.Updatebegin(x2,y2,OCH);
      else
      list.Insertbegin(x2,y2,x1,y1,OCH);
     
       return 3;
      }
    else if((*OCH)->first->x1==x2&&(*OCH)->first->y1==y2)
      { 
       if(((*OCH)->first->x2==x1|| (*OCH)->first->y2==y1))
      list.Updatebegin(x1,y1,OCH);
      else
      list.Insertbegin(x1,y1,x2,y2,OCH);
         
       return 4;
      } 
    }
  else
   {
// when the cycle ends means the segment attaches to bot ends
      if((*OCH)->last->x1==x2)
        {  list.Updateend(x2,y2,OCH);
        }
      else
        { 
           list.Insertbegin(x1,y1,x2,y2,OCH);
        }
     return 5;
   }
  
return 0;
}
// merge to PWH hole nodes with polygonID1 and polygonID2
void contour :: mergeanddelete(int polygonID1 , int polygonID2 , int intensity)
{
 Polygonwithholes *PWH1 , *PPWH1 , *PWH2 , *PPWH2  , *PWH , *PPWH;
 Holeheader *HH;
 Outercycleheader *OCH;
 List *list1;
  if(intensity==1)
   {
   PWH = list.list->Intensity1List->first;
   list1= list.list->Intensity1List;
   }
  if(intensity==2)
   {
    PWH = list.list->Intensity2List->first;
   list1= list.list->Intensity2List;
   }
  if(intensity==3)
   {
   PWH = list.list->Intensity3List->first;
   list1= list.list->Intensity3List;
   }
 PPWH1=NULL;
 PPWH2=NULL;
 PPWH = NULL;
 while(PWH!=NULL)
  {
   if(polygonID1 ==  PWH->polygonID) 
          {
             PWH1=PWH;
             PPWH1 = PPWH;
          }
       
   if(polygonID2 == PWH->polygonID) 
          {
             PWH2=PWH;
             PPWH2 = PPWH;
          }
       
   PPWH = PWH;
   PWH = PWH->next;
  }

// see which one exist first in lexicographical order and attach to its outer cycle or hole cycles the outer cycle of other and merge the hole cycle list.

 if((PWH1->outercycle->start->x1!=PWH2->outercycle->start->x1 && PWH1->outercycle->start->x1 < PWH2->outercycle->start->x1)||(PWH1->outercycle->start->x1==PWH2->outercycle->start->x1 && PWH1->outercycle->start->y1 < PWH2->outercycle->start->y1))
  {    if(PWH1->outercycle->last->x2==PWH2->outercycle->first->x1 && PWH1->outercycle->last->y2==PWH2->outercycle->first->y1)
        { 
         list.Mergepolygonwithholes(&PWH1 ,&PWH2 , 0);
         list.DeletePWH(PPWH2 , PWH2);
        }
       else if(PWH1->outercycle->first->x1==PWH2->outercycle->last->x2 && PWH1->outercycle->first->y1==PWH2->outercycle->last->y2)
        {   
         list.Mergepolygonwithholes(&PWH1 ,&PWH2 , 1);
         list.DeletePWH(PPWH2 , PWH2);
        }
       else
        {
         HH = PWH1->holecycles;
         while(HH!=NULL)
          {
             OCH = HH->holecycle;
             if(OCH->first->x1==PWH2->outercycle->first->x1 && OCH->first->y1==PWH2->outercycle->first->y1)
               {
                 list.Invertcycle(&(PWH2->outercycle));

                PWH2->outercycle->last->next=OCH->first;
                OCH->last->next= PWH2->outercycle->first;
                OCH->first =  PWH2->outercycle->first;    

                 list.Mergepolygonwithholes(&PWH1 ,&PWH2 , 3);
                 list.DeletePWH(PPWH2 , PWH2);
                 break;
               }
             HH = HH->next;
          }
        }
     if(list1->last == PWH2)
       list1->last=PPWH2;
  }
  else
  {     if(PWH2->outercycle->last->x2==PWH1->outercycle->first->x1 && PWH2->outercycle->last->y2==PWH1->outercycle->first->y1)
        {   
         list.Mergepolygonwithholes(&PWH2 ,&PWH1 , 0);
         list.DeletePWH(PPWH1 , PWH1);
        }
      else if(PWH2->outercycle->first->x1==PWH1->outercycle->last->x2 && PWH2->outercycle->first->y1==PWH1->outercycle->last->y2)
        {  
         list.Mergepolygonwithholes(&PWH2 ,&PWH1 , 1);
         list.DeletePWH(PPWH1 , PWH1);
        }
      else 
        {
           HH = PWH2->holecycles;
         while(HH!=NULL)
          {
              OCH = HH->holecycle;
            
             if(OCH->first->x1==PWH1->outercycle->first->x1 && OCH->first->y1==PWH1->outercycle->first->y1)
               { 
                list.Invertcycle(&(PWH1->outercycle));
                PWH1->outercycle->last->next=OCH->first;
                OCH->last->next= PWH1->outercycle->first;
                OCH->first =  PWH1->outercycle->first;  
                list.Mergepolygonwithholes(&PWH2 ,&PWH1 , 3);
                list.DeletePWH(PPWH1 , PWH1);
                break;
               }
            HH = HH->next;
          }
        } 
     if(list1->last == PWH1)
       list1->last=PPWH1;
    
  }
 
}     



void contour :: writetofile(char *s)
           {
           ofstream outfile;
            outfile.open (s); 
            int polygonID =0 , holeID=0;
            Node *N;
            Polygonwithholes *PWH;
            Holeheader *HH;
           
            for(int i=1;i<4;i++)
            {
            if(i==1)
            PWH=list.list->Intensity1List->first;
            if(i==2)
            PWH=list.list->Intensity2List->first;
            if(i==3)
            PWH=list.list->Intensity3List->first;
            polygonID = 0;

            if(PWH!=NULL)
            { 
             do
             {
             outfile<<"REGIONID :: "<<polygonID<<"\nINTENSITYLEVEL :: "<<"\nREGION COORDINATES :: {";
             polygonID++;
             holeID=0;
             N=PWH->outercycle->start;
             if(N!=NULL)
              {
             do {
                 outfile<<"("<<N->x1<<","<<N->y1<<"->"<<N->x2<<","<<N->y2<<") ";
                 N = N->next;
                }
             while (N != PWH->outercycle->start);
              }

             outfile<<"}";
             HH = PWH->holecycles;
           
             if(HH!=NULL)
             {
              do
               {
                outfile<<"\n\nHoleID :: "<<holeID;
                outfile<<"\nHOLE COORDINATES :: {";
                holeID++;
                N=HH->holecycle->start;
                if(N!=NULL)
                 {
                do {
                    outfile<<"("<<N->x1<<","<<N->y1<<"->"<<N->x2<<","<<N->y2<<") ";
                    N = N->next;
                   } 
                while (N != HH->holecycle->start);
                 }
                outfile<<"}" ;
                HH = HH->next;
               }
              while(HH!=NULL);
             }
             outfile<<"\n\n\t\t\t\t\t\t\t***************************************************\n\n";
             PWH = PWH->next;
             }
            while(PWH!=NULL); 
            }
           } 
            cout<<"Traversal done"<<endl;
            outfile.close();

       }   
