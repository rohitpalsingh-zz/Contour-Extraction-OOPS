#include "Listclass.h"
#include <iostream>
#include <cstdlib>

using namespace std;


// basic constructor function

       Listclass :: Listclass()
          {
           list = (Header*)malloc(sizeof(Header));
           list->Intensity1List = (List*)malloc(sizeof(list));
           list->Intensity2List = (List*)malloc(sizeof(list));
           list->Intensity3List = (List*)malloc(sizeof(list));

           list->Intensity1List->first=NULL;
           list->Intensity1List->last=NULL;
     
           list->Intensity2List->first=NULL;
           list->Intensity2List->last=NULL;

           list->Intensity3List->first=NULL;
           list->Intensity3List->last=NULL;
	  }

// basic deconstructor function
       Listclass :: ~Listclass()
          {
            Node *N , *PN;
            Polygonwithholes *PWH , *PPWH;
            Holeheader *HH , *PHH;
            for(int i=0;i<3;i++)
            {
            if(i==0)
            PWH=list->Intensity1List->first;
            if(i==1)
            PWH=list->Intensity2List->first;
            if(i==2)
            PWH=list->Intensity3List->first;
            
            if(PWH!=NULL)
            { 
             do
             {
             N=PWH->outercycle->first;
             if(N!=NULL)
              {
             do {
                 PN=N;
                 N = N->next;
                 PWH->outercycle->first = N;
                 free(PN);
                }
             while (N != PWH->outercycle->last);
              }
             HH = PWH->holecycles;
           
             if(HH!=NULL)
             {
              do
               {
                N=HH->holecycle->first;
                if(N!=NULL)
                 {
                do {
                    PN=N;
                    N = N->next;
                    HH->holecycle->first=N;
                    free(PN);
                   } 
                while (N != HH->holecycle->last);
                 }
                PHH=HH;
                HH = HH->next;
                PWH->holecycles = HH;
                free(PHH);                
               }
              while(HH!=NULL);
             }
             PPWH = PWH;
             PWH = PWH->next;
             if(i==0)
             list->Intensity1List->first = PWH;
             if(i==1)
             list->Intensity2List->first = PWH;
             if(i==2)
             list->Intensity3List->first = PWH;
             free(PPWH);
             }
            while(PWH!=NULL); 
            }
           }
          }

//  merge operations merge outercycle PWH2 to the beginning if PWH1 if w is 1 otherwise to the end if w is 0
         void Listclass :: Mergepolygonwithholes(Polygonwithholes** PWH1 , Polygonwithholes** PWH2 , int w)
            {
             Holeheader *temp;
             
             if(w==0)
              {
                (*PWH1)->outercycle->last->next=(*PWH2)->outercycle->first;
                (*PWH1)->outercycle->last=(*PWH2)->outercycle->last;
                (*PWH2)->outercycle->last->next=(*PWH1)->outercycle->first;
              }
             else if(w==1)
              {
               (*PWH2)->outercycle->last->next=(*PWH1)->outercycle->first;
               (*PWH1)->outercycle->first = (*PWH2)->outercycle->first;
               (*PWH1)->outercycle->last->next=(*PWH1)->outercycle->first;
              }
              if((*PWH1)->holecycles!=NULL) 
               {
                temp = (*PWH1)->holecycles;
                while(temp->next!=NULL)            
                 temp=temp->next;
                 temp->next = (*PWH2)->holecycles;
                }
              else
               {
                 (*PWH1)->holecycles = (*PWH2)->holecycles;
               } 


              (*PWH2)->holecycles=NULL;
              (*PWH2)->outercycle->first=NULL;
              (*PWH2)->outercycle->start=NULL;
              (*PWH2)->outercycle->last=NULL;
            }
