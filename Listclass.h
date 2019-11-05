
using namespace std;               

// list hierarchial structure defenition
                struct Node {
			// data
			float x1;
                        float y1;
                        float x2;
                        float y2;                        
			Node *next;
               	};         

               	struct Outercycleheader {
                        Node *first;
                        Node *last;
                        Node *start;      
                };
                
               	struct Holeheader {
                       Outercycleheader *holecycle;
                       Holeheader *next;                        
                };    
                       
                struct Polygonwithholes {
                        int polygonID;
                        Outercycleheader *outercycle;
                        Holeheader *holecycles;
                        Polygonwithholes *next;
                };
                struct List {
                       Polygonwithholes *first;
                       Polygonwithholes *last;
                };
                struct Header {
                       List *Intensity1List;
                       List *Intensity2List;
                       List *Intensity3List;
                };


class Listclass {

     public:
		// basic constructor function
		 Listclass ();
		// deconstructor function
		~Listclass ();
                //list header
                Header *list;

		// merge operations merge Second Argument type A2 to the beginning if First Argument type A1 if where (where to add) is 1 otherwise to the end if where is 0
                void Mergepolygonwithholes (Polygonwithholes** A1 , Polygonwithholes** A2 , int where); 
                void Mergecycles (Outercycleheader **A1 , Outercycleheader **A2 , int where);
                // delete a particuar Polygonwithholes
                void DeletePWH (Polygonwithholes* PPWH , Polygonwithholes* PWH);
                // delete a particuclar hole
                void DeleteH (Holeheader* PHH , Holeheader* HH);
                // add Poygonwithholes node to end of Poygonwithholes list. which one of the 3 lists are identified by which variable
             	void Insert (int polygonID , int which);
                // add holeheader to the end of holelist
                void Insertholeheader (Polygonwithholes **PWH);
                // add node to the begining of the node list 
                void Insertbegin (float x1, float y1, float x2 , float y2 , Outercycleheader** OCH);
                // add node to the end of the node list
                void Insertend (float x1, float y1, float x2 , float y2 , Outercycleheader** OCH);
                // add node to the begining of the node list 
                void Updatebegin (float x1, float y1, Outercycleheader** OCH);
                // add node to the end of the node list
                void Updateend (float x1, float y1, Outercycleheader** OCH);
                // To invert a Outer cycle
                void Invertcycle(Outercycleheader** OCH);
                // To invert a Outer cycle
                void Swapendpoints(Outercycleheader** OCH);
               
};