//  merge operations merge outercycle OCH2 to the beginning if OCH1 if w is 1 otherwise to the end if w is 0
          void Listclass :: Mergecycles(Outercycleheader** OCH1 , Outercycleheader** OCH2 , int w)
              {
               Node *N ,*temp;
               if(w==0)
              { 
                N = (*OCH2)->first;

                (*OCH2)->first = (*OCH2)->first->next;
                (*OCH2)->last->next = (*OCH2)->first;
                free(N); 

                (*OCH1)->last->next=(*OCH2)->first;
                (*OCH1)->last=(*OCH2)->last;
                (*OCH1)->last->next=(*OCH1)->first;
              }
             else if(w==1)
              {
                 N = (*OCH1)->first;

                (*OCH1)->first = (*OCH1)->first->next;
                (*OCH1)->last->next = (*OCH1)->first;
                free(N); 
                             
                      
               (*OCH2)->last->next=(*OCH1)->first;
               (*OCH1)->first = (*OCH2)->first;
               (*OCH1)->last->next=(*OCH1)->first;  
              }
             else if(w==2)
              {
                N = (*OCH2)->start;
               while(N->next != (*OCH2)->last)
                  N=N->next;
                    
               N->next =(*OCH2)->first;
               temp = (*OCH2)->last; 
               (*OCH2)->last = N;
               free(temp);
                
               (*OCH2)->last->next=(*OCH1)->first;
               (*OCH1)->first = (*OCH2)->first;
               (*OCH1)->last->next=(*OCH1)->first;  
               }
             else if(w==3)
              {
                N = (*OCH1)->start;
               while(N->next != (*OCH1)->last)
                  N=N->next;
                    
               N->next =(*OCH1)->first;
               temp = (*OCH1)->last; 
               (*OCH1)->last = N;
               free(temp);

               (*OCH1)->last->next=(*OCH2)->first;
               (*OCH1)->last = (*OCH2)->last;
               (*OCH1)->last->next=(*OCH1)->first;  
              }
              (*OCH2)->last=NULL;
              (*OCH2)->first=NULL;
              (*OCH2)->start=NULL;
             }
       void Listclass :: Invertcycle(Outercycleheader** OCH)
             {
               Node *N , *NN , *PN , *FN;
               float x,y;
               N=(*OCH)->first;
               x=N->x1;
               y=N->y1;
               N->x1 = N->x2;
               N->y1 = N->y2;
               N->x2 = x;
               N->y2 = y; 
               NN = N->next;
               N->next = (*OCH)->last;
               PN = N;
               if((*OCH)->first != (*OCH)->last)
               {
               do
               {
                 N=NN;
                 x=N->x1;
                 y=N->y1;
                 N->x1 = N->x2;
                 N->y1 = N->y2;
                 N->x2 = x;
                 N->y2 = y;
                 NN = N->next;
                 N->next = PN;
                 PN = N;
               }
               while(N!=(*OCH)->last);
               }
              FN = (*OCH)->first;
              (*OCH)->first = (*OCH)->last;
              (*OCH)->last = FN; 

             } 
      void Listclass :: Swapendpoints(Outercycleheader** OCH)
             {
               Node *N ;
               float x,y;
               N=(*OCH)->first;
               do
               {
                 x=N->x1;
                 y=N->y1;
                 N->x1 = N->x2;
                 N->y1 = N->y2;
                 N->x2 = x;
                 N->y2 = y;
                 N = N->next;
               }
               while(N!=(*OCH)->first);
             } 
            
// add Polygonwithholes node to end of Polygonwithholes list
       void Listclass :: Insert (int polygonID , int which)
            {
             List *list1;
             Polygonwithholes *PWH;
             PWH = (Polygonwithholes*)malloc(sizeof(Polygonwithholes));
             PWH->polygonID = polygonID;
             PWH->outercycle = (Outercycleheader*)malloc(sizeof(Outercycleheader));
             PWH->outercycle->first=NULL;
             PWH->outercycle->start=NULL;
             PWH->outercycle->last=NULL;
             PWH->holecycles=NULL;
             PWH->next=NULL;

             if(which==1)
             list1 = list->Intensity1List;
             if(which==2)
             list1 = list->Intensity2List;
             if(which==3)
             list1 = list->Intensity3List;
  
 
             if(list1->first==NULL)
              {
                list1->first = PWH;
                list1->last = PWH;
              }
             else
              {
                list1->last->next=PWH;
                list1->last = PWH;
              }
          } 
// add holeheader to end of hole list
       void Listclass :: Insertholeheader(Polygonwithholes **PWH)
            {
              Holeheader *HH , *temp;
              Outercycleheader *OCH;
              HH = (Holeheader*)malloc(sizeof(Holeheader));
              OCH =  (Outercycleheader*)malloc(sizeof(Outercycleheader));
              OCH->first=NULL; 
              OCH->start=NULL;
              OCH->last=NULL;
              HH->next=NULL;

              HH->holecycle=OCH;
             
  
              if((*PWH)->holecycles==NULL)
               {
                (*PWH)->holecycles=HH;
               }
              else
               {
                temp = (*PWH)->holecycles;
                while(temp->next!=NULL)
                 {
                    temp=temp->next;
                 }
                temp->next=HH;
               }
            }
// delete a particuar Outer Cycle node given the Previous Outer cycle access
       void Listclass :: DeleteH (Holeheader* PHH , Holeheader* HH)
            {
            Node *N;
            Node *PN;
            int k;
                        
            N = HH->holecycle->first;
           
             if(N!=NULL)
             {
             do {
                PN = N;
                N = N->next;
                free(PN);
               }
             while (N->next != HH->holecycle->last);
              }
              
               free(HH->holecycle);
            
               if(PHH!=NULL)
                {     
                 PHH->next = HH->next;
                 free(HH);
                }
               else
                free(HH);
                
                      
            }  

// delete a particuar Outer Cycle node given the Previous Outer cycle access
       void Listclass :: DeletePWH (Polygonwithholes* PPWH , Polygonwithholes* PWH)
            {
            Node *N , *PN;
            Holeheader *HH , *PHH;
               
            N=PWH->outercycle->first;
             if(N!=NULL)
              {
             do {
                 PN=N;
                 N = N->next;
                 PWH->outercycle->first = N;
                 free(PN);
                }
             while (N != PWH->outercycle->last);
              }
             HH = PWH->holecycles;
           
             if(HH!=NULL)
             {
              do
               {
                N=HH->holecycle->first;
                if(N!=NULL)
                 {
                do {
                    PN=N;
                    N = N->next;
                    HH->holecycle->first=N;
                    free(PN);
                   } 
                while (N != HH->holecycle->last);
                 }
                PHH=HH;
                HH = HH->next;
                PWH->holecycles = HH;
                free(PHH);                
               }
              while(HH!=NULL);
             }
             if(PPWH!=NULL)
             PPWH->next = PWH->next;
           
             
             free(PWH);
           }  

// add node to the begining of the node list of a given Outer Cycle
       void Listclass :: Insertbegin (float x1 , float y1 , float x2 , float y2 ,Outercycleheader ** OCH)
            {
            Node *N;
            N= (Node*)malloc(sizeof(Node));
            N->x1=x1;
            N->y1=y1;
            N->x2=x2;
            N->y2=y2;

             if((*OCH)->start==NULL)
             {
              (*OCH)->first=N;
              (*OCH)->last=N;
              (*OCH)->start=N;
               N->next=(*OCH)->first;
             }
             else
             {
            N->next=(*OCH)->first;
            (*OCH)->first = N;
            (*OCH)->last->next = (*OCH)->first;
             }
            }
  
// add node to the end of the node coordinate list of given Outer Cycle
       void Listclass :: Insertend (float x1 , float y1 , float x2 , float y2 ,Outercycleheader ** OCH)
            {
            Node *N;
            N= (Node*)malloc(sizeof(Node));
            N->x1=x1;
            N->y1=y1;
            N->x2=x2;
            N->y2=y2;
            if((*OCH)->start==NULL)
             {
              (*OCH)->first=N;
              (*OCH)->last=N;
              (*OCH)->start=N;
              N->next=(*OCH)->first;
             }
             else
             {
            (*OCH)->last->next=N;
            N->next=(*OCH)->first;
            (*OCH)->last = N;
              }
          }
       void Listclass :: Updateend(float x1 , float y1 ,Outercycleheader ** OCH)
            {
            Node *N;
            N = (*OCH)->last;
            N->x2=x1;
            N->y2=y1;
            }
      void Listclass :: Updatebegin(float x1 , float y1 ,Outercycleheader ** OCH)
            {
            Node *N;
            N = (*OCH)->first;
            N->x1=x1;
            N->y1=y1;
            }
 
